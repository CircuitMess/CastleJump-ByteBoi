#include "EraseHighscoreState.h"
#include "Highscore/Highscore.h"
#include "Melodies/Notes.hpp"


CastleJump::EraseHighscoreState *CastleJump::EraseHighscoreState::instance = nullptr;

CastleJump::EraseHighscoreState::EraseHighscoreState(){

	display = ByteBoi.getDisplay();
	baseSprite = display->getBaseSprite();
	instance = this;

}

void CastleJump::EraseHighscoreState::start(CastleJump &gameEnter){
	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		Highscore.clear();
		instance->castleJump->openHighscores();
		//	Piezo.tone(NOTE_B6,25);
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->castleJump->openHighscores();
		//	Piezo.tone(NOTE_B6,25);
	});

}

void CastleJump::EraseHighscoreState::stop(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnReleaseCallback(BTN_B);
	//Piezo.setMute(true);
}

void CastleJump::EraseHighscoreState::drawWarning(){
	baseSprite->clear(TFT_BLACK);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->drawString("   Your really want", 15, 17);
	baseSprite->drawString("   to erase your", 15, 32);
	baseSprite->drawString("   highscore list?", 15, 47);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->setCursor(110, 100);
	baseSprite->printCenter("  A: delete     B: back");

}
void CastleJump::EraseHighscoreState::draw(){
	drawWarning();
	display->commit();

}
void CastleJump::EraseHighscoreState::loop(uint time){

}
