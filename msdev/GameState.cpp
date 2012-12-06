#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include "GameState.h"

using namespace std;

/*
	Class: GameState
	This class will handle all interactions with the game state and packets
	to be sent to the Arduino.  This includes rotation, resistance, angle, etc.

	This class will contain packet interactions and formations.  Packets are
	currently designed as follows:

	=========================
	| a | b | c | d | e | f |
	=========================
*/

	GameState::GameState(){
		state = 0;
		incline = 0;
		angle = 0;
		vibration = 0;
		resistance = 0;
	}

	GameState::~GameState(){

	}

	
	/**
		Increases the incline by a set interval amount on it
	*/
	void increaseIncline(int interval){
		incline += interval;

		if (incline > MAX_INCLINE) incline = MAX_INCLINE;
		else if (incline < MIN_INCLINE) incline = MIN_INCLINE;
	}


	void setTerrain(int terrainType){
		switch (terrainType){
		case 1:
			state = 1;
			vibration = 1;
			increaseIncline(1);
			break;

		default: break;
		}
	}
