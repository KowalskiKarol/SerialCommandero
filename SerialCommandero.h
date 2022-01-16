#pragma once

#ifndef SerialCommandero_h
#define SerialCommandero_h
#include "Arduino.h"

class SerialCommandero
{

#ifndef MAX_COMMAND_LENGTH
#define MAX_COMMAND_LENGTH 50
#endif
#ifndef PARAM_LENGTH
#define PARAM_LENGTH 10
#endif
#ifndef TEST_MODE
#define TEST_MODE false
#endif
	public:
		char cmd[MAX_COMMAND_LENGTH];
		char serialBuffer[MAX_COMMAND_LENGTH] = "";
		char param1[PARAM_LENGTH];
		char param2[PARAM_LENGTH];
		char param3[PARAM_LENGTH];
		int paramCount = 0;
		byte incomingByte;

		void init(char* buff, bool toUCase = false);
		int strLoc(char* str, char soughtChar, int startIndex);
		int strLoc1(char* str, char soughtChar, int startIndex);
		void strSubstr1(char* str, char* retVal, int startIndex, int endIndex, bool toUpperCase);
		void strSubstr(char* str, char* retVal, int startIndex, int endIndex, bool toUpperCase);
		void strConcat(char* buff, char val);
		bool isSerialCommandAvailable();
};

#endif