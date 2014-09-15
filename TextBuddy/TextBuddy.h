#ifndef TEXTBUDDY_H
#define TEXTBUDDY_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

	void getFileNameFromArgument(char* argv[]);
	void makeFile();
	void printWelcome();
	void listenForCommands();
	void printMsg(string msg);
	void delegateTaskWithCommand(string cmd);
	void getParamAdd(string cmd);
	void getParamDelete(string cmd);
	void closeFiles();
	void writeToFile(string toStore, int mode);
	void deleteFromFile(string lineString);
	void deleteLine(string lineString);
	void displayFromFile();
	void printFromFile();
	void clearFileContents();
	bool isEmptyFile();
	bool keyFoundInString(string& cmd, string key);
	string getInputString();
	string getCommandParams(string cmd);
	string trim(string& str);

#endif