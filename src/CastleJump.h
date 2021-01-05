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
#include <Support/Context.h>
//extern Context* runningContext;

namespace CastleJump {


	class State;

	class CastleJump : public Context, public LoopListener {

	public:

		CastleJump(Display *display);

		void start() override;

		void loop(uint time) override;

		void stop() override;

		void draw() override;

		void newGame();

		void enterHighscore();

		void openHighscores();

		void deleteHighscores();

		void pauseGame();

		void gameOver();

		void resumeGame();

		void returnToMenu();

		State *pausedGameState = nullptr;

		uint score;

	private:

		State *state;
		static CastleJump *instance;
		Display *display;
		Sprite *baseSprite;


	};
};
#endif
