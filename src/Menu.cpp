#include "Menu.h"
#include <Nibble.h>
#include <Arduino.h>
#include <FS.h>
#include <FS/CompressedFile.h>
#include <SPIFFS.h>
#include "Melodies/Notes.hpp"
#include "bitmaps/player.hpp"
#include "bitmaps/home_screen.hpp"
#include <Pins.hpp>

const char *CastleJump::Menu::titleMenu[3] = {"Start", "Highscore", "Quit"};
CastleJump::Menu *CastleJump::Menu::instance = nullptr;

CastleJump::Menu::Menu(){

	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();

	instance = this;
	titleCursor = 0;
	blinkState = 0;
	blinkMicros = 0;
	melody.play(MelodyImpl::menu, true);
	display->commit();

	backgroundBuffer = static_cast<Color*>(ps_malloc(160 * 128 * 2));
	if(backgroundBuffer == nullptr){
		Serial.printf("Menu background picture unpack error\n");
		return;
	}

	fs::File backgroundFile = CompressedFile::open(SPIFFS.open("/HomeScreen160x128.raw.hs"),13,12);

	backgroundFile.read(reinterpret_cast<uint8_t*>(backgroundBuffer), 160 * 128 * 2);
	backgroundFile.close();
}

CastleJump::Menu::~Menu(){
	stop();
	free(backgroundBuffer);
}

void CastleJump::Menu::start(CastleJump &gameEnter){

	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_LEFT, [](){
		if(instance->titleCursor > 0){
			instance->titleCursor--;
			Piezo.tone(NOTE_B6, 25);

		}
	});
	Input::getInstance()->setBtnPressCallback(BTN_RIGHT, [](){
		if(instance->titleCursor < 2){
			instance->titleCursor++;
			Piezo.tone(NOTE_B6, 25);

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
				instance->castleJump->pop();
				break;
		}
	});
	Piezo.setMute(true);

}

CastleJump::Menu::~Menu(){
	stop();
}

void CastleJump::Menu::stop(){

	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_LEFT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_LEFT);
	Input::getInstance()->removeBtnPressCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_RIGHT);
	Piezo.setMute(true);
}

void CastleJump::Menu::draw(){
	baseSprite->clear(TFT_BLACK);
	baseSprite->drawIcon(backgroundBuffer, 0,0,160,128);
	baseSprite->setCursor(125, 105);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->drawRect(18, 110, 92, 18, TFT_WHITE);
	baseSprite->drawRect(17, 109, 94, 20, TFT_WHITE);

	baseSprite->setCursor(18*2, 110);
	baseSprite->printCenter(titleMenu[titleCursor]);
	if(blinkState)
	{
		if (titleCursor == 0)
		{
			baseSprite->drawIcon(icon_player, 4, 114, 8, 8, 1, TFT_BLACK );
			baseSprite->drawIcon(icon_player, 116, 114, 8, 8, 1, TFT_BLACK);
		}
		else if (titleCursor == 2)
		{
			baseSprite->drawIcon(icon_player, 4, 116, 8, 8, 1, TFT_BLACK);
			baseSprite->drawIcon(icon_player, 116, 116, 8, 8, 1, TFT_BLACK);
		}
		else
		{
			baseSprite->drawIcon(icon_player, 4, 116, 8, 8, 1, TFT_BLACK);
			baseSprite->drawIcon(icon_player, 116, 114, 8, 8, 1, TFT_BLACK);
		}
	}
	else
	{
		baseSprite->drawIcon(icon_player, 4, 114, 8, 8, 1, TFT_BLACK);
		baseSprite->drawIcon(icon_player, 116, 116, 8, 8, 1, TFT_BLACK);
	}

	display->commit();
}

void CastleJump::Menu::loop(uint time){
	baseSprite->clear(TFT_BLACK);
	blinkMicros+=time;
	if(blinkMicros > 200000)
	{
		blinkState = !blinkState;
		blinkMicros = 0;
	}


}