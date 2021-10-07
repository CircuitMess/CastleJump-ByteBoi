#ifndef CASTLEJUMP_ERASEHIGHSCORESTATE_H
#define CASTLEJUMP_ERASEHIGHSCORESTATE_H

#include "State.h"

namespace CastleJump {
	class EraseHighscoreState : public State {
	public:

		EraseHighscoreState(Screen* screen);

		void loop(uint time) override;

		void start(CastleJump &gameEnter) override;

		void stop() override;

		void draw() override;

	private:

		void drawWarning();

		static EraseHighscoreState *instance;
		Display *display;
		Screen* screen;
		Sprite *baseSprite;
	};
};
#endif //CASTLEJUMP_ERASEHIGHSCORESTATE_H
