#ifndef CASTLEJUMP_ENTERHIGHSCORESTATE_H
#define CASTLEJUMP_ENTERHIGHSCORESTATE_H


#include "GameState.h"
#include "State.h"

class EnterHighscoreState : public State {
public:

	EnterHighscoreState(int score);

	void loop(uint time) override;

	void enter(CastleJump &gameEnter) override;

	void exit() override;

	void draw() override;

private:
	int score{};
	char *name;
	uint8_t charCursor;
	bool cursorBlink;
	bool hiscoreBlink;
	uint cursorTime;
	uint hiscoreTime;

	void drawHighscore();

	static EnterHighscoreState *instance;
	Display *display;
	Sprite *baseSprite;
};


#endif //CASTLEJUMP_ENTERHIGHSCORESTATE_H
