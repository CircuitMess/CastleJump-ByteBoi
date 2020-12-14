#include "GameOverState.h"
#include "GameState.h"
#include "Menu.h"
#include <Nibble.h>
#include <Arduino.h>

GameOverState *GameOverState::instance = nullptr;

GameOverState::GameOverState(int scoreOver){

	score = scoreOver;
	instance = this;
	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();
}

void GameOverState::enter(CastleJump &gameEnter){

	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_A, buttonAPress);
	Input::getInstance()->setBtnPressCallback(BTN_B, buttonBPress);
}

void GameOverState::buttonAPress(){
	instance->aState = true;
}

void GameOverState::buttonBPress(){
	instance->bState = true;
}

void GameOverState::buttonARelease(){
	instance->aState = false;
}

void GameOverState::buttonBRelease(){
	instance->bState = false;
}

void GameOverState::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	score = 0;
}

void GameOverState::drawGameOver(){
	baseSprite->setTextSize(TFT_WHITE);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(3);
	baseSprite->drawString("Game", 30, 20);
	baseSprite->drawString("Over", 30, 40);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Score : ",30,70);
	baseSprite->drawNumber(score - 0, 80, 70);
	baseSprite->setTextSize(1);
	baseSprite->setCursor(110, 110);
	baseSprite->printCenter("A: new game B: menu");
	display->commit();


}

void GameOverState::loop(uint time){
	baseSprite->clear(TFT_BLACK);
	drawGameOver();
	if(aState){
		castleJump->changeState(new GameState());
	}
	if(bState){
		castleJump->changeState(new Menu());
	}
}

