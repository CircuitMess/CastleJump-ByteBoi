#include "CastleJump.h"
#include "State.h"
#include "Menu.h"
#include "PauseState.h"
#include "GameState.h"
#include "ShowHighscoreState.h"
#include "EraseHighscoreState.h"
#include "EnterHighscoreState.h"
#include "Highscore/Highscore.h"
#include "GameOverState.h"

CastleJump::CastleJump *CastleJump::CastleJump::instance = nullptr;

CastleJump::CastleJump::CastleJump(Display *display) : Context(*display), score(0){

	LoopManager::addListener(&melody);
	state = new Menu(&screen);

}

void CastleJump::CastleJump::draw(){
	state->draw();
}

void CastleJump::CastleJump::pauseGame(){
	state->stop();
	pausedGameState = state;
	state = new PauseState(&screen);
	state->start(*this);
}

void CastleJump::CastleJump::resumeGame(){
	state->stop();
	delete state;
	state = pausedGameState;
	pausedGameState = nullptr;
	state->start(*this);

}

void CastleJump::CastleJump::start(){
	Highscore.begin();
	state->start(*this);
	LoopManager::addListener(this);
}

void CastleJump::CastleJump::stop(){
	state->stop();
	LoopManager::removeListener(this);
}

void CastleJump::CastleJump::openHighscores(){
	state->stop();
	delete state;
	state = new ShowHighscoreState(&screen);
	state->start(*this);
}

void CastleJump::CastleJump::deleteHighscores(){
	state->stop();
	delete state;
	state = new EraseHighscoreState(&screen);
	state->start(*this);
}

void CastleJump::CastleJump::returnToMenu(){
	state->stop();
	delete state;
	state = new Menu(&screen);
	state->start(*this);
}

void CastleJump::CastleJump::enterHighscore(){
	state->stop();
	delete state;
	state = new EnterHighscoreState(&screen);
	state->start(*this);
}

void CastleJump::CastleJump::gameOver(){
	state->stop();
	delete state;
	state = new GameOverState(&screen);
	state->start(*this);
}

void CastleJump::CastleJump::newGame(){
	state->stop();
	delete state;
	state = new GameState(&screen);
	state->start(*this);
}

void CastleJump::CastleJump::loop(uint time){
	state->loop(time);
	draw();
	screen.commit();
}