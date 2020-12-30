#ifndef CASTLEJUMP_GAMEOVERSTATE_H
#define CASTLEJUMP_GAMEOVERSTATE_H

#include "State.h"
#include "GameState.h"

class GameOverState : public State {
public:
	GameOverState(int score);

	static void buttonAPress();

	static void buttonBPress();

	static void buttonARelease();

	static void buttonBRelease();

	void loop(uint time) override;

	void enter(CastleJump &gameEnter) override;

	void exit() override;

	void draw() override;

private:
	int score;
	GameState *gameState;
	Display *display;
	Sprite *baseSprite;
	bool aState = false;
	bool bState = false;
	bool initialValue = true;
	bool checkMusic = false;
	int seconds=0;
	int currentTime;
	int previousTime;

	void drawGameOver();

	static GameOverState *instance;
};

#endif //CASTLEJUMP_GAMEOVERSTATE_H
