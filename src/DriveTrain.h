#ifndef __DRIVETRAIN_H_
#define __DRIVETRAIN_H_

namespace std {}
using namespace std;

#include "H_Graphics.h"
#include "Tacho.h"

class DriveTrain
{
public:
	//EnginRevs(ex:Redline) and WheelRevs given in rev.s-1
	//gear ratio is given in EnginRevs/WheelRevs
	//Torque is given in N.m
	DriveTrain();
	DriveTrain(REAL Redline, REAL MaxTorque/*to be replaced by array*/);
	REAL GetTorque(REAL Gas, REAL WheelRevs);
	void drawInfo(REAL tmp);
private:
	REAL GetRevs(); //convert from rev/sec to rev/min
	int MyNbGears;
	REAL *MyGearRatios;
	REAL MyPower;
	REAL MyRedline;
	Tacho MyTacho;
	REAL MyMaxTorque;
};

#endif