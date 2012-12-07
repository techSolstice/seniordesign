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
	char* create_packet();
//private:	TODO this will be private once this class is completed
	int send_data(char* temp);
	bool open_port();
	char* create_packet(byte state, byte incline, byte angle, byte vibration, byte resistance);
	bool close_port();
	static HANDLE hDevice;
	static bool isConnected;
};

#endif