#ifndef _GameState_H
#define _GameState_H

#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>

using namespace std;

	static unsigned int state = 0;
	static unsigned int incline = 0;
	static int angle = 0;
	static unsigned int vibration = 0;
	static unsigned int resistance = 0;

	const int MAX_INCLINE = 5;
	const int MIN_INCLINE = 0;
	const int MIN_ANGLE = -30;
	const int MAX_ANGLE = 30;
	const int MIN_VIBRATION = 0;
	const int MAX_VIBRATION = 5;
	const int MIN_RESISTANCE = 0;
	const int MAX_RESISTANCE = 10;

class GameState{
public:
	GameState();
	~GameState();
	void setTerrain(int terrainType);
	void increaseIncline(int interval);
	void increaseAngle(int angleAmount);
	void increaseVibration(int vibrationLevel);
	void increaseResistance(int resistanceAmount);
	void setState(int newState);

	byte getState();
	byte getIncline();
	byte getAngle();
	byte getVibration();
	byte getResistance();
	static char* GameState::toString(){
		char* stateString = new char[];
		stateString[0] = state;
		stateString[1] = incline;
		stateString[2] = angle;
		stateString[3] = vibration;
		stateString[4] = resistance;

		return stateString;
	}

//private:	TODO this will be private once this class is completed

};

#endif