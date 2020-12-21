//
// Created by hrvoj on 17/12/2020.
//

#ifndef CASTLEJUMP_MELODY_H
#define CASTLEJUMP_MELODY_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/Input.h>
#include <Loop/LoopManager.h>
#include "Note.h"
#include <Audio/Piezo.h>


class MelodyImpl : public LoopListener {
	bool isPlaying = true;
	int melodySize;
	Note *playingMelody;
	bool continuePlaying = false;
public:

	MelodyImpl();

	void loop(uint) override;

	enum Melodies {
		menu, win, coin, game, dead, hit
	};

	void play(Melodies state, bool loopMelody);

private:

	int counterMelody = 0;
	void stop();
	unsigned long previousNoteTime = 0;
	unsigned long currentNoteTime = 0;
};

extern MelodyImpl melody;

#endif //CASTLEJUMP_MELODY_H
