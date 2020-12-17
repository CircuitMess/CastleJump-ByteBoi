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

	ability.push_back({50, -1800, 2, TFT_BLUE});

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
	baseSprite->drawIcon(icon_player,player.pos.x, player.pos.y,8,8 );
}

void GameState::drawCoin(Coin &goldenCoin){
	baseSprite->drawIcon(icon_coin,goldenCoin.x, goldenCoin.y, 5,5);
}

void GameState::drawRect(Rect &stairs){
	baseSprite->fillRect(stairs.x, stairs.y, stairs.w, stairs.h, TFT_RED);
}

void GameState::drawAbilityPoint(PowerUps &ability){
	baseSprite->drawIcon(power_up,ability.x, ability.y, 5,5);
}
void GameState::drawWalls(){
	baseSprite->drawIcon(leftWall,0,0,5,128);
	baseSprite->drawIcon(rightWall,123,0,5,128);

}
void GameState::drawFloor(){
	baseSprite->drawIcon(icon_floor,0,118,128,10);
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
		float randX = stairs.x;
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
		Piezo.tone(NOTE_B5,100);
		Piezo.tone(NOTE_E6,150);
		score = score + 5;
		goldenCoin.y = -700;
		float randX = goldenCoin.x;
		do {
			goldenCoin.y = -700;
			randX = random(10, 110);
		} while(abs(randX - goldenCoin.x > 30));
		goldenCoin.x = randX;
	}
}

void GameState::checkForPowerUp(PowerUps &ability){
	if(abs(player.pos.x - ability.x) == 0 && abs((player.pos.y - ability.y) == 0) ||
	   (abs(player.pos.x - ability.x) + abs((player.pos.y - ability.y))) <= 5){
		int randNum = random(1, 3);
		if(randNum == 1){
			highspeed = true;
		}
		if(randNum == 2){
			lowGravity = true;
		}
		ability.y = -1800;
		float randX = ability.x;
		do {
			ability.y = -1800;
			randX = random(10, 110);
		} while(abs(randX - ability.x > 30));
		ability.x = randX;
	}
}

void GameState::checkForCollision(Rect &stairs){
	if(player.velocity.y < 0){
		return;
	}

	if(stairs.w == 20){
		float distX = abs(player.pos.x - stairs.x - 10);
		float distY = abs(player.pos.y - stairs.y - 1);
		if((distX <= 11 && distY <= 4)){

			player.velocity.y = -min(player.velocity.y, 200.0f);
			firstTouch = true;
		}


	}
	if(stairs.w == 40){
		float distX = abs(player.pos.x - stairs.x - 20);
		float distY = abs(player.pos.y - stairs.y - 1);
		if((distX <= 21 && distY <= 4)){

			player.velocity.y = -min(player.velocity.y, 200.0f);
			firstTouch = true;
		}

	}
	if(stairs.w == 10){
		float distX = abs(player.pos.x - stairs.x - 5);
		float distY = abs(player.pos.y - stairs.y - 1);
		if((distX <= 6 && distY <= 4)){

			player.velocity.y = -min(player.velocity.y, 200.0f);
			firstTouch = true;
		}

	}
}

void GameState::scoreTable(){
	baseSprite->setTextColor(TFT_RED);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Score:", 3, 1);
	baseSprite->drawNumber(score - 0, 38, 1);
}

void GameState::powerUpTimer(){
	baseSprite->setTextColor(TFT_BLUE);
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
	baseSprite->setTextColor(TFT_RED);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Lvl: ", 58, 1);
	baseSprite->drawNumber(lvl - 0, 83, 1);
}

void GameState::lives(){
	baseSprite->setTextColor(TFT_RED);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->drawString("X", 103, 1);
	baseSprite->drawNumber(livesNum - 0, 110, 1);
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
	float dt = (float) time / 1000000.0f;
	baseSprite->clear(TFT_BLACK);
	velocity(dt);
	for(int i = 0; i < dropRect.size(); ++i){
		checkForCollision(dropRect[i]);
	}
	if(player.pos.y > 115){
		player.pos.y = 115;
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
	xPosMoving();
	drawPlayerCircle();
	drawWalls();
	drawFloor();
	for(int i = 0; i < 1; i++){
		drawCoin(coin[0]);
		movingCoin(coin[0], time);
		checkForPoint(coin[0]);
	}
	scoreTable();

	for(int i = 0; i < dropRect.size(); ++i){
		movingRects(dropRect[i], time);
		drawRect(dropRect[i]);

	}
	for(int i = 0; i < 1; i++){
		drawAbilityPoint(ability[i]);
		movingPowerUps(ability[i], time);
		checkForPowerUp(ability[i]);
	}
	if(highspeed || lowGravity){
		powerUpTimer();
	}
	levelCounter();
	level();
	checkLevel();
	lives();


	display->commit();
}