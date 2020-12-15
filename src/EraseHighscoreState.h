#ifndef CASTLEJUMP_ERASEHIGHSCORESTATE_H
#define CASTLEJUMP_ERASEHIGHSCORESTATE_H

#include "State.h"

class EraseHighscoreState : public State {
public:

	EraseHighscoreState();

	void loop(uint time) override;

	void enter(CastleJump &gameEnter) override;

	void exit() override;

private:

	void drawWarning();

	static EraseHighscoreState *instance;
	Display *display;
	Sprite *baseSprite;
};
#endif //CASTLEJUMP_ERASEHIGHSCORESTATE_H
