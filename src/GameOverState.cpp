#include "GameOverState.h"
#include "Highscore/Highscore.h"
#include <Nibble.h>
#include <Arduino.h>
#include "Melodies/Notes.hpp"
#include "bitmaps/game_over.hpp"

CastleJump::GameOverState *CastleJump::GameOverState::instance = nullptr;

CastleJump::GameOverState::GameOverState(){


	instance = this;
	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();
	score =0 ;
}

void CastleJump::GameOverState::start(CastleJump &gameEnter){

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
	Piezo.setMute(true);
}

void CastleJump::GameOverState::drawGameOver(){
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->drawIcon(game_over, 0, 0, 128, 128);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Score : ", 35, 30);
	baseSprite->drawNumber(castleJump->score -0, 85, 30);
	baseSprite->setTextSize(1);
	baseSprite->setCursor(110, 1);
	baseSprite->printCenter("A: new game B: menu");
	display->commit();

}

void CastleJump::GameOverState::draw(){

}

void CastleJump::GameOverState::loop(uint time){
	Serial.println("castleJump->score :");
	score=castleJump->score;
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

