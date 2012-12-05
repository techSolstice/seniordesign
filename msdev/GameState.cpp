#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include "GameState.h"

using namespace std;

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
