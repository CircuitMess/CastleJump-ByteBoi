//
// Created by hrvoj on 01/12/2020.
//
#include <Nibble.h>
#include <Arduino.h>
#include "GameState.h"

GameState *GameState::instance = nullptr;

GameState::GameState(){

	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();

	instance = this;

	player.pos.x = 66;
	player.pos.y = 66;
	player.velocity.x = 0;
	player.velocity.y = 0;

	dropRect.push_back({0, 0, 20, 2});

}

void GameState::enter(CastleJump &gameEnter){

	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_RIGHT, buttonRightPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_RIGHT, buttonRightRelease);
	Input::getInstance()->setBtnPressCallback(BTN_LEFT, buttonLeftPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_LEFT, buttonLeftRelease);

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

void GameState::drawPlayerCircle(){
	baseSprite->fillCircle(player.pos.x, player.pos.y, 4, TFT_WHITE);

}

void GameState::drawRect(Rect &stairs){
	baseSprite->fillRect(stairs.x, stairs.y, stairs.w, stairs.h, TFT_RED);

}

void GameState::functionForRects(Rect &stairs){
	for(int i = 0; i < dropRect.size(); i++){
		drawRect(dropRect[i]);
		if(dropRect.size() == 1 && stairs.y > 40){
			dropRect.push_back({0, 0, 40, 2});
		}
		if(dropRect.size() == 2 && stairs.y > 120){
			dropRect.push_back({0, 0, 10, 2});
		}
	}
}

void GameState::xPosMoving(){
	if(rightState){
		player.velocity.x = 30 ;
	}

	if(player.pos.x > 118){
		player.pos.x = 118;

		player.velocity.x = -50;
	}
	if(player.pos.x < 10){
		player.pos.x = 10;

		player.velocity.x = 50;
	}

	if(leftState){
		player.velocity.x = -30 ;

	}

}


void GameState::movingRects(Rect &stairs, uint b){

	stairs.y += 1.2 * speed * b / 13000;

	if(stairs.y > 126){
		stairs.y = 0;

		randX = random(110);
		if(randX - stairs.x < 30 || randX - stairs.x < 50){
			stairs.x = randX;
		}
	}

}


void GameState::velocity(float dt){
	player.pos += player.velocity * dt;
	player.velocity += gravity * dt;


}


void GameState::yBouncing(){
	/*if(player.y > 10 && player.y < 118){
		player.y += s;
	}*/

}


void GameState::checkForCollision(Rect &stairs){
	float distX = abs(player.pos.x - stairs.x - 10);
	float distY = abs(player.pos.y - stairs.y - 1);
	if(distX <= 11 && distY <= 4){
		player.velocity.y = -min(player.velocity.y, 150.0f);
	}

}


void GameState::loop(uint time){
	float dt = (float) time / 1000000.0f;
	baseSprite->clear(TFT_BLACK);
	velocity(dt);
	for(int i = 0; i < dropRect.size(); ++i){
		checkForCollision(dropRect[i]);
	}
	if(player.pos.y > 118){
		player.pos.y = 118;

		player.velocity.y = -min(player.velocity.y, 100.0f);
	}
	/*
	if(player.pos.x < 10){
		player.pos.x = 10;
		leftState = false;
		player.velocity.x = -player.velocity.x;

	}*/
	xPosMoving();

	yBouncing();
	drawPlayerCircle();

	for(int i = 0; i < dropRect.size(); ++i){
		drawRect(dropRect[i]);
		functionForRects(dropRect[i]);
		movingRects(dropRect[i], time);
	}
	display->commit();
}

