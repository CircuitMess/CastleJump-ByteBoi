#include "EraseHighscoreState.h"
#include "Highscore/Highscore.h"
#include "Melodies/Notes.hpp"


CastleJump::EraseHighscoreState *CastleJump::EraseHighscoreState::instance = nullptr;

CastleJump::EraseHighscoreState::EraseHighscoreState(Screen* screen) : screen(screen){
	display = ByteBoi.getDisplay();
	baseSprite = screen->getSprite();
	instance = this;

}

void CastleJump::EraseHighscoreState::start(CastleJump &gameEnter){
	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		Highscore.clear();
		instance->castleJump->openHighscores();
		Piezo.tone(NOTE_B6,25);
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->castleJump->openHighscores();
		Piezo.tone(NOTE_B6,25);
	});

}

void CastleJump::EraseHighscoreState::stop(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnReleaseCallback(BTN_B);

}

void CastleJump::EraseHighscoreState::drawWarning(){
	baseSprite->clear(TFT_BLACK);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Your really want", 30, 17);
	baseSprite->drawString("to erase your", 30, 32);
	baseSprite->drawString("highscore list?", 30, 47);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->setCursor(110, 100);
	baseSprite->printCenter("  A: delete     B: back");

}
void CastleJump::EraseHighscoreState::draw(){
	drawWarning();
	screen->commit();

}
void CastleJump::EraseHighscoreState::loop(uint time){

}
