#ifndef CASTLEJUMP_GAMEOVERSTATE_H
#define CASTLEJUMP_GAMEOVERSTATE_H

#include "State.h"
#include "GameState.h"

namespace CastleJump {
	class GameOverState : public State {
	public:
		GameOverState(Screen* screen);

		static void buttonAPress();

		static void buttonBPress();

		static void buttonARelease();

		static void buttonBRelease();

		void loop(uint time) override;

		void start(CastleJump& gameEnter) override;

		void stop() override;

		void draw() override;

	private:
		GameState* gameState;
		Display* display;
		Sprite* baseSprite;
		Screen* screen;
		bool aState = false;
		bool bState = false;
		bool initialValue = true;
		bool checkMusic = false;
		int seconds = 0;
		int currentTime;
		int previousTime;
		uint score;

		void drawGameOver();

		static GameOverState* instance;
	};
};
#endif //CASTLEJUMP_GAMEOVERSTATE_H
