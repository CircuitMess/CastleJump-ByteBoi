#ifndef CASTLEJUMP_GAMESTATE_H
#define CASTLEJUMP_GAMESTATE_H

#include "State.h"
#include <Motion/vec.hpp>

struct Player {
	vec3f pos;
	vec3f velocity;
};
struct Coin {
	float x;
	float y;
	float r;
	Color color;
};
struct PowerUps {
	float x;
	float y;
	float r;
	Color color;
};
struct Rect {
	float x;
	float y;
	float w;
	float h;

};

class GameState : public State {

public:
	GameState();

	void loop(uint time) override;

	void enter(CastleJump &gameEnter) override;

	void exit() override;

	static void buttonRightPress();

	static void buttonRightRelease();

	static void buttonLeftPress();


	static void buttonLeftRelease();

	static void buttonBPress();

	static void buttonBRelease();


private:
	static GameState *instance;
	Display *display;
	Sprite *baseSprite;
	const float speed = 1;
	bool leftState = false;
	bool rightState = false;
	bool bState = false;
	Vector<Rect> dropRect;
	Player player;
	int score = 0;
	vec3f gravity = {0, 190, 0};
	bool firstTouch = false;
	bool highspeed = false;
	bool lowGravity = false;
	unsigned long currentTime;
	unsigned long previousTime = 0;
	int seconds = 5;
	Vector<Coin> coin;
	bool checkWallBump = false;
	int lvl = 1;
	int livesNum=3;

	Vector<PowerUps> ability;

	void drawPlayerCircle();

	void drawRect(Rect &stairs);

	void checkForCollision(Rect &stairs);

	void velocity(float dt);

	void movingRects(Rect &stairs, uint b);

	void xPosMoving();

	void scoreTable();

	void powerUpTimer();

	void level();

	void levelCounter();

	void lives();

	void livesCounter();

	void drawCoin(Coin &goldenCoin);

	void movingCoin(Coin &goldenCoin, uint b);

	void checkForPoint(Coin &goldenCoin);

	void drawAbilityPoint(PowerUps &ability);

	void movingPowerUps(PowerUps &ability, uint b);

	void checkForPowerUp(PowerUps &ability);
};

#endif