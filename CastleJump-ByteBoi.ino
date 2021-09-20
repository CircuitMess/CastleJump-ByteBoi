#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include "src/CastleJump.h"
#include "src/GameState.h"
#include <ByteBoi.h>
#include <SPIFFS.h>

CastleJump::CastleJump* castleJump;
Sprite *baseSprite;

void setup(){
	Serial.begin(115200);
	ByteBoi.begin();
	ByteBoi.getDisplay()->commit();
	Piezo.begin(25);
	LoopManager::addListener(Input::getInstance());
	castleJump=new CastleJump::CastleJump(ByteBoi.getDisplay());
	LoopManager::addListener(castleJump);
	castleJump->unpack();
	castleJump->start();
}

void loop(){
	LoopManager::loop();

}