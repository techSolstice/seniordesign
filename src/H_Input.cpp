
#include "H_Geometry.h"
#include "H_Input.h"

/*
#include "stdafx.h"

using namespace System;
using namespace System::IO::Ports;

int flashLED(array<System::String ^> ^args)
{

	String^ answer;
	String^ portName;
	int baudRate=9600;
	Console::WriteLine("Type in a port name and hit ENTER");
	portName="COM4";
	// arduino settings
	SerialPort^ arduino;
	arduino = gcnew SerialPort(portName, baudRate);
	// open port
	try
	{
		arduino->Open();

		do
		{
			// ask on or off
			Console::WriteLine("Type \"on\" to turn the light on or \"off\" to turn it off");
			// get answer
			answer = "on";
			//check that user typed one of the options
			if(String::Compare(answer,"on")==0)
				arduino->WriteLine("1"); // send 1 to arduino
			else if(String::Compare(answer,"off")==0)
				arduino->WriteLine("0"); // send 0 to arduino
			else
				Console::WriteLine(answer+" was not an option");
			// clear the screen
			Console::Clear();
		}while(String::Compare(answer,"yes")==0);
		// close port to arduino
		arduino->Close();
	}
	catch (IO::IOException^ e  )
	{
		Console::WriteLine(e->GetType()->Name+": Port is not ready");
	}
	catch (ArgumentException^ e)
	{
		Console::WriteLine(e->GetType()->Name+": incorrect port name syntax, must start with COM/com");
	}
	// end program
	Console::Write("Press enter to close the program");
	Console::Read();
    return 0;
}

*/




//CLASS KeyJoystick
KeyJoystick::KeyJoystick(HWindow *w) :
	up_key(SDLK_UP),
	down_key(SDLK_DOWN),
	left_key(SDLK_LEFT),
	right_key(SDLK_RIGHT),
	button_key(SDLK_SPACE),
	speed(.1f),
	m_HWindow(w),
	Yaxis(0),
	Xaxis(0),
	button(false)
{
	hDevice = open_port();
}

KeyJoystick::~KeyJoystick()
{
	close_port();
}

bool KeyJoystick::IsValid()
{
	return true;
}

const char *KeyJoystick::GetDescription()
{
	return m_HWindow->GetKeyboardDescription();
}

int KeyJoystick::GetNumAxis()
{
	return 2;
}

int KeyJoystick::GetNumButtons()
{
	return 1;
}

void KeyJoystick::UpdateState()
{
    button = m_HWindow->IsPressed(button_key);

    bool UpState = m_HWindow->IsPressed(up_key);
    bool DownState = m_HWindow->IsPressed(down_key);
    bool LeftState = m_HWindow->IsPressed(left_key);
    bool RightState = m_HWindow->IsPressed(right_key);
	//assert(!(UpState && DownState && LeftState && RightState));

    if (LeftState) Xaxis = H_MIN(Xaxis+2*speed,1);
	else if (RightState)
		Xaxis = H_MAX(Xaxis-2*speed,-1);
	else if (Xaxis>0)
		Xaxis = H_MAX(0,Xaxis-speed);
	else if (Xaxis<0)
		Xaxis = H_MIN(0,Xaxis+speed);

    if (UpState)
		Yaxis = H_MIN(Yaxis+2*speed,1);
	else if (DownState)
		Yaxis = H_MAX(Yaxis-2*speed,-1);
	else if (Yaxis>0)
		Yaxis = H_MAX(0,Yaxis-speed);
	else if (Yaxis<0)
		Yaxis = H_MIN(0,Yaxis+speed);

	if (UpState) send_data("U");
}

REAL KeyJoystick::GetAxisPos(int i)
{
	switch (i)
	{
	case 0: return Xaxis;
	case 1: return Yaxis;
	default: return 0;
	}
	return 0;
}

bool KeyJoystick::GetButtonPos(int i)
{
	return (i==0) ? button : 0;
}

bool KeyJoystick::SetForceFeedback(REAL x, REAL y)
{
	return false;
}


//Added by Alex

HANDLE KeyJoystick::open_port(){
	bool debug = true;
	HANDLE hDev = CreateFile("\\\\.\\COM4", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);

	if (hDev == INVALID_HANDLE_VALUE){
		return NULL;
	}

	if (debug) printf("Port opened. \n");
	DCB lpTest;
	GetCommState(hDev, &lpTest);	//Accepts the device handle and the pointer to the state of the device
	lpTest.BaudRate = CBR_9600;
	lpTest.ByteSize = 8;
	lpTest.Parity = NOPARITY;
	lpTest.StopBits = ONESTOPBIT;
	SetCommState(hDev, &lpTest);

	return hDev;
}

void KeyJoystick::close_port(){
		CloseHandle(hDevice);
}

int KeyJoystick::send_data(char temp[]){
	DWORD btsIO;
	WriteFile(hDevice, &temp, strlen(temp), &btsIO, NULL);

	return 0;
}