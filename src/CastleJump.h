//
// Created by hrvoj on 01/12/2020.
//

#ifndef CASTLEJUMP_CASTLEJUMP_H
#define CASTLEJUMP_CASTLEJUMP_H

#include <Arduino.h>
#include <Nibble.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include <spiffs_api.h>
#include <Audio/Piezo.h>
#include "CastleJump.h"
#include "Melodies/Melody.h"

class State;

class CastleJump : public LoopListener {


public:

	CastleJump();

	void changeState(State *differentState);

	void loop(uint) override;

	void pauseGame();

	void resumeGame();

	void draw() ;


	State *pausedGameState = nullptr;

private:

	State *state;
	static CastleJump *instance;


	Display *display;
	Sprite *baseSprite;


};

#endif
