#ifndef CASTLEJUMP_SHOWHIGHSCORESTATE_H
#define CASTLEJUMP_SHOWHIGHSCORESTATE_H

#include "State.h"

namespace CastleJump {
	class ShowHighscoreState : public State {
	public:
		ShowHighscoreState(Screen* screen);

		void loop(uint time) override;

		void start(CastleJump& gameEnter) override;

		void stop() override;

		void draw() override;

	private:
		static ShowHighscoreState* instance;

		Display* display;

		Sprite* baseSprite;
		Screen* screen;
		Color* backgroundBuffer = nullptr;

		void drawScrollText();

		void drawHighscore();
	};
};
#endif //CASTLEJUMP_SHOWHIGHSCORESTATE_H
