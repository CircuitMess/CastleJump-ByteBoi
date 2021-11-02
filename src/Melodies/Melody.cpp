#include "Melody.h"
#include <Arduino.h>
#include <ByteBoi.h>
#include "MelodyNotes.h"

MelodyImpl melody;

MelodyImpl::MelodyImpl(){

}
void MelodyImpl::play(Melodies state, bool loopMelody){
	isPlaying = true;
	counterMelody = 0;
	continuePlaying = loopMelody;
	if(state == win){
		playingMelody = melodyWin;
		melodySize = sizeof(melodyWin) / sizeof(melodyWin[0]);

	}else if(state == coin){
		playingMelody = melodyCoin;
		melodySize = sizeof(melodyCoin) / sizeof(melodyCoin[0]);

	}else if(state == menu){
		playingMelody = melodyMenu;
		melodySize = (sizeof(melodyMenu) / sizeof(melodyMenu[0]));
	}else if(state == game){

		playingMelody = melodyGame;
		melodySize = (sizeof(melodyGame) / sizeof(melodyGame[0])-1);
	}else if(state == dead){

		playingMelody = melodyDead;
		melodySize = (sizeof(melodyDead) / sizeof(melodyDead[0])-1);
	}else if(state == hit){

		playingMelody = melodyHit;
		melodySize = (sizeof(melodyHit) / sizeof(melodyHit[0]));
	}
}

void MelodyImpl::loop(uint){

	/*if(isPlaying == false){
		return;
	}
	if(counterMelody <= melodySize){
	//	Playback.tone(playingMelody[counterMelody].frequency, playingMelody[counterMelody].duration);
		currentNoteTime = millis();
		if(currentNoteTime - previousNoteTime > playingMelody[counterMelody].duration){
			previousNoteTime = currentNoteTime;
			counterMelody++;
		}
	}else{
		if(continuePlaying == true){
			isPlaying = true;
			counterMelody = 0;
		}else{
			isPlaying = false;
		}


	}*/
}

