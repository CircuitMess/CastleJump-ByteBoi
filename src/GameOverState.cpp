#include "GameOverState.h"
#include "Highscore/Highscore.h"
#include <ByteBoi.h>
#include <Arduino.h>
#include "Melodies/Notes.hpp"
#include "bitmaps/game_over160x128.hpp"

CastleJump::GameOverState* CastleJump::GameOverState::instance = nullptr;

CastleJump::GameOverState::GameOverState(Screen* screen) : screen(screen){
	display = ByteBoi.getDisplay();
	baseSprite = screen->getSprite();

	instance = this;
	score = 0;
}

void CastleJump::GameOverState::start(CastleJump& gameEnter){

	castleJump = &gameEnter;
	score = castleJump->score;

	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		instance->castleJump->enterHighscore();
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->castleJump->enterHighscore();
	});
	Input::getInstance()->setBtnPressCallback(BTN_UP, [](){
		instance->castleJump->enterHighscore();
	});
	Input::getInstance()->setBtnPressCallback(BTN_DOWN, [](){
		instance->castleJump->enterHighscore();
	});
	Input::getInstance()->setBtnPressCallback(BTN_LEFT, [](){
		instance->castleJump->enterHighscore();
	});
	Input::getInstance()->setBtnPressCallback(BTN_RIGHT, [](){
		instance->castleJump->enterHighscore();
	});

}


void CastleJump::GameOverState::stop(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnPressCallback(BTN_UP);
	Input::getInstance()->removeBtnPressCallback(BTN_DOWN);
	Input::getInstance()->removeBtnPressCallback(BTN_LEFT);
	Input::getInstance()->removeBtnPressCallback(BTN_RIGHT);
}

void CastleJump::GameOverState::drawGameOver(){
	baseSprite->drawIcon(game_over1, 0, -4, 160, 128);
	/*baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Score : ", 45, 30);
	baseSprite->drawNumber(castleJump->score - 0, 95, 30);
	baseSprite->setTextSize(1);
	*/
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(1);
	baseSprite->setCursor(0, 5);
	baseSprite->printCenter("Press any key to continue.");
	screen->commit();

}

void CastleJump::GameOverState::draw(){
//	drawGameOver();
}

void CastleJump::GameOverState::loop(uint time){

	previousTime = 0;
	currentTime = millis();
	if(currentTime - previousTime > 1000){
		previousTime = currentTime;
		seconds++;
		if(seconds < 2){
			melody.play(MelodyImpl::dead, false);
		}
		drawGameOver();
	}

}

