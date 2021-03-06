#ifndef CASTLEJUMP_STATE_H
#define CASTLEJUMP_STATE_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/Input.h>
#include <Loop/LoopManager.h>
#include <Display/Sprite.h>
#include <ByteBoi.h>
#include "CastleJump.h"
#include "Melodies/Melody.h"

namespace CastleJump {
	class CastleJump;
	class State {

	public:


		virtual ~State();

		virtual void start(CastleJump &gameEnter) = 0;

		virtual void stop(){};

		virtual void loop(uint time) = 0;

		virtual void draw() = 0;


	protected:

		CastleJump *castleJump;


	};
};
#endif //JUMPINGJACK_STATE_H
