#include <FS.h>
#include <FS/CompressedFile.h>
#include <SPIFFS.h>
#include "ShowHighscoreState.h"
#include "Highscore/Highscore.h"
#include "Melodies/Notes.hpp"
#include "bitmaps/highscore.hpp"

CastleJump::ShowHighscoreState *CastleJump::ShowHighscoreState::instance = nullptr;

CastleJump::ShowHighscoreState::ShowHighscoreState(){
	backgroundBuffer = static_cast<Color*>(ps_malloc(160 * 120 * 2));
	if(backgroundBuffer == nullptr){
		Serial.printf("Highscore background picture unpack error\n");
		return;
	}

	fs::File backgroundFile = CompressedFile::open(SPIFFS.open("/Highscore.raw.hs"), 10, 5);

	backgroundFile.read(reinterpret_cast<uint8_t*>(backgroundBuffer), 160 * 120* 2);
	backgroundFile.close();

	display = ByteBoi.getDisplay();
	baseSprite = display->getBaseSprite();
	instance = this;

}

void CastleJump::ShowHighscoreState::start(CastleJump &gameEnter){

	castleJump=&gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_UP,[](){
		Piezo.tone(NOTE_B7,100);
		instance->castleJump->deleteHighscores();
	});
	Input::getInstance()->setBtnPressCallback(BTN_A,[](){
		Piezo.tone(NOTE_B6,25);
		instance->castleJump->returnToMenu();
	});
	Input::getInstance()->setBtnPressCallback(BTN_B,[](){
		Piezo.tone(NOTE_B6,25);
		instance->castleJump->returnToMenu();
	});
	Input::getInstance()->setBtnPressCallback(BTN_C, [](){
		instance->castleJump->returnToMenu();
	});
}
void CastleJump::ShowHighscoreState::stop(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnReleaseCallback(BTN_B);
	Input::getInstance()->removeBtnPressCallback(BTN_UP);
	Input::getInstance()->removeBtnReleaseCallback(BTN_UP);
	Input::getInstance()->removeBtnPressCallback(BTN_C);
	Input::getInstance()->removeBtnReleaseCallback(BTN_C);

}
void CastleJump::ShowHighscoreState::drawHighscore(){
	baseSprite->clear(TFT_BLACK);
	baseSprite->drawIcon(backgroundBuffer,0,0,160,120);
	for(int i=0;i<5;i++){
		baseSprite->setTextColor(TFT_WHITE);
		baseSprite->setCursor(43,(i*16)+32);
		baseSprite->setTextSize(1);
		baseSprite->setTextFont(1);
		if((i+1) <= Highscore.count()){
			Serial.println(Highscore.get(i).score);
			baseSprite->printf("  %.3s  %4d",Highscore.get(i).name, Highscore.get(i).score);
		}
	}

}
void CastleJump::ShowHighscoreState::draw(){
	drawHighscore();
	drawScrollText();
	display->commit();

}
void CastleJump::ShowHighscoreState::loop(uint time){

}

void CastleJump::ShowHighscoreState::drawScrollText(){
	baseSprite->setCursor(display->getWidth()/ 2 - display->getBaseSprite()->textWidth("Press UP to erase") / 2, 1);
	baseSprite->setTextSize(1);
	baseSprite->setTextFont(1);
	baseSprite->print("Press UP to erase");
}


