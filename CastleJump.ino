#include <Arduino.h>
#include <Nibble.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include "src/CastleJump.h"
#include "src/Highscore/Highscore.h"
#include <Audio/Piezo.h>
#include <avr/pgmspace.h>
#include "src/Menu.h"
#include "Pins.hpp"


CastleJump::CastleJump *castleJump;

void setup(){
	Serial.begin(115200);
	Nibble.getDisplay();
	Nibble.begin();
	castleJump = new CastleJump::CastleJump(Nibble.getDisplay());
	LoopManager::addListener(castleJump);
	LoopManager::addListener(Input::getInstance());
	castleJump->start();
}

void loop(){
	LoopManager::loop();
}