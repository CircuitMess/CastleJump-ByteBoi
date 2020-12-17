#include "ShowHighscoreState.h"
#include "Highscore/Highscore.h"
#include "Menu.h"
#include "EraseHighscoreState.h"
#include "Melodies/Notes.hpp"
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
	baseSprite->setCursor(15, 4);
	baseSprite->setTextSize(1);
	baseSprite->setTextFont(2);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->printCenter("HIGHSCORES");

	for(int i=1;i<6;i++){
		baseSprite->setCursor(6,i*20);
		if(i <= Highscore.count()){
			Serial.println(Highscore.get(i).score);
			baseSprite->printf("%d. %.3s %4d",i,Highscore.get(i-1).name, Highscore.get(i-1).score);
		}
		else
		{
			baseSprite->printf("%d. ---  -----",i);
		}
	}

	display->commit();
}
void ShowHighscoreState::loop(uint time){
	drawHighscore();
}