#include "EnterHighscoreState.h"
#include "CastleJump.h"
#include "Highscore/Highscore.h"
#include "GameState.h"
#include "ShowHighscoreState.h"
#include "GameOverState.h"
#include "Melodies/Notes.hpp"

EnterHighscoreState *EnterHighscoreState::instance = nullptr;

EnterHighscoreState::EnterHighscoreState(int highscoreScore){

	score = highscoreScore;
	display = Nibble.getDisplay();
	baseSprite = display->getBaseSprite();
	charCursor = 0;
	cursorTime = 0;
	hiscoreTime = 0;
	cursorBlink = true;
	hiscoreBlink = false;
	name = new char[4];
	strncpy(name, "AAA\0", sizeof(name));
	instance = this;
	melody.play(MelodyImpl::win,false);

}

void EnterHighscoreState::enter(CastleJump &gameEnter){
	castleJump = &gameEnter;
	Input::getInstance()->setBtnPressCallback(BTN_UP, [](){
		instance->cursorBlink = true;
		instance->cursorTime = millis();
		instance->name[instance->charCursor]++;
		Piezo.tone(NOTE_B6,25);
		if(instance->name[instance->charCursor] == '0') instance->name[instance->charCursor] = ' ';
		if(instance->name[instance->charCursor] == '!') instance->name[instance->charCursor] = 'A';
		if(instance->name[instance->charCursor] == '[') instance->name[instance->charCursor] = '0';
		if(instance->name[instance->charCursor] == '@') instance->name[instance->charCursor] = '!';

	});
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_UP, 200, [](uint){
		instance->cursorBlink = true;
		instance->cursorTime = millis();
		instance->name[instance->charCursor]++;
		Piezo.tone(NOTE_B6,25);
		if(instance->name[instance->charCursor] == '0') instance->name[instance->charCursor] = ' ';
		if(instance->name[instance->charCursor] == '!') instance->name[instance->charCursor] = 'A';
		if(instance->name[instance->charCursor] == '[') instance->name[instance->charCursor] = '0';
		if(instance->name[instance->charCursor] == '@') instance->name[instance->charCursor] = '!';
	});
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_DOWN, 200, [](uint){
		instance->cursorBlink = true;
		instance->cursorTime = millis();
		instance->name[instance->charCursor]--;
		Piezo.tone(NOTE_B6,25);
		if(instance->name[instance->charCursor] == ' ') instance->name[instance->charCursor] = '?';
		if(instance->name[instance->charCursor] == '/') instance->name[instance->charCursor] = 'Z';
		if(instance->name[instance->charCursor] == 31) instance->name[instance->charCursor] = '/';
		if(instance->name[instance->charCursor] == '@') instance->name[instance->charCursor] = ' ';
	});
	Input::getInstance()->setBtnPressCallback(BTN_DOWN, [](){
		instance->cursorBlink = true;
		instance->cursorTime = millis();
		instance->name[instance->charCursor]--;
		Piezo.tone(NOTE_B6,25);
		if(instance->name[instance->charCursor] == ' ') instance->name[instance->charCursor] = '?';
		if(instance->name[instance->charCursor] == '/') instance->name[instance->charCursor] = 'Z';
		if(instance->name[instance->charCursor] == 31) instance->name[instance->charCursor] = '/';
		if(instance->name[instance->charCursor] == '@') instance->name[instance->charCursor] = ' ';
	});
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		instance->charCursor++;
		instance->cursorBlink = true;
		instance->cursorTime = millis();
		Piezo.tone(NOTE_B6,25);
	});
	Input::getInstance()->setBtnPressCallback(BTN_LEFT, [](){
		if(instance->charCursor > 0){
			instance->charCursor--;
			instance->cursorBlink = true;
			instance->cursorTime = millis();
			Piezo.tone(NOTE_B6,25);
		}
	});
	Input::getInstance()->setBtnPressCallback(BTN_RIGHT, [](){
		if(instance->charCursor < 2){
			instance->charCursor++;
			instance->cursorBlink = true;
			instance->cursorTime = millis();
			Piezo.tone(NOTE_B6,25);
		}
	});
	Piezo.setMute(false);

}


void EnterHighscoreState::drawHighscore(){
	baseSprite->setCursor(16, 8);
	baseSprite->setTextFont(2);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextSize(1);
	baseSprite->printCenter("ENTER NAME");
	baseSprite->setCursor(20, 75);

	if(hiscoreBlink && score > Highscore.get(0).score){
		baseSprite->printCenter("NEW HIGH!");
	}else{
		baseSprite->setCursor(20, 90);
		baseSprite->printf("SCORE: %3d", score);
	}
	baseSprite->setCursor(40, 40);
	baseSprite->print(name[0]);
	baseSprite->setCursor(55, 40);
	baseSprite->print(name[1]);
	baseSprite->setCursor(70, 40);
	baseSprite->print(name[2]);
	if(cursorBlink){
		baseSprite->drawFastHLine(38 + 15 * charCursor, 56, 12, TFT_WHITE);
	}
}

void EnterHighscoreState::exit(){

	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnPressCallback(BTN_LEFT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_LEFT);
	Input::getInstance()->removeBtnPressCallback(BTN_DOWN);
	Input::getInstance()->removeBtnReleaseCallback(BTN_DOWN);
	Input::getInstance()->removeBtnPressCallback(BTN_UP);
	Input::getInstance()->removeBtnReleaseCallback(BTN_UP);
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_UP, 0, nullptr);
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_DOWN, 0, nullptr);
	Piezo.setMute(true);
}

void EnterHighscoreState::loop(uint time){
	baseSprite->clear(TFT_BLACK);
	drawHighscore();
	hiscoreTime += time;
	if(hiscoreTime >= 1000000){
		hiscoreTime = 0;
		hiscoreBlink = !hiscoreBlink;
	}
	cursorTime += time;
	if(cursorTime >= 350000){
		cursorTime = 0;
		cursorBlink = !cursorBlink;
	}
	if(charCursor >2 || charCursor<0){
		Score newScore{};
		strcpy(newScore.name, name);
		newScore.score = score;
		Highscore.add(newScore);
		castleJump->changeState(new ShowHighscoreState());
	}
	display->commit();
}