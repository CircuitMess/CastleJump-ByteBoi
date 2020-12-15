#include <Arduino.h>
#include <Nibble.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include "src/CastleJump.h"
#include "src/GameState.h"
#include "src/Highscore/Highscore.h"

CastleJump *castleJump;

void setup(){
	Serial.begin(115200);
	Nibble.begin();
	Highscore.begin();
	castleJump=new CastleJump();
	LoopManager::addListener(castleJump);
	LoopManager::addListener(Input::getInstance());
}

void loop(){

	LoopManager::loop();

}