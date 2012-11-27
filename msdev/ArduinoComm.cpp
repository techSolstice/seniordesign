#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include "ArduinoComm.h";

using namespace std;

int send_data(char temp[]){
	bool debug = true;
	HANDLE hDevice = CreateFile("\\\\.\\COM4", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);

	if (hDevice == INVALID_HANDLE_VALUE){
		return 1;
	}

	if (debug) printf("Port opened. \n");
	DCB lpTest;
	GetCommState(hDevice, &lpTest);	//Accepts the device handle and the pointer to the state of the device
	lpTest.BaudRate = CBR_9600;
	lpTest.ByteSize = 8;
	lpTest.Parity = NOPARITY;
	lpTest.StopBits = ONESTOPBIT;
	SetCommState(hDevice, &lpTest);

	DWORD btsIO;
	WriteFile(hDevice, &temp, strlen(temp), &btsIO, NULL);

	CloseHandle(hDevice);

	return 0;
}