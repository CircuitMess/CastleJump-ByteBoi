#include "PauseState.h"
#include <ByteBoi.h>
#include <Arduino.h>
#include "GameState.h"


CastleJump::PauseState *CastleJump::PauseState::instance = nullptr;

CastleJump::PauseState::PauseState(){
	display = ByteBoi.getDisplay();
	baseSprite = display->getBaseSprite();

	instance = this;
}

void CastleJump::PauseState::start(CastleJump &gameEnter){
	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		instance->castleJump->resumeGame();
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		delete instance->castleJump->pausedGameState;
		instance->castleJump->pausedGameState = nullptr;
		instance->castleJump->returnToMenu();
	});
}

void CastleJump::PauseState::stop(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
}


void CastleJump::PauseState::displayMessage(){
	baseSprite->setCursor(32, baseSprite->height() / 2 - 25);
	baseSprite->setTextSize(2);
	baseSprite->setTextFont(2);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->printCenter("    PAUSE");
	baseSprite->setTextSize(1);
	baseSprite->setCursor(110, 100);
	baseSprite->printCenter("   A: resume    B: quit");
}
void CastleJump::PauseState::draw(){
	baseSprite->clear(TFT_BLACK);
	displayMessage();
	display->commit();

}

void CastleJump::PauseState::loop(uint time){

}
