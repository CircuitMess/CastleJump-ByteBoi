#include <Nibble.h>
#include <Arduino.h>
#include "GameState.h"
#include "GameOverState.h"
#include "Melodies/Notes.hpp"
#include "bitmaps/player.hpp"
#include "bitmaps/coin.hpp"
#include "bitmaps/power_up.hpp"
#include "bitmaps/leftWall.hpp"
#include "bitmaps/rightWall.hpp"
#include "bitmaps/floor.hpp"
#include "bitmaps/platform1_1.hpp"
#include "bitmaps/platform1_2.hpp"
#include "bitmaps/platform1_4.hpp"
#include "bitmaps/platform2_1.hpp"
#include "bitmaps/platform2_2.hpp"
#include "bitmaps/platform2_4.hpp"
#include "bitmaps/platform3_1.hpp"
#include "bitmaps/platform3_2.hpp"
#include "bitmaps/platform3_4.hpp"
#include "bitmaps/lava.hpp"
#include "bitmaps/heart/heart1.hpp"
#include "bitmaps/heart/heart2.hpp"
#include "bitmaps/heart/heart3.hpp"
#include "bitmaps/heart/heart4.hpp"
#include "bitmaps/heart/heart5.hpp"
#include "bitmaps/heart/heart6.hpp"
#include "bitmaps/heart/heart7.hpp"
#include "bitmaps/heart/heart8.hpp"
#include "bitmaps/heart/heart9.hpp"
#include "bitmaps/heart/heart10.hpp"
#include "bitmaps/heart/heart11.hpp"


GameState *GameState::instance = nullptr;

GameState::GameState(){

	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();

	instance = this;


	player.pos.x = 66;
	player.pos.y = 66;
	player.velocity.x = 0;
	player.velocity.y = 0;

	coin.push_back({50, -700, 2, TFT_GOLD});

	powerUp.push_back({50, -1800, 2, TFT_BLUE});

	dropRect.push_back({40, 0, 20, 2});
	dropRect.push_back({80, -20, 40, 2});
	dropRect.push_back({70, -45, 20, 2});
	dropRect.push_back({20, -65, 10, 2});
	dropRect.push_back({60, -85, 20, 2});
	dropRect.push_back({80, -105, 40, 2});


}

void GameState::enter(CastleJump &gameEnter){

	castleJump = &gameEnter;

	for(int i = 0; i < dropRect.size(); ++i){
		dropRect[i].x;
		dropRect[i].y;
		Serial.println("x:");
		Serial.println(dropRect[i].x);
		Serial.println("y:");
		Serial.println(dropRect[i].y);

	}
	Input::getInstance()->setBtnPressCallback(BTN_RIGHT, buttonRightPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_RIGHT, buttonRightRelease);
	Input::getInstance()->setBtnPressCallback(BTN_LEFT, buttonLeftPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_LEFT, buttonLeftRelease);
	Input::getInstance()->setBtnPressCallback(BTN_B, buttonBPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_B, buttonBRelease);

}

void GameState::exit(){
	for(int i = 0; i < dropRect.size(); i++){
		dropRect.pop_back();

	}
	Input::getInstance()->removeBtnPressCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnPressCallback(BTN_LEFT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_LEFT);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnReleaseCallback(BTN_B);
}

void GameState::buttonLeftPress(){
	instance->leftState = true;


}

void GameState::buttonLeftRelease(){
	instance->leftState = false;

}

void GameState::buttonRightPress(){
	instance->rightState = true;

}

void GameState::buttonRightRelease(){
	instance->rightState = false;

}

void GameState::buttonBPress(){
	instance->bState = true;

}

void GameState::buttonBRelease(){

	instance->bState = false;


}

void GameState::drawPlayerCircle(){
	baseSprite->drawIcon(icon_player, player.pos.x, player.pos.y, 8, 8);
}

void GameState::drawCoin(Coin &goldenCoin){
	baseSprite->drawIcon(icon_coin, goldenCoin.x, goldenCoin.y, 5, 5);
}

void GameState::drawRect(Rect &stairs){
	if(lvl == 1 && stairs.w == 10){
		baseSprite->drawIcon(icon_platform1_1, stairs.x, stairs.y, stairs.w, stairs.h);
	}else if(lvl == 1 && stairs.w == 20){
		baseSprite->drawIcon(icon_platform1_2, stairs.x, stairs.y, stairs.w, stairs.h);
	}else if(lvl == 1 && stairs.w == 40){
		baseSprite->drawIcon(icon_platform1_4, stairs.x, stairs.y, stairs.w, stairs.h);
	}else if(lvl == 2 && stairs.w == 10){
		baseSprite->drawIcon(icon_platform2_1, stairs.x, stairs.y, stairs.w, stairs.h);
	}else if(lvl == 2 && stairs.w == 20){
		baseSprite->drawIcon(icon_platform2_2, stairs.x, stairs.y, stairs.w, stairs.h);
	}else if(lvl == 2 && stairs.w == 40){
		baseSprite->drawIcon(icon_platform2_4, stairs.x, stairs.y, stairs.w, stairs.h);
	}else if(lvl == 3 && stairs.w == 10){
		baseSprite->drawIcon(icon_platform3_1, stairs.x, stairs.y, stairs.w, stairs.h);
	}else if(lvl == 3 && stairs.w == 20){
		baseSprite->drawIcon(icon_platform3_2, stairs.x, stairs.y, stairs.w, stairs.h);
	}else if(lvl == 3 && stairs.w == 40){
		baseSprite->drawIcon(icon_platform3_4, stairs.x, stairs.y, stairs.w, stairs.h);
	}
}

void GameState::drawAbilityPoint(PowerUps &ability){
	baseSprite->drawIcon(power_up, ability.x, ability.y, 5, 5);
}

void GameState::drawWalls(){
	baseSprite->drawIcon(leftWall, 0, 0, 5, 128);
	baseSprite->drawIcon(rightWall, 123, 0, 5, 128);

}

void GameState::drawFloor(){
	if(!firstTouch){
		baseSprite->drawIcon(icon_floor, 0, 118, 128, 10);
	}else if(firstTouch){
		baseSprite->drawIcon(icon_lava, 0, 118, 128, 10);

	}
}


void GameState::xPosMoving(){
	if(player.pos.x > 115){
		checkWallBump = true;
		rightState = false;
		player.pos.x = 115;
		player.velocity.x = -100;
	}
	if(player.pos.x < 5){
		checkWallBump = true;
		leftState = false;
		player.pos.x = 5;
		player.velocity.x = 100;
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

void GameState::movingRects(Rect &stairs, uint b){
	if(!highspeed){
		stairs.y += 0.6 * speed * b / 13000;
	}
	if(highspeed){
		stairs.y += 0.8 * speed * b / 13000;
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
			randX = random(10, 110);
		} while(abs(randX - stairs.x > 30));
		stairs.x = randX;
	}
}


void GameState::velocity(float dt){
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


void GameState::checkForPoint(Coin &goldenCoin){
	if(abs(player.pos.x - goldenCoin.x) == 0 && abs((player.pos.y - goldenCoin.y) == 0) ||
	   (abs(player.pos.x - goldenCoin.x) + abs((player.pos.y - goldenCoin.y))) <= 5){
		Piezo.tone(NOTE_B5, 100);
		Piezo.tone(NOTE_E6, 150);
		score = score + 5;
		goldenCoin.y = -700;
		float randX;
		do {
			goldenCoin.y = -700;
			randX = random(10, 110);
		} while(abs(randX - goldenCoin.x > 30));
		goldenCoin.x = randX;
	}
}

void GameState::checkForPowerUp(PowerUps &powerUp){
	if(abs(player.pos.x - powerUp.x) == 0 && abs((player.pos.y - powerUp.y) == 0) ||
	   (abs(player.pos.x - powerUp.x) + abs((player.pos.y - powerUp.y))) <= 5){
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
			randX = random(10, 110);
		} while(abs(randX - powerUp.x > 30));
		powerUp.x = randX;
	}
}

void GameState::checkForCollision(Rect &stairs){
	if(player.velocity.y < 0){
		return;
	}

	if(stairs.w == 20){
		float distX = abs(player.pos.x - stairs.x - 10);
		float distY = abs(player.pos.y - stairs.y - 1);
		if((distX <= 11 && distY <= 5)){

			player.velocity.y = -min(player.velocity.y, 200.0f);
			firstTouch = true;
		}


	}
	if(stairs.w == 40){
		float distX = abs(player.pos.x - stairs.x - 20);
		float distY = abs(player.pos.y - stairs.y - 1);
		if((distX <= 21 && distY <= 5)){

			player.velocity.y = -min(player.velocity.y, 200.0f);
			firstTouch = true;
		}

	}
	if(stairs.w == 10){
		float distX = abs(player.pos.x - stairs.x - 5);
		float distY = abs(player.pos.y - stairs.y - 1);
		if((distX <= 6 && distY <= 5)){

			player.velocity.y = -min(player.velocity.y, 200.0f);
			firstTouch = true;
		}

	}
}

void GameState::scoreTable(){
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Score:", 6, 1);
	baseSprite->drawNumber(score - 0, 44, 1);
}

void GameState::powerUpTimer(){
	baseSprite->setTextColor(TFT_GREEN);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->drawNumber(seconds - 0, 10, 110);
}

void GameState::levelCounter(){
	if(score >= 100){
		lvl = 2;
	}
	if(score >= 200){
		lvl = 3;
	}
}

void GameState::level(){
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Lvl: ", 63, 1);
	baseSprite->drawNumber(lvl - 0, 89, 1);
}

void GameState::lives(){
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->drawString("x", 109, 1);
	baseSprite->drawNumber(livesNum - 0, 115, 1);
}


void GameState::movingCoin(Coin &goldenCoin, uint b){
	goldenCoin.y += 1.1 * speed * b / 13000;
	if(goldenCoin.y > 117){
		float randX = goldenCoin.x;
		do {
			goldenCoin.y = -700;
			randX = random(10, 110);
		} while(abs(randX - goldenCoin.x > 30));
		goldenCoin.x = randX;
	}
}

void GameState::movingPowerUps(PowerUps &ability, uint b){
	ability.y += 1.1 * speed * b / 13000;
	if(ability.y > 117){
		float randX;
		do {
			ability.y = -1800;
			randX = random(10, 110);
		} while(abs(randX - ability.x) > 30);
		ability.x = randX;
	}
}

void GameState::checkLevel(){
	if(lvl == 1){
		speed = 1;
	}
	if(lvl == 2){
		speed = 1.2;
	}
	if(lvl == 3){
		speed = 1.7;
	}
}


void GameState::loop(uint time){
	baseSprite->clear(TFT_BLACK);
	scoreTable();
	xPosMoving();
	drawPlayerCircle();
	drawWalls();
	drawFloor();
	levelCounter();
	level();
	checkLevel();
	lives();
	float dt = (float) time / 1000000.0f;
	velocity(dt);
	if(player.pos.y<0){
		float delta=-player.pos.y;
		player.pos.y=0;
		for(int i = 0; i < dropRect.size(); ++i){
			dropRect[i].y-=delta;
			speed=speed+0.1;
		}
	}
	for(int i = 0; i < dropRect.size(); ++i){
		movingRects(dropRect[i], time);
		drawRect(dropRect[i]);
		checkForCollision(dropRect[i]);
	}
	if(!firstTouch && player.pos.y > 112){
		player.pos.y = 112;
		Piezo.tone(NOTE_E5, 100);
		player.velocity.y = -min(player.velocity.y, 200.0f);
	}
	if(firstTouch && player.pos.y > 120){
		player.pos.y = 120;
		Piezo.tone(NOTE_E5, 100);
		if(firstTouch){
			if(livesNum > 0){
				livesNum--;
				Piezo.tone(NOTE_E2, 100);
			}

		}
		player.velocity.y = -min(player.velocity.y, 200.0f);
	}
	if(livesNum == 0){
		Piezo.tone(NOTE_E2, 500);
		lvl = 1;
		firstTouch = false;
		castleJump->changeState(new GameOverState(score));
	}
	if(bState){
		castleJump->pauseGame();
	}

	for(int i = 0; i < 1; i++){
		drawCoin(coin[i]);
		movingCoin(coin[i], time);
		checkForPoint(coin[i]);
		drawAbilityPoint(powerUp[i]);
		movingPowerUps(powerUp[i], time);
		checkForPowerUp(powerUp[i]);
	}
	if(highspeed || lowGravity){
		powerUpTimer();
	}

	display->commit();
}