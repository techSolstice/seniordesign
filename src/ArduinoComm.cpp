#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include "ArduinoComm.h"

using namespace std;

ArduinoCom::ArduinoCom(){
	if (open_port()) isConnected = true;
	else isConnected = false;
}

ArduinoCom::~ArduinoCom(){
	if (isConnected) CloseHandle(hDevice);
}

bool ArduinoCom::open_port(){
	bool debug = true;

	hDevice = CreateFile("\\\\.\\COM4", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);

	if (hDevice == INVALID_HANDLE_VALUE){
		hDevice = NULL;
		return false;
	}

	if (debug) printf("Port opened. \n");
	DCB lpTest;
	GetCommState(hDevice, &lpTest);	//Accepts the device handle and the pointer to the state of the device
	lpTest.BaudRate = CBR_9600;
	lpTest.ByteSize = 8;
	lpTest.Parity = NOPARITY;
	lpTest.StopBits = ONESTOPBIT;
	SetCommState(hDevice, &lpTest);

	return true;
}

bool ArduinoCom::close_port(){
	isConnected = false;
	CloseHandle(hDevice);
	return true;
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

int ArduinoCom::send_data(char temp[]){
	if (isConnected){
		DWORD btsIO;
		WriteFile(hDevice, &temp, strlen(temp), &btsIO, NULL);
	}
	return 0;
}
