#ifndef CASTLEJUMP_GAMESTATE_H
#define CASTLEJUMP_GAMESTATE_H

#include "State.h"
#include <Motion/vec.hpp>
#include <Display/AnimatedSprite.h>
namespace CastleJump {
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

		void start(CastleJump &gameEnter) override;

		void stop() override;

		void draw() override;

		static void buttonRightPress();

		static void buttonRightRelease();

		static void buttonLeftPress();


		static void buttonLeftRelease();


		uint score;


	private:
		static GameState *instance;
		Display *display;
		Sprite *baseSprite;
		double speed;
		bool leftState = false;
		bool rightState = false;
		Vector<Rect> dropRect;
		Player player;
		vec3f gravity = {0, 200, 0};
		bool firstTouch = false;
		bool highspeed = false;
		bool lowGravity = false;
		unsigned long currentTime;
		unsigned long previousTime = 0;
		int seconds = 5;
		Vector<Coin> coin;
		bool checkWallBump = false;
		int lvl = 1;
		int livesNum = 3;
		float korak = 0;

		Vector<PowerUps> powerUp;
		AnimatedSprite srce;
		/*AnimatedSprite downHit;
		AnimatedSprite leftHit;
		AnimatedSprite rightHit;*/
		enum AnimState {
			NONE, ANIM_LEFT, ANIM_RIGHT, ANIM_DOWN
		};
		AnimState state;

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

		void drawCoin(Coin &goldenCoin);

		void movingCoin(Coin &goldenCoin, uint b) const;

		void checkForPoint(Coin &goldenCoin);

		void drawAbilityPoint(PowerUps &powerUp);

		void movingPowerUps(PowerUps &powerUp, uint b) const;

		void checkForPowerUp(PowerUps &powerUp);

		void checkLevel();

		void drawWalls();

		void drawFloor();

		void drawLives();

		void drawBackGround();
	};
};
#endif