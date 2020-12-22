//
// Created by hrvoj on 01/12/2020.
//

#ifndef CASTLEJUMP_STATE_H
#define CASTLEJUMP_STATE_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/Input.h>
#include <Loop/LoopManager.h>
#include <Display/Sprite.h>
#include <Nibble.h>
#include "CastleJump.h"
#include "Melodies/Melody.h"

class State {

public:


	virtual ~State();

	virtual void enter(CastleJump &gameEnter) = 0;

	virtual void exit()=0;

	virtual void loop(uint) = 0;


protected:

	CastleJump *castleJump;


};

#endif //JUMPINGJACK_STATE_H
