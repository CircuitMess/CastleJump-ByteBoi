#ifndef CASTLEJUMP_SHOWHIGHSCORESTATE_H
#define CASTLEJUMP_SHOWHIGHSCORESTATE_H

#include "State.h"

class ShowHighscoreState : public State {
public:
	ShowHighscoreState();

	void loop(uint time) override;

	void enter(CastleJump &gameEnter) override;

	void exit() override;

private:
	static ShowHighscoreState *instance;

	Display *display;

	Sprite *baseSprite;

	void drawHighscore();
};

#endif //CASTLEJUMP_SHOWHIGHSCORESTATE_H
