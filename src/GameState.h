//
// Created by hrvoj on 01/12/2020.
//

#ifndef CASTLEJUMP_GAMESTATE_H
#define CASTLEJUMP_GAMESTATE_H

#include "State.h"
#include <Motion/vec.hpp>

struct Player {
	vec3f pos;
	vec3f velocity;
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

	static void buttonRightPress();

	static void buttonRightRelease();

	static void buttonLeftPress();

	static void buttonLeftRelease();


private:
	static GameState *instance;
	Display *display;
	Sprite *baseSprite;
	bool direction_y = false;
	float y_var;
	const float speed = 1;
	bool leftState = false;
	bool rightState = false;
	Vector<Rect> dropRect;
	Player player;
	int randX;

	vec3f gravity={0,150,0};

	void drawPlayerCircle();

	void drawRect(Rect &stairs);

	void yBouncing();

	void checkForCollision(Rect &stairs);

	void velocity(float dt);

	void functionForRects(Rect &stairs);

	void movingRects(Rect &stairs, uint b);

	void xPosMoving();

};

#endif
