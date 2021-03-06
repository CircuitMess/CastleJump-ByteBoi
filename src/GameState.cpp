#include <ByteBoi.h>
#include <Arduino.h>
#include "GameState.h"
#include "Melodies/Notes.hpp"
#include "bitmaps/player.hpp"
#include "bitmaps/coin.hpp"
#include "bitmaps/power_up.hpp"
#include "bitmaps/leftWall.hpp"
#include "bitmaps/rightWall.hpp"
#include "bitmaps/floor.hpp"
#include "bitmaps/platform1_1.hpp"
#include "bitmaps/platform1_2.hpp"
#include "bitmaps/platform1_3.hpp"
#include "bitmaps/platform2_1.hpp"
#include "bitmaps/platform2_2.hpp"
#include "bitmaps/platform2_3.hpp"
#include "bitmaps/platform3_1.hpp"
#include "bitmaps/platform3_2.hpp"
#include "bitmaps/platform3_3.hpp"
#include "bitmaps/lava.hpp"
#include "bitmaps/heart/heart1.hpp"
#include "bitmaps/red_screen.hpp"
#include "bitmaps/window.hpp"
#include "bitmaps/brick2.hpp"
#include "bitmaps/brick1.hpp"
#include "bitmaps/brick3.hpp"
#include <FS/PGMFile.h>
#include <FS/CompressedFile.h>
#include <SPIFFS.h>
#include <SD.h>
#include <Playback/PlaybackSystem.h>
#include <Playback/Sample.h>

CastleJump::GameState* CastleJump::GameState::instance = nullptr;

const unsigned short* listBricks1[2] = {cigle2, cigle3};
const unsigned short* listBricks2[2] = {window_draw, cigle1};

CastleJump::GameState::GameState(Screen* screen) : heartGif(screen->getSprite(), ByteBoi.openResource("/heart.hpp.g565", "r")),
									 lavaGif(screen->getSprite(), CompressedFile::open(ByteBoi.openResource("/PodLava160x10.g565.hs", "r"), 13, 12,866), true), screen(screen){


	display = ByteBoi.getDisplay();
	baseSprite = screen->getSprite();
	instance = this;

	heartGif.setXY(130, 4);
	heartGif.setMaskingColor(TFT_BLACK);

	lavaGif.setLoop(true);
	lavaGif.setXY(0, 110);
	lavaGif.setMaskingColor(TFT_BLACK);
	lavaGif.nextFrame();

	player.pos.x = 66;
	player.pos.y = 66;
	player.velocity.x = 0;
	player.velocity.y = 0;

	coin.push_back({50, -700, 2, TFT_GOLD});

	powerUp.push_back({50, -1800, 2, TFT_BLUE});

	bricks.push_back({70, 80, 40, 20});

	window.push_back({20, 30, 20, 20});

	dropRect.push_back({40, 0, 20, 2});
	dropRect.push_back({20, -23, 10, 2});
	dropRect.push_back({90, -50, 20, 2});
	dropRect.push_back({80, -75, 20, 2});
	dropRect.push_back({110, -97, 40, 2});

	randBitmapBrick = 0;
	randBitmapWin = 0;

	score = 0;

	grassFloorBuffer = static_cast<Color*>(ps_malloc(160 * 10 * 2));
	if(grassFloorBuffer == nullptr){
		return;
	}

	fs::File grassFloorFile = ByteBoi.openResource("/Pod160x10.raw");

	grassFloorFile.read(reinterpret_cast<uint8_t*>(grassFloorBuffer), 160 * 10 * 2);
	grassFloorFile.close();

}

CastleJump::GameState::~GameState(){
	GameState::stop();
	free(grassFloorBuffer);
}

void CastleJump::GameState::start(CastleJump& gameEnter){
	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		Playback.tone(NOTE_B6, 25);
		instance->castleJump->pauseGame();
	});
	Input::getInstance()->setBtnPressCallback(BTN_C, [](){
		Playback.tone(NOTE_B6, 25);
		instance->castleJump->pauseGame();
	});
	Input::getInstance()->setBtnPressCallback(BTN_RIGHT, buttonRightPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_RIGHT, buttonRightRelease);
	Input::getInstance()->setBtnPressCallback(BTN_LEFT, buttonLeftPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_LEFT, buttonLeftRelease);

	extern Sample* gameMusic;
	//Playback.play(gameMusic);
}

void CastleJump::GameState::stop(){
	Input::getInstance()->removeBtnPressCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnPressCallback(BTN_LEFT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_LEFT);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnReleaseCallback(BTN_B);
	Input::getInstance()->removeBtnPressCallback(BTN_C);
	Input::getInstance()->removeBtnReleaseCallback(BTN_C);
	LED.setRGB(OFF);
	Playback.stop();
	delay(100);
}

void CastleJump::GameState::buttonLeftPress(){
	instance->leftState = true;


}

void CastleJump::GameState::buttonLeftRelease(){
	instance->leftState = false;

}

void CastleJump::GameState::buttonRightPress(){
	instance->rightState = true;

}

void CastleJump::GameState::buttonRightRelease(){
	instance->rightState = false;

}

void CastleJump::GameState::drawPlayerCircle(){
	baseSprite->drawIcon(icon_player, player.pos.x, player.pos.y, 8, 8, 1, TFT_BLACK);
}

void CastleJump::GameState::drawCoin(Coin& goldenCoin){
	baseSprite->drawIcon(icon_coin, goldenCoin.x, goldenCoin.y, 5, 5);
}

void CastleJump::GameState::drawRect(Rect& stairs){
	if(lvl == 1 && stairs.w == 10){
		baseSprite->drawIcon(icon_platform1_1, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}else if(lvl == 1 && stairs.w == 20){
		baseSprite->drawIcon(icon_platform1_2, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}else if(lvl == 1 && stairs.w == 40){
		baseSprite->drawIcon(icon_platform1_3, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}else if(lvl == 2 && stairs.w == 10){
		baseSprite->drawIcon(icon_platform2_1, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}else if(lvl == 2 && stairs.w == 20){
		baseSprite->drawIcon(icon_platform2_2, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}else if(lvl == 2 && stairs.w == 40){
		baseSprite->drawIcon(icon_platform2_3, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}else if(lvl == 3 && stairs.w == 10){
		baseSprite->drawIcon(icon_platform3_1, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}else if(lvl == 3 && stairs.w == 20){
		baseSprite->drawIcon(icon_platform3_2, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}else if(lvl == 3 && stairs.w == 40){
		baseSprite->drawIcon(icon_platform3_3, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}else if(lvl == 4 && stairs.w == 10){
		baseSprite->drawIcon(icon_platform1_1, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}else if(lvl == 4 && stairs.w == 20){
		baseSprite->drawIcon(icon_platform2_2, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}else if(lvl == 4 && stairs.w == 40){
		baseSprite->drawIcon(icon_platform3_3, stairs.x, stairs.y, stairs.w, stairs.h, 1, TFT_BLACK);
	}
}

void CastleJump::GameState::drawAbilityPoint(PowerUps& ability){
	baseSprite->drawIcon(power_up, ability.x, ability.y, 5, 5);
}

void CastleJump::GameState::drawBrick(BackPict& brick){
	baseSprite->drawIcon(listBricks1[randBitmapBrick], brick.x, brick.y, brick.w, brick.h, 1, TFT_BLACK);
}

void CastleJump::GameState::drawWindow(BackPict& windows){
	baseSprite->drawIcon(listBricks2[randBitmapWin], windows.x, windows.y, windows.w, windows.h, 1, TFT_BLACK);
}

void CastleJump::GameState::drawWalls(){
	baseSprite->drawIcon(leftWall, 0, 0, 5, 128);
	baseSprite->drawIcon(rightWall, 155, 0, 5, 128);
}

void CastleJump::GameState::drawFloor(){
	if(!firstTouch){

		baseSprite->drawIcon(grassFloorBuffer, 0, 115, 160, 10);

	}else if(firstTouch){
		lavaGif.push();
	}
}

void CastleJump::GameState::xPosMoving(){
	if(player.pos.x > 145){
		checkWallBump = true;
		rightState = false;
		player.pos.x = 146;
		player.velocity.x = -70;
		Playback.tone(NOTE_E4, 100);

	}
	if(player.pos.x < 8){
		checkWallBump = true;
		leftState = false;
		player.pos.x = 7;
		player.velocity.x = 80;
		Playback.tone(NOTE_E4, 100);

	}
	if(!rightState && !checkWallBump){
		player.velocity.x = 0;
	}
	if(!leftState && !checkWallBump){
		player.velocity.x = 0;
	}
	if(rightState){
		checkWallBump = false;
		player.velocity.x = 50;
	}
	if(leftState){
		checkWallBump = false;
		player.velocity.x = -50;
	}
}

void CastleJump::GameState::movingRects(Rect& stairs, uint b){
	if(!highspeed){
		stairs.y += 0.6 * speed * b / 20000;
	}
	if(highspeed){
		stairs.y += 0.8 * speed * b / 20000;
		currentTime = millis();
		if(currentTime - previousTime > 1000){
			previousTime = currentTime;
			seconds--;
		}
		if(seconds < 0){
			seconds = 5;
			highspeed = false;
		}
	}
	if(stairs.y > 117){
		if(firstTouch){
			score++;
		}
		float randX;
		do {
			stairs.y = 0;
			randX = random(9, 110);
		} while(abs(randX - stairs.x > 50));
		stairs.x = randX;
	}
}


void CastleJump::GameState::velocity(float dt){
	player.pos += player.velocity * dt;
	if(!lowGravity){
		player.velocity += gravity * dt;
	}
	if(lowGravity){
		player.velocity += gravity * 0.3 * dt;
		currentTime = millis();
		if(currentTime - previousTime > 1000){
			previousTime = currentTime;
			seconds--;
		}
		if(seconds < 0){
			seconds = 5;
			lowGravity = false;
		}
	}

}


void CastleJump::GameState::checkForPoint(Coin& goldenCoin){
	if(abs(player.pos.x - goldenCoin.x) == 0 && abs((player.pos.y - goldenCoin.y) == 0) ||
	   (abs(player.pos.x - goldenCoin.x) + abs((player.pos.y - goldenCoin.y))) <= 5){
		Playback.tone(NOTE_B5, 100);
		Playback.tone(NOTE_E6, 150);
		score = score + 5;
		coinIsPicked = true;
		goldenCoin.y = -700;
		float randX;
		do {
			goldenCoin.y = -700;
			randX = random(10, 140);
		} while(abs(randX - goldenCoin.x > 30));
		goldenCoin.x = randX;
	}
}

void CastleJump::GameState::checkForPowerUp(PowerUps& powerUp){
	if(abs(player.pos.x - powerUp.x) == 0 && abs((player.pos.y - powerUp.y) == 0) ||
	   (abs(player.pos.x - powerUp.x) + abs((player.pos.y - powerUp.y))) <= 5){
		Playback.tone(NOTE_E6, 150);
		int randNum = random(1, 3);
		if(randNum == 1){
			highspeed = true;
		}
		if(randNum == 2){
			lowGravity = true;
		}
		powerUp.y = -1800;
		float randX;
		do {
			powerUp.y = -1800;
			randX = random(10, 140);
		} while(abs(randX - powerUp.x > 30));
		powerUp.x = randX;
	}
}

void CastleJump::GameState::checkForCollision(Rect& stairs){
	if(player.velocity.y < 0){
		return;
	}

	if(stairs.w == 20){
		float distX = abs(player.pos.x - stairs.x - 10);
		float distY = abs(player.pos.y - stairs.y - 1);
		if((distX <= 11.5 && distY <= 8)){
			player.velocity.y = -min(player.velocity.y, 110.0f);
			firstTouch = true;
		}
	}else if(stairs.w == 40){
		float distX = abs(player.pos.x - stairs.x - 20);
		float distY = abs(player.pos.y - stairs.y - 1);
		if((distX <= 21.5 && distY <= 8)){
			player.velocity.y = -min(player.velocity.y, 110.0f);
			firstTouch = true;
		}

	}else if(stairs.w == 10){
		float distX = abs(player.pos.x - stairs.x - 5);
		float distY = abs(player.pos.y - stairs.y - 1);
		if((distX <= 6.5 && distY <= 8)){
			player.velocity.y = -min(player.velocity.y, 110.0f);
			firstTouch = true;
		}

	}
}

void CastleJump::GameState::scoreTable(){
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Score:", 7, 4);
	baseSprite->drawNumber(score - 0, 44, 4);
}

void CastleJump::GameState::powerUpTimer(){
	baseSprite->setTextColor(TFT_GREEN);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->drawNumber(seconds - 0, 10, 105);
}

void CastleJump::GameState::levelCounter(){
	if(score >= 100){
		lvl = 2;
	}
	if(score >= 200){
		lvl = 3;
	}
	if(score >= 300){
		lvl = 4;
	}
}

void CastleJump::GameState::level(){
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Lvl: ", 73, 4);
	baseSprite->drawNumber(lvl - 0, 99, 4);
}

void CastleJump::GameState::lives(){
	if(heartGif.checkFrame()){
		heartGif.nextFrame();
	}
	heartGif.push();
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->drawString("x", 140, 4);
	baseSprite->drawNumber(livesNum - 0, 147, 4);
}

void CastleJump::GameState::movingBrick(BackPict& brick, uint b){
	if(firstTouch){
		brick.y += backgorundSpeed * speed * b / 20000;
		if(brick.y > 125){
			brick.y = -20;
			randBitmapBrick = random(0, 2);
		}
	}
}

void CastleJump::GameState::movingWindow(BackPict& window, uint b){
	if(firstTouch){
		window.y += backgorundSpeed * speed * b / 20000;
		if(window.y > 125){
			window.y = -20;
			randBitmapWin = random(0, 2);
		}
	}
}

void CastleJump::GameState::movingCoin(Coin& goldenCoin, uint b) const{
	goldenCoin.y += 1.1 * speed * b / 20000;
	if(goldenCoin.y > 117){
		float randX;
		do {
			goldenCoin.y = -700;
			randX = random(10, 130);
		} while(abs(randX - goldenCoin.x > 60));
		goldenCoin.x = randX;
	}
}

void CastleJump::GameState::movingPowerUps(PowerUps& ability, uint b) const{
	ability.y += 1.1 * speed * b / 20000;
	if(ability.y > 117){
		float randX;
		do {
			ability.y = -1800;
			randX = random(10, 130);
		} while(abs(randX - ability.x) > 60);
		ability.x = randX;
	}
}

void CastleJump::GameState::checkLevel(){
	if(lvl == 1){
		speed = 1;
		backgorundSpeed = 0.2;
	}
	if(lvl == 2){
		speed = 1.2;
		backgorundSpeed = 0.3;
	}
	if(lvl == 3){
		speed = 1.4;
		backgorundSpeed = 0.4;
	}
	if(lvl == 4){
		speed = 1.6;
		backgorundSpeed = 0.5;
	}
}

void CastleJump::GameState::draw(){
	baseSprite->clear(TFT_DARKGREY);
	drawBrick(bricks[0]);
	drawWindow(window[0]);
	for(int i = 0; i < dropRect.size(); ++i){
		drawRect(dropRect[i]);
	}
	if(isDrawing){
		drawPlayerCircle();
	}
	drawWalls();
	drawFloor();
	for(int i = 0; i < 1; i++){
		drawCoin(coin[i]);
		drawAbilityPoint(powerUp[i]);
	}
	scoreTable();
	level();
	lives();
	if(drawCoinText){
		baseSprite->setTextColor(TFT_GOLD);
		baseSprite->setTextFont(1);
		baseSprite->setTextSize(1);
		baseSprite->drawString("+5", 44, 13);
	}
	if(highspeed){
		baseSprite->setTextColor(TFT_GREEN);
		baseSprite->setTextFont(1);
		baseSprite->setTextSize(1);
		baseSprite->drawString("High speed!", 5, 100);
	}
	if(lowGravity){
		baseSprite->setTextColor(TFT_GREEN);
		baseSprite->setTextFont(1);
		baseSprite->setTextSize(1);
		baseSprite->drawString("Low gravity!", 5, 100);
	}
	screen->commit();

}

void CastleJump::GameState::loop(uint time){
	castleJump->score = score;
	xPosMoving();
	levelCounter();
	checkLevel();
	float dt = (float) time / 1000000.0f;
	velocity(dt);

	for(int i = 0; i < dropRect.size(); ++i){
		movingRects(dropRect[i], time);
		checkForCollision(dropRect[i]);
	}
	if(!firstTouch && player.pos.y > 110){
		Playback.tone(NOTE_E4, 100);
		player.pos.y = 110;
		player.velocity.y = -min(player.velocity.y, 200.0f);
	}
	if(firstTouch && player.pos.y > 120){
		player.pos.y = 120;
		if(firstTouch){
			if(livesNum > 0){
				livesNum--;
				heartGif.reset();
				lostLife = true;
				Playback.tone(NOTE_C4, 100);
			}

		}
		player.velocity.y = -min(player.velocity.y, 200.0f);
	}
	if(coinIsPicked){
		drawCoinText = true;
		currentTime = millis();
		if(currentTime - previousTimeCoin > 1000){
			previousTime = currentTime;
			secondsCoin--;
		}
		if(secondsCoin < 0){
			drawCoinText = false;
			coinIsPicked = false;
			secondsCoin = 15 ;
		}else{
			drawCoinText = true;
		}
	}
	if(lostLife){
		if(millis() - previousTimeBlink >= 100){
			previousTimeBlink = millis();
			if(LED.getRGB() == OFF){
				LED.setRGB(static_cast<LEDColor>(LEDColor::RED));
			}else{
				LED.setRGB(OFF);
			}
			if(isDrawing){
				isDrawing = false;
				blinkerCounter++;
			}else{
				isDrawing = true;
			}
			if(blinkerCounter >= 5){
				blinkerCounter = 0;
				previousTimeBlink = 0;
				lostLife = false;
				isDrawing = true;
			}
		}
	}else{
		LED.setRGB(OFF);
	}
	if(livesNum == 0){
		lvl = 1;
		firstTouch = false;
		castleJump->gameOver();
	}

	if(firstTouch){
		if(lavaGif.checkFrame()){
			lavaGif.nextFrame();
		}
	}

	for(int i = 0; i < 1; i++){
		movingCoin(coin[i], time);
		checkForPoint(coin[i]);
		movingPowerUps(powerUp[i], time);
		checkForPowerUp(powerUp[i]);
		movingBrick(bricks[i], time);
		movingWindow(window[i], time);
	}
	if(highspeed || lowGravity){
		powerUpTimer();
	}
}