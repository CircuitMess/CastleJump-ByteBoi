#include "EraseHighscoreState.h"
#include "Highscore/Highscore.h"
#include "ShowHighscoreState.h"
#include "Melodies/Notes.hpp"


EraseHighscoreState *EraseHighscoreState::instance = nullptr;

EraseHighscoreState::EraseHighscoreState(){

	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();
	instance = this;

}

void EraseHighscoreState::enter(CastleJump &gameEnter){
	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		Highscore.clear();
		instance->castleJump->changeState(new ShowHighscoreState());
		Piezo.tone(NOTE_B6,25);
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->castleJump->changeState(new ShowHighscoreState());
		Piezo.tone(NOTE_B6,25);
	});
}

void EraseHighscoreState::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnReleaseCallback(BTN_B);

}

void EraseHighscoreState::drawWarning(){
	baseSprite->clear(TFT_BLACK);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Your really want", 15, 17);
	baseSprite->drawString("to erase your", 15, 32);
	baseSprite->drawString("highscore list?", 15, 47);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->setCursor(110, 110);
	baseSprite->printCenter("A: delete  B: back");

}
void EraseHighscoreState::loop(uint time){
	baseSprite->clear(TFT_BLACK);
	drawWarning();
	display->commit();
}
