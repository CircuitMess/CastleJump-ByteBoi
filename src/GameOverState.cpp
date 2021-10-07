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
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		Piezo.tone(NOTE_B6, 25);
		instance->castleJump->newGame();
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
			Piezo.tone(NOTE_B6, 25);
		instance->castleJump->returnToMenu();
	});
}


void CastleJump::GameOverState::stop(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_B);
}

void CastleJump::GameOverState::drawGameOver(){
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->drawIcon(game_over1, 0, 0, 160, 128);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Score : ", 45, 30);
	baseSprite->drawNumber(castleJump->score - 0, 95, 30);
	baseSprite->setTextSize(1);
	baseSprite->setCursor(130, 1);
	baseSprite->printCenter("  A: new game  B: menu");
	screen->commit();

}

void CastleJump::GameOverState::draw(){

}

void CastleJump::GameOverState::loop(uint time){
	Serial.println("castleJump->score :");
	score = castleJump->score;
	if(Highscore.count() > 1){
		initialValue = false;
	}
	if(score > Highscore.get(0).score || initialValue || score > Highscore.get(1).score ||
	   score > Highscore.get(2).score || score > Highscore.get(3).score ||
	   score >= Highscore.get(4).score){
		Serial.println(Highscore.get(0).score);
		castleJump->enterHighscore();
	}else{
		if(Highscore.get(4).score > score && Highscore.count() > 1){
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
	}
}

