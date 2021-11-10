#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include "src/CastleJump.h"
#include "src/GameState.h"
#include <ByteBoi.h>
#include <SPIFFS.h>
#include <SD.h>
#include <SleepService.h>

CastleJump::CastleJump* castleJump;
Sprite *baseSprite;

namespace CastleJump {
	Sample* menuMusic = nullptr;
	Sample* gameMusic = nullptr;
}

void setup(){
	Serial.begin(115200);
	ByteBoi.begin();
	Sleep.begin();
	ByteBoi.bindMenu();
	BatteryPopup.enablePopups(true);
	ByteBoi.setGameID("CJump");

	SD.begin(SD_CS, SPI);

	CastleJump::menuMusic = new Sample(SD.open(ByteBoi.getSDPath() + "/Music/Menu.aac"));
	CastleJump::gameMusic = new Sample(SD.open(ByteBoi.getSDPath() + "/Music/Game.aac"));

	CastleJump::menuMusic->setLooping(true);
	CastleJump::gameMusic->setLooping(true);

	castleJump=new CastleJump::CastleJump(ByteBoi.getDisplay());
	castleJump->unpack();
	ByteBoi.splash();
	castleJump->start();
}

void loop(){
	LoopManager::loop();
}