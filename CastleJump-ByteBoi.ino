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
	castleJump=new CastleJump::CastleJump(ByteBoi.getDisplay());
	castleJump->unpack();
	castleJump->start();
}

void loop(){
	LoopManager::loop();

}