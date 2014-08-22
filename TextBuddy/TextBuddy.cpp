// TextBuddy.cpp
// Alex Yao Yang
// A0097699X

#include "stdafx.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
ofstream writeFile;
ifstream readFile;
const char delim = '^';
string fileName;
const string defaultFileName = "mytextfile.txt";
const string unableToOpenFile = "Unable to open file";

void printMsg(string msg){
	cout << msg << endl;
}

void writeToFile(string& toStore,int mode){
	//mode 0 overwrites
	//mode 1 appends
	if (mode == 1){
		writeFile.open(fileName, ios::app);
	}
	else if (mode == 0){
		writeFile.open(fileName);
	}
	if (writeFile.good()){
		writeFile << toStore;
		if (mode == 1){
			writeFile << delim;
			cout << "added to " << fileName << ": \"" << toStore << "\"" << endl;
		}
	}
	else printMsg(unableToOpenFile);
}

bool isEmptyFile(){
	readFile.seekg(0, ios::end);
	int length = (int)readFile.tellg();
	readFile.seekg(0, ios::beg);
	return length == 0;
}

void displayFromFile(){
	readFile.open(fileName);
	if (isEmptyFile()){
		cout << fileName << " is empty" << endl;
	}
	else {
		if (readFile.good()){
			string line;
			int i = 1;
			while (!readFile.eof()){
				getline(readFile, line, delim);
				if (line != ""){
					cout << i << ". " << line << endl;
					i++;
				}
			}
		}
		else printMsg(unableToOpenFile);
	}
}

void deleteFromFile(string& l){
	//need to fix if string is very long
	readFile.open(fileName);
	if (readFile.good()){
		int line = stoi(l), start = 0, end = 0;
		string value;
		getline(readFile, value);
		for (int i = 0; i < line; i++){
			start = end;
			end = value.find(delim,start);
			end++;
		}
		cout << "deleted from " << fileName << ": " << value.substr(start, end - start-1) << endl;
		value.erase(start,end-start);
		readFile.close();
		writeToFile(value, 0);
	}
	else printMsg(unableToOpenFile);
}

void clearFileContents(){
	remove(fileName.c_str());
	cout << "all content deleted from " << fileName << endl;
	writeFile.open(fileName);
}

void listenForCommands(){
	while (1){
		readFile.close();
		writeFile.close();
		cout << "command: ";
		string cmd;
		getline(cin, cmd);

		if (cmd.find("add") == 0){
			writeToFile(cmd.substr(cmd.find_first_of(' ') + 1),1);
		}
		else if (cmd.find("delete") == 0){
			deleteFromFile(cmd != "delete" ? cmd.substr(cmd.find_first_of(' ') + 1) : "");
		}
		else if (cmd.find("display") == 0){
			displayFromFile();
		}
		else if (cmd.find("clear") == 0){
			clearFileContents();
		}
		else if (cmd.find("exit") == 0){
			break;
		}
		else {
			printMsg("Invalid command, please re-enter.");
		}
	}
}

void getFileNameFromArgument(char* argv[]){
	if (!argv[1]){
		printMsg("Argument not found, defaulting file name to " + defaultFileName);
		fileName = defaultFileName;
	}
	else {
		fileName = argv[1];
	}
}

void getFileReady(){
	writeFile.open(fileName);
}

void printWelcome(){
	printMsg("Welcome to TextBuddy. " + fileName + " is ready for use");
}

int main(int argc, char* argv[]){
	getFileNameFromArgument(argv);
	getFileReady();
	printWelcome();
	listenForCommands();
	return 0;
}

