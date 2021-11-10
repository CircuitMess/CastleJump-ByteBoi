#include "Menu.h"
#include <ByteBoi.h>
#include <Arduino.h>
#include <FS.h>
#include <FS/CompressedFile.h>
#include <SPIFFS.h>
#include "Melodies/Notes.hpp"
#include "bitmaps/player.hpp"
#include "bitmaps/home_screen.hpp"

const char *CastleJump::Menu::titleMenu[3] = {"Start", "Highscore", "Quit"};
CastleJump::Menu *CastleJump::Menu::instance = nullptr;

CastleJump::Menu::Menu(Screen* screen) : screen(screen){
	display = ByteBoi.getDisplay();
	baseSprite = screen->getSprite();
	instance = this;
	titleCursor = 0;
	blinkState = 0;
	blinkMicros = 0;
	display->commit();

	backgroundBuffer = static_cast<Color*>(ps_malloc(160 * 120 * 2));
	if(backgroundBuffer == nullptr){
		return;
	}

	fs::File backgroundFile = CompressedFile::open(ByteBoi.openResource("/Homescreen.raw.hs"),13,12);

	backgroundFile.read(reinterpret_cast<uint8_t*>(backgroundBuffer), 160 * 120 * 2);
	backgroundFile.close();
}

CastleJump::Menu::~Menu(){
	Menu::stop();
	free(backgroundBuffer);
}

void CastleJump::Menu::start(CastleJump &gameEnter){

	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_LEFT, [](){
		if(instance->titleCursor > 0){
			instance->titleCursor--;

		}
	});
	Input::getInstance()->setBtnPressCallback(BTN_RIGHT, [](){
		if(instance->titleCursor < 2){
			instance->titleCursor++;

		}
	});
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		switch (instance->titleCursor)
		{
			case 0:
				instance->castleJump->newGame();
				break;

			case 1:
				instance->castleJump->openHighscores();
				break;
			case 2:
				Playback.stop();
				ByteBoi.backToLauncher();
				break;
		}
	});

	extern Sample* menuMusic;
	Playback.play(menuMusic);
}

void CastleJump::Menu::stop(){

	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_LEFT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_LEFT);
	Input::getInstance()->removeBtnPressCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_RIGHT);
	Playback.stop();
}

void CastleJump::Menu::draw(){
	baseSprite->drawIcon(backgroundBuffer, 0,0,160,120);
	baseSprite->setCursor(125, 105);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->drawRect(35, 100, 92, 18, TFT_WHITE);
	baseSprite->drawRect(34, 99, 94, 20, TFT_WHITE);
	baseSprite->setCursor(display->getWidth()/ 2 - display->getBaseSprite()->textWidth(titleMenu[titleCursor]) / 2, 100);
	baseSprite->print(titleMenu[titleCursor]);
	if(blinkState)
	{
		if (titleCursor == 0)
		{
			baseSprite->drawIcon(icon_player, 23, 108, 8, 8, 1, TFT_BLACK );
			baseSprite->drawIcon(icon_player, 131, 108, 8, 8, 1, TFT_BLACK);
		}
		else if (titleCursor == 2)
		{
			baseSprite->drawIcon(icon_player, 23, 110, 8, 8, 1, TFT_BLACK);
			baseSprite->drawIcon(icon_player, 131, 110, 8, 8, 1, TFT_BLACK);
		}
		else
		{
			baseSprite->drawIcon(icon_player, 23, 110, 8, 8, 1, TFT_BLACK);
			baseSprite->drawIcon(icon_player, 131, 108, 8, 8, 1, TFT_BLACK);
		}
	}
	else
	{
		baseSprite->drawIcon(icon_player, 23, 108, 8, 8, 1, TFT_BLACK);
		baseSprite->drawIcon(icon_player, 131, 110, 8, 8, 1, TFT_BLACK);
	}
}

void CastleJump::Menu::loop(uint time){
	blinkMicros+=time;
	if(blinkMicros > 200000)
	{
		blinkState = !blinkState;
		blinkMicros = 0;
	}


}