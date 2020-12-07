//
// Created by hrvoj on 01/12/2020.
//
#include "CastleJump.h"
#include "State.h"
#include "GameState.h"

CastleJump *CastleJump::instance= nullptr;

CastleJump::CastleJump(){

	state=new GameState();
	state->enter(*this);

}
/*void JumpingJack::changeState(State *differentState){
	state->exit();
	delete state;
	state = differentState;
	state->enter(*this);
}*/
void CastleJump::loop(uint time){
	state->loop(time);

}