#ifndef _GameState_H
#define _GameState_H

#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>

using namespace std;



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
		stateString[0] = '0' + state;
		stateString[1] = '0' + incline;
		stateString[2] = '0' + angle;
		stateString[3] = '0' + vibration;
		stateString[4] = '0' + resistance;

		return stateString;
	}

	static unsigned int state;
	static unsigned int incline;
	static int angle;
	static unsigned int vibration;
	static unsigned int resistance;

	static const int MAX_INCLINE = 5;
	static const int MIN_INCLINE = 0;
	static const int MIN_ANGLE = -30;
	static const int MAX_ANGLE = 30;
	static const int MIN_VIBRATION = 0;
	static const int MAX_VIBRATION = 5;
	static const int MIN_RESISTANCE = 0;
	static const int MAX_RESISTANCE = 10;

//private:	TODO this will be private once this class is completed

};

#endif