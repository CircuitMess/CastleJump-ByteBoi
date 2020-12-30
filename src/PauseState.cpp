#include "PauseState.h"
#include <Nibble.h>
#include <Arduino.h>
#include "GameState.h"
#include "GameOverState.h"
#include "Menu.h"

PauseState *PauseState::instance = nullptr;

PauseState::PauseState(){
	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();

	instance = this;
}

void PauseState::enter(CastleJump &gameEnter){
	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		instance->castleJump->resumeGame();

	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		delete instance->castleJump->pausedGameState;
		instance->castleJump->pausedGameState = nullptr;
		instance->castleJump->changeState(new Menu());
	});
}

void PauseState::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);

}


void PauseState::displayMessage(){
	baseSprite->setCursor(32, baseSprite->height() / 2 - 25);
	baseSprite->setTextSize(2);
	baseSprite->setTextFont(2);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->printCenter("PAUSE");
	baseSprite->setTextSize(1);
	baseSprite->setCursor(110, 110);
	baseSprite->printCenter("A: resume   B: quit");
}
void PauseState::draw(){
	displayMessage();
	display->commit();

}

void PauseState::loop(uint time){
	baseSprite->clear(TFT_BLACK);
	display->commit();
}
