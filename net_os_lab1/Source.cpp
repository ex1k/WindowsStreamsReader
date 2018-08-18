#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <iostream>
using namespace std;

void create_and_write(wchar_t* wfilename, char* buff) {
	DWORD wCount;
	HANDLE file = CreateFile(wfilename, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
	if (file == INVALID_HANDLE_VALUE) {
		cout << "Cannot open file" << endl;
		ExitProcess(1);
	}
	else
		WriteFile(file, buff, strlen(buff), &wCount, NULL);
	CloseHandle(file);
	return;
}

char* read_file(wchar_t* wfilename, char* buff) {
	DWORD rCount;
	HANDLE file = CreateFile(wfilename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (file == INVALID_HANDLE_VALUE) {
		cout << "Cannot open file" << endl;
		ExitProcess(1);
	}
	else 
		ReadFile(file, buff, 1000, &rCount, NULL);
	CloseHandle(file);
	return buff;
}

BOOL WINAPI consoleHandler(DWORD signal) {
	if (signal == CTRL_C_EVENT) {
		return 0;
	}
	return TRUE;
}

int main() {
	HANDLE file, stream;
	char filename[50];
	char buff[1000];
	wchar_t wname[100];
	int action;
	
	system("color F0");
	
	if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
		cout << "Couldn't set control handler" << endl;
		Sleep(5000);
		return 1;
	}

	while (1) {
		cout << "Type action:" << endl;
		cout << "1 - write file" << endl;
		cout << "2 - read file" << endl;		
		cin.getline(buff, sizeof(buff));
		action = atoi(buff);
		memset(filename, 0, sizeof(filename));
		switch (action) {
			case 1:
				cout << "Type file name:" << endl;
				cin.getline(filename, sizeof(filename));
				cout << "Type text:" << endl;
				cin.getline(buff, sizeof(buff));
				mbstowcs(wname, filename, strlen(filename) + 1);
				create_and_write(wname, buff);
				wmemset(wname, 0, sizeof(wname));
				memset(buff, 0, sizeof(buff));
				break;
			case 2:
				cout << "Type filename to read:" << endl;
				cin.getline(filename, sizeof(filename));
				mbstowcs(wname, filename, strlen(filename) + 1);
				memset(buff, 0, sizeof(buff));
				cout << "File content:" << endl;
				cout << read_file(wname, buff) << endl;
				memset(buff, 0, sizeof(buff));
				break;
			default:
				break;
		}
	}
}