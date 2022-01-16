#include "Arduino.h"
#include "SerialCommandero.h"

#ifndef MAX_COMMAND_LENGTH
#define MAX_COMMAND_LENGTH 50
#endif
#ifndef PARAM_LENGTH
#define PARAM_LENGTH 10
#endif
#ifndef TEST_MODE
#define TEST_MODE false
#endif

	char cmd[MAX_COMMAND_LENGTH];
	char param1[PARAM_LENGTH];
	char param2[PARAM_LENGTH];
	char param3[PARAM_LENGTH];
	int paramCount = 0;

	void SerialCommandero::init(char* buff, bool toUCase = false)
	{
		paramCount = 0;
		int commaIndex1 = 0;
		int commaIndex2 = 0;
		int commaIndex3 = 0;
		commaIndex1 = strLoc1(buff, ',', 0);
		commaIndex2 = strLoc1(buff, ',', commaIndex1 + 1);
		commaIndex3 = strLoc1(buff, ',', commaIndex2 + 1);

		if (commaIndex1 > 0 && commaIndex2 > 0 && commaIndex3 > 0 && commaIndex1 != commaIndex2 && commaIndex2 != commaIndex3)
		{
			//command seems to have 3 params
			strSubstr1(buff, cmd, 0, commaIndex1, toUCase);
			strSubstr1(buff, param1, commaIndex1 + 1, commaIndex2, toUCase);
			strSubstr1(buff, param2, commaIndex2 + 1, commaIndex3, toUCase);
			strSubstr1(buff, param3, commaIndex3 + 1, strlen(buff), toUCase);

			paramCount = 3;
		}
		else if (commaIndex1 > 0 && commaIndex2 > 0 && commaIndex1 != commaIndex2)
		{
			//command seems to have 2 params
			strSubstr1(buff, cmd, 0, commaIndex1, toUCase);
			strSubstr1(buff, param1, commaIndex1 + 1, commaIndex2, toUCase);
			strSubstr1(buff, param2, commaIndex2 + 1, strlen(buff), toUCase);
			param3[0] = 0;
			paramCount = 2;
		}
		else if (commaIndex1 > 0)
		{
			strSubstr1(buff, cmd, 0, commaIndex1, toUCase);
			strSubstr1(buff, param1, commaIndex1 + 1, strlen(buff), toUCase);
			param2[0] = 0;
			param3[0] = 0;

			paramCount = 1;
		}
		else
		{
			strSubstr1(buff, cmd, 0, strlen(buff), toUCase);
			param1[0] = 0;
			param2[0] = 0;
			param3[0] = 0;
			paramCount = 0;
		}
	}
	int SerialCommandero::strLoc1(char* str, char soughtChar, int startIndex)
	{
		char tmpChar;
		for (int i = startIndex;i < strlen(str);i++)
		{
			tmpChar = str[i];
			if (tmpChar == soughtChar) return i;
		}
		return -1;
	}
	void SerialCommandero::strSubstr1(char* str, char* retVal, int startIndex, int endIndex, bool toUpperCase)
	{
		int cntr = 0;
		for (int i = startIndex;i < endIndex;i++)
		{
			if (toUpperCase)
			{
				retVal[cntr] = toupper(str[i]);
			}
			else
			{
				retVal[cntr] = str[i];
			}
			cntr++;
		}
		retVal[cntr] = 0;
	}
	int SerialCommandero::strLoc(char* str, char soughtChar, int startIndex)
	{
		char tmpChar;
		for (int i = startIndex;i < strlen(str);i++)
		{
			tmpChar = str[i];
			if (tmpChar == soughtChar) return i;
		}
		return -1;
	}
	void SerialCommandero::strSubstr(char* str, char* retVal, int startIndex, int endIndex, bool toUpperCase)
	{
		int cntr = 0;
		for (int i = startIndex;i < endIndex;i++)
		{
			if (toUpperCase)
			{
				retVal[cntr] = toupper(str[i]);
			}
			else
			{
				retVal[cntr] = str[i];
			}
			cntr++;
		}
		retVal[cntr] = 0;
	}
	void SerialCommandero::strConcat(char* buff, char val)
	{
		int lenBefore = strlen(buff);
		buff[lenBefore] = val;
		buff[lenBefore + 1] = 0;
	}
	bool SerialCommandero::isSerialCommandAvailable()
	{
		if (Serial.available() > 0)
		{
			// read the incoming byte:
			incomingByte = Serial.read();
			if (incomingByte != 10 && incomingByte != 13)
			{
				strConcat(serialBuffer, incomingByte);
				return false;
			}
			else //either 10 or 13
			{
				if (strlen(serialBuffer) > 1)
				{
					if (TEST_MODE)
					{
						Serial.print("serbuf: ");
						Serial.println(serialBuffer);
						delay(200);
					}

					init(serialBuffer, true);

					if (TEST_MODE)
					{
						Serial.print("cmd: ");
						Serial.println(cmd);
						Serial.print("p1: ");
						Serial.println(param1);
						Serial.print("p2: ");
						Serial.println(param2);
						Serial.print("p3: ");
						Serial.println(param3);
						delay(200);
					}
					serialBuffer[0] = 0;
					return true;
				}
				else
				{
					serialBuffer[0] = 0;
					return false;
				}
			}
		}
		return false;
	}
