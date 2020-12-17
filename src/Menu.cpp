#include "Menu.h"
#include <Nibble.h>
#include <Arduino.h>
#include "GameState.h"
#include "ShowHighscoreState.h"
#include "Melodies/Notes.hpp"
#include "bitmaps/player.hpp"
#include "bitmaps/home_screen.hpp"

Menu *Menu::instance = nullptr;

Menu::Menu(){

	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();

	instance = this;

	menuSelect.x = 20;
	menuSelect.y = 100;
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
	Input::getInstance()->setBtnPressCallback(BTN_LEFT, buttonDownPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_LEFT, buttonDownRelease);
	Input::getInstance()->setBtnPressCallback(BTN_RIGHT, buttonUpPress);
	Input::getInstance()->setBtnReleaseCallback(BTN_RIGHT, buttonUpRelease);


}

void Menu::exit(){

	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_UP);
	Input::getInstance()->removeBtnReleaseCallback(BTN_UP);
	Input::getInstance()->removeBtnPressCallback(BTN_DOWN);
	Input::getInstance()->removeBtnReleaseCallback(BTN_DOWN);
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
	baseSprite->drawIcon(icon_player,menuSelect.x, menuSelect.y, 8,8);
}

void Menu::checkStateAndMove(MenuSelection &menuSelect){
	if(upState){

		menuSelect.y = 100;
		checkState = false;
	}
	if(downState){

		menuSelect.y = 115;
		checkState = true;
	}
}

void Menu::drawMenuScreen(){
	baseSprite->clear(TFT_BLACK);
	baseSprite->drawIcon(homescreen,0,0,128,128);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->drawString("New game", 30, 96);
	baseSprite->drawString("Highscore", 30, 111);
}

void Menu::loop(uint time){
	baseSprite->clear(TFT_BLACK);
	drawMenuScreen();
	drawSelection(menuSelect);
	checkStateAndMove(menuSelect);
	if(aState && !checkState){
		Piezo.tone(NOTE_B6,25);
		castleJump->changeState(new GameState());
	}
	if(aState && checkState){
		Piezo.tone(NOTE_B6,25);
		castleJump->changeState(new ShowHighscoreState());
	}
	display->commit();
}