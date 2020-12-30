#include "GameOverState.h"
#include "GameState.h"
#include "Menu.h"
#include "Highscore/Highscore.h"
#include <Nibble.h>
#include <Arduino.h>
#include "EnterHighscoreState.h"
#include "Melodies/Notes.hpp"
#include "bitmaps/game_over.hpp"

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
	//Piezo.setMute(false);
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
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_B);
	score = 0;
	Piezo.setMute(true);
}

void GameOverState::drawGameOver(){
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->drawIcon(game_over,0,0,128,128);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Score : ",35,30);
	baseSprite->drawNumber(score - 0, 85, 30);
	baseSprite->setTextSize(1);
	baseSprite->setCursor(110, 1);
	baseSprite->printCenter("A: new game B: menu");
	display->commit();

}

void GameOverState::draw(){
	display->commit();

}

void GameOverState::loop(uint time){
	baseSprite->clear(TFT_BLACK);
	if(Highscore.count() > 1){
		initialValue = false;
	}
	if(score > Highscore.get(0).score || initialValue || score > Highscore.get(1).score ||
	   score > Highscore.get(2).score || score > Highscore.get(3).score ||
	   score >= Highscore.get(4).score){
		Serial.println(Highscore.get(0).score);
		castleJump->changeState(new EnterHighscoreState(score));
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
			if(aState){
				Piezo.tone(NOTE_B6, 25);
				castleJump->changeState(new GameState());
			}
			if(bState){
				Piezo.tone(NOTE_B6, 25);
				castleJump->changeState(new Menu());
			}
		}
	}
}

