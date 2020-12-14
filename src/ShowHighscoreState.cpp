#include "ShowHighscoreState.h"

#include "Menu.h"

ShowHighscoreState *ShowHighscoreState::instance = nullptr;

ShowHighscoreState::ShowHighscoreState(){

	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();
	instance = this;

}

void ShowHighscoreState::enter(CastleJump &gameEnter){

	castleJump=&gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_A,[](){
		instance->castleJump->changeState(new Menu());
	});
	Input::getInstance()->setBtnPressCallback(BTN_B,[](){
		instance->castleJump->changeState(new Menu());
	});
}
void ShowHighscoreState::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);

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
		if(i <= 6){
			Serial.println(i);
			baseSprite->printf("%d. %.3s ",i,"--");
		}
	}

	display->commit();
}
void ShowHighscoreState::loop(uint time){
	drawHighscore();
}