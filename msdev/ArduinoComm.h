#ifndef _ARDUINO_COMM_H
#define _ARDUINO_COMM_H

#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>

using namespace std;

class ArduinoCom{
public:
	ArduinoCom();
	~ArduinoCom();
//private:	TODO this will be private once this class is completed
	int send_data(char temp[]);
	bool open_port();
	bool close_port();
	HANDLE hDevice;
	bool isConnected;
};

#endif