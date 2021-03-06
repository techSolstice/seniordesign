#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include "ArduinoComm.h"

using namespace std;

/*
	This object is instantiated by the constructor of the KeyJoystick class, part of H_Input.cpp
*/

	bool ArduinoCom::isConnected;
	HANDLE ArduinoCom::hDevice;

ArduinoCom::ArduinoCom(){

	if (open_port()) ArduinoCom::isConnected = true;
	else{
		ArduinoCom::isConnected = false;
		ArduinoCom::hDevice = NULL;
	}
}

ArduinoCom::~ArduinoCom(){
	if (ArduinoCom::isConnected){
		close_port();
	}
}


char* ArduinoCom::create_packet(byte state, byte incline, byte angle, byte vibration, byte resistance){
	char packet[5];
	packet[0] = state;
	packet[1] = incline;
	packet[2] = angle;
	packet[3] = vibration;
	packet[4] = resistance;

	return packet;
}


int ArduinoCom::send_data(char* temp){
	if (open_port()){
		DWORD btsIO;
		WriteFile(ArduinoCom::hDevice, &temp, strlen(temp), &btsIO, NULL);
	}
	return 0;
}

int ArduinoCom::receive_data(){
	if (open_port()){
		if (ReadFile(ArduinoCom::hDevice, buffer, sizeof(buffer), &read, NULL)){
			;
		}
	}
	return 0;
}


/**
	Port operations
*/

bool ArduinoCom::open_port(){
	bool debug = true;

	ArduinoCom::hDevice = CreateFile("\\\\.\\COM4", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);

	if (ArduinoCom::hDevice == INVALID_HANDLE_VALUE){
		ArduinoCom::hDevice = NULL;
		return false;
	}

	if (debug) printf("Port opened. \n");
	DCB lpTest;
	GetCommState(ArduinoCom::hDevice, &lpTest);	//Accepts the device handle and the pointer to the state of the device
	lpTest.BaudRate = CBR_9600;
	lpTest.ByteSize = 8;
	lpTest.Parity = NOPARITY;
	lpTest.StopBits = ONESTOPBIT;
	SetCommState(ArduinoCom::hDevice, &lpTest);

	return true;
}

bool ArduinoCom::close_port(){
	ArduinoCom::isConnected = false;
	if (NULL != ArduinoCom::hDevice)
		CloseHandle(ArduinoCom::hDevice);

	return true;
}

