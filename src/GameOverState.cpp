#include "GameOverState.h"
#include "GameState.h"
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
}

void GameOverState::buttonAPress(){
	instance->aState = true;
}

void GameOverState::buttonARelease(){
	instance->aState = false;
}

void GameOverState::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	score = 0;
}

void GameOverState::drawGameOver(){
	baseSprite->setTextSize(TFT_WHITE);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(2);
	baseSprite->drawString("Your", 3, 20);
	baseSprite->drawString("score", 3, 40);
	baseSprite->drawString("is : ", 3, 60);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(2);
	baseSprite->drawNumber(score - 0, 90, 40);
	baseSprite->setTextSize(1);
	baseSprite->setCursor(110, 110);
	baseSprite->printCenter("A: new game");
	display->commit();


}

void GameOverState::loop(uint time){
	baseSprite->clear(TFT_BLACK);
	drawGameOver();
	if(aState){
		castleJump->changeState(new GameState());
	}
}

