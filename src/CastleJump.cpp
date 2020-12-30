//
// Created by hrvoj on 01/12/2020.
//
#include "CastleJump.h"
#include "State.h"
#include "Menu.h"
#include "PauseState.h"
#include "GameState.h"
#include "Pins.hpp"


CastleJump *CastleJump::instance= nullptr;

CastleJump::CastleJump() : Context(*display) {

	LoopManager::addListener(&melody);
	state=new Menu();
	state->enter(*this);

}
void CastleJump::draw(){
	state->draw();
}

void CastleJump::pauseGame(){

	pausedGameState = state;
	state = new PauseState();
	state->enter(*this);
}

void CastleJump::resumeGame(){
	state->exit();
	delete state;
	state = pausedGameState;
	pausedGameState = nullptr;
	state->enter(*this);
}


void CastleJump::changeState(State *differentState){
	state->exit();
	delete state;
	state = differentState;
	state->enter(*this);
}
void CastleJump::loop(uint time){
	state->loop(time);
	draw();

}