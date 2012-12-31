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

	//char* create_packet();
	char* create_packet(byte state, byte incline, byte angle, byte vibration, byte resistance);

	int send_data(char* temp);
	int receive_data();

	bool open_port();
	bool close_port();

	static HANDLE hDevice;
	static bool isConnected;
	static char buffer[5];
	static DWORD read;
};

#endif