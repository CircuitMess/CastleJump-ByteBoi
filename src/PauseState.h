#ifndef CASTLEJUMP_PAUSESTATE_H
#define CASTLEJUMP_PAUSESTATE_H
#include "State.h"

class PauseState : public State {
public:
	PauseState();


	void loop(uint time) override;

	void enter(CastleJump &gameEnter) override;

	void exit() override;

private:

	Display *display;
	Sprite *baseSprite;

	void displayMessage();


	static PauseState *instance;
};
#endif //CASTLEJUMP_PAUSESTATE_H
