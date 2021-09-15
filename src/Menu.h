#ifndef CASTLEJUMP_MENU_H
#define CASTLEJUMP_MENU_H

#include "State.h"

namespace CastleJump {

	struct MenuSelection {
		float x;
		float y;
		float r;
		Color color;
	};

	class Menu : public State {

	public:
		Menu();

		~Menu();

		static void buttonAPress();

		static void buttonARelease();

		static void buttonDownPress();

		static void buttonDownRelease();

		static void buttonUpPress();

		static void buttonUpRelease();

		static void buttonRightPress();

		static void buttonRightRelease();

		static void buttonLeftPress();

		static void buttonLeftRelease();

		void loop(uint time) override;

		void start(CastleJump& gameEnter) override;

		void stop() override;

		void draw() override;

	private:
		static const char* titleMenu[3];
		uint8_t titleCursor;
		bool blinkState;
		uint blinkMicros;
		static Menu* instance;
		Display* display;
		Sprite* baseSprite;
		Color* backgroundBuffer = nullptr;
	};
};

#endif //CASTLEJUMP_MENU_H
