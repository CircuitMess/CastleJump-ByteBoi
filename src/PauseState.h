#ifndef CASTLEJUMP_PAUSESTATE_H
#define CASTLEJUMP_PAUSESTATE_H
#include "State.h"
namespace CastleJump {
	class PauseState : public State {
	public:
		PauseState(Screen* screen);


		void loop(uint time) override;

		void start(CastleJump &gameEnter) override;

		void stop() override;

		void draw() override;

	private:

		Display *display;
		Sprite *baseSprite;
		Screen* screen;
		void displayMessage();


		static PauseState *instance;
	};
};
#endif //CASTLEJUMP_PAUSESTATE_H
