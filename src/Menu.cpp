#include "Menu.h"
#include <Nibble.h>
#include <Arduino.h>
#include "GameState.h"
#include "ShowHighscoreState.h"

Menu *Menu::instance = nullptr;

Menu::Menu(){

	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();

	instance = this;

	menuSelect.x = 25;
	menuSelect.y = 73;
	menuSelect.color = TFT_RED;

	display->commit();
}
void Menu::enter(CastleJump &gameEnter){

	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_A, buttonAPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_A, buttonARelease);
	Input::getInstance()->setBtnPressCallback(BTN_UP, buttonUpPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_UP, buttonUpRelease);
	Input::getInstance()->setBtnPressCallback(BTN_DOWN, buttonDownPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_DOWN, buttonDownRelease);

}
void Menu::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_UP);
	Input::getInstance()->removeBtnPressCallback(BTN_DOWN);
}
void Menu::buttonAPress(){
	instance->aState = true;

}

void Menu::buttonARelease(){
	instance->aState = false;

}
void Menu::buttonUpPress(){
	instance->upState = true;

}

void Menu::buttonUpRelease(){
	instance->upState = false;

}

void Menu::buttonDownPress(){
	instance->downState = true;

}

void Menu::buttonDownRelease(){
	instance->downState = false;

}
void Menu::drawSelection(MenuSelection &menuSelect){
	baseSprite->drawRect(menuSelect.x,menuSelect.y,70,16,menuSelect.color);
}
void Menu::checkStateAndMove(MenuSelection &menuSelect){
	if (upState){
		menuSelect.y=73;
		checkState=false;
	}
	if (downState){
		menuSelect.y=93;
		checkState=true;
	}
}
void Menu::drawMenuScreen(){
	baseSprite->clear(TFT_BLACK);
	baseSprite->setTextColor(TFT_RED);
	baseSprite->setTextFont(1);
	baseSprite->setTextSize(2);
	baseSprite->drawString("CastleJump", 8, 17);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->drawString("New game", 30, 71);
	baseSprite->drawString("Highscore", 30, 91);
}
void Menu::loop(uint time){
	baseSprite->clear(TFT_BLACK);
	drawMenuScreen();
	drawSelection(menuSelect);
	checkStateAndMove(menuSelect);
	if(aState && !checkState){
		castleJump->changeState(new GameState());
	}
	if(aState && checkState){
		castleJump->changeState(new ShowHighscoreState());
	}
	display->commit();
}