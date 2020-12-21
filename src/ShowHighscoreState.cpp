#include "ShowHighscoreState.h"
#include "Highscore/Highscore.h"
#include "Menu.h"
#include "EraseHighscoreState.h"
#include "Melodies/Notes.hpp"
#include "bitmaps/highscore.hpp"
ShowHighscoreState *ShowHighscoreState::instance = nullptr;

ShowHighscoreState::ShowHighscoreState(){

	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();
	instance = this;

}

void ShowHighscoreState::enter(CastleJump &gameEnter){

	castleJump=&gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_UP,[](){
		Piezo.tone(NOTE_B7,100);
		instance->castleJump->changeState(new EraseHighscoreState());
	});
	Input::getInstance()->setBtnPressCallback(BTN_A,[](){
		Piezo.tone(NOTE_B6,25);
		instance->castleJump->changeState(new Menu());
	});
	Input::getInstance()->setBtnPressCallback(BTN_B,[](){
		Piezo.tone(NOTE_B6,25);
		instance->castleJump->changeState(new Menu());
	});
	Piezo.setMute(true);
}
void ShowHighscoreState::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnReleaseCallback(BTN_B);
	Input::getInstance()->removeBtnPressCallback(BTN_UP);
	Input::getInstance()->removeBtnReleaseCallback(BTN_UP);

}
void ShowHighscoreState::drawHighscore(){
	baseSprite->clear(TFT_BLACK);
	baseSprite->drawIcon(high_score,0,0,128,128);
	for(int i=0;i<5;i++){
		baseSprite->setTextColor(TFT_WHITE);
		baseSprite->setCursor(43,(i*16)+37);
		baseSprite->setTextSize(1);
		baseSprite->setTextFont(1);
		if((i+1) <= Highscore.count()){
			Serial.println(Highscore.get(i).score);
			baseSprite->printf("%.3s  %4d",Highscore.get(i).name, Highscore.get(i).score);
		}
	}

	display->commit();
}
void ShowHighscoreState::loop(uint time){
	drawHighscore();
}