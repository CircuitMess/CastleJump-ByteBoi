#ifndef CASTLEJUMP_MENU_H
#define CASTLEJUMP_MENU_H

#include "State.h"

struct MenuSelection{
		float x;
		float y;
		float r;
		Color color;
};

class Menu : public State {

public:
	Menu();
	static void buttonAPress();

	static void buttonARelease();

	static void buttonDownPress();

	static void buttonDownRelease();

	static void buttonUpPress();

	static void buttonUpRelease();

	void loop(uint time) override;

	void enter(CastleJump &gameEnter) override;

	void exit() override;

private:

	void drawSelection(MenuSelection &menuSelect);

	void checkStateAndMove(MenuSelection &menuSelect);

	MenuSelection menuSelect;
	static Menu *instance;
	Display *display;
	Sprite *baseSprite;
	bool aState = false;
	bool upState = false;
	bool downState = false;
	bool checkState = false;

	void drawMenuScreen();
};


#endif //CASTLEJUMP_MENU_H
