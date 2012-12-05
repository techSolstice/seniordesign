#ifndef _ARDUINO_COMM_H
#define _ARDUINO_COMM_H

#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>

using namespace std;

	static unsigned int state;
	static unsigned int incline;
	static unsigned int angle;
	static unsigned int vibration;
	static unsigned int resistance;

	const int MAX_INCLINE = 5;
	const int MIN_INCLINE = 0;

class GameState{
public:
	GameState();
	~GameState();
	void setTerrain(int terrainType);
	void increaseIncline(int interval);
//private:	TODO this will be private once this class is completed

};

#endif