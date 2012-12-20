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

	Sending:
		=====================
		| s | i | a | v | r |
		=====================
		s: state
		i: incline
		a: angle
		v: vibration
		r: resistance

	Receiving:
		=====================
		| s | t | r | d | b |
		=====================
		s: state
		t: timestamp
		r: # of rotations
		d: direction
		b: buttons & e-brake
*/
int GameState::state = 0;
int GameState::incline = 0;
int GameState::angle = 0;
int GameState::vibration = 0;
int GameState::resistance = 0;


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
	void GameState::increaseIncline(int interval){
		incline += interval;

		if (incline > MAX_INCLINE) incline = MAX_INCLINE;
		else if (incline < MIN_INCLINE) incline = MIN_INCLINE;
	}

	void GameState::increaseAngle(int angleAmount){
		angle += angleAmount;

		if (angleAmount > MAX_ANGLE) angle = MAX_ANGLE;
		if (angleAmount < MIN_ANGLE) angle = MIN_ANGLE;
	}

	void GameState::increaseVibration(int vibrationLevel){
		vibration += vibrationLevel;

		if (vibration > MAX_VIBRATION) vibration = MAX_VIBRATION;
		if (vibration < MIN_VIBRATION) vibration = MIN_VIBRATION;
	}

	void GameState::increaseResistance(int resistanceAmount){
		resistance += resistanceAmount;

		if (resistance > MAX_RESISTANCE) resistance = MAX_RESISTANCE;
		if (resistance < MIN_RESISTANCE) resistance = MIN_RESISTANCE;
	}

	void GameState::setState(int newState){
		state = newState;
	}

	void GameState::setTerrain(int terrainType){
		switch (terrainType){
		case 1:
			state = 1;
			vibration = 1;
			increaseIncline(1);
			break;

		default: break;
		}
	}
	
		byte GameState::getState(){return (byte)('0'+state);}
		
		byte GameState::getIncline(){return (byte)incline;}
		byte GameState::getAngle(){return (byte)angle;}
		byte GameState::getVibration(){return (byte)vibration;}
		byte GameState::getResistance(){return (byte)resistance;}

		
