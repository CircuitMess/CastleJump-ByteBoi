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

CastleJump *castleJump;

void setup(){
	Serial.begin(115200);
	Nibble.begin();
	Highscore.begin();
	//Serial.println(ESP.getFreeHeap());
	castleJump=new CastleJump();//new (bilo koji state)
	//delete castleJump;
//	Serial.println(ESP.getFreeHeap());
	LoopManager::addListener(castleJump);
	LoopManager::addListener(Input::getInstance());

}

void loop(){

	LoopManager::loop() ;

}