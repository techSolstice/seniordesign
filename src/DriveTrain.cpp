#include "DriveTrain.h"

DriveTrain::DriveTrain()
{}

DriveTrain::DriveTrain(REAL Redline, REAL MaxTorque/*to be replaced by array*/) :
	MyRedline(Redline),
	MyTacho(Redline),
	MyMaxTorque(MaxTorque)
{}

REAL DriveTrain::GetTorque(REAL Gas, REAL WheelRevs)
{
	return MyMaxTorque;
}

void DriveTrain::drawInfo(REAL tmp)
{
	MyTacho.draw(tmp*300);
}
