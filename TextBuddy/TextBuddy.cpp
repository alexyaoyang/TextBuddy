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
	else cout << "Unable to open file" << endl;
}

bool isEmpty(){
	readFile.seekg(0, ios::end);
	int length = readFile.tellg();
	readFile.seekg(0, ios::beg);
	return length == 0;
}

void displayFromFile(){
	readFile.open(fileName);
	if (isEmpty()){
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
		else cout << "Unable to open file" << endl;
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
	else cout << "Unable to open file" << endl;
}

void deleteFileContents(){
	remove(fileName.c_str());
	cout << "all content deleted from " << fileName << endl;
	writeFile.open(fileName);
}

void listenForCommand(){
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
			deleteFileContents();
		}
		else if (cmd.find("exit") == 0){
			break;
		}
		else{
			cout << "Invalid command, please re-enter." << endl;
		}
	}
}

int main(int argc, char* argv[]){
	fileName = argv[1] ? argv[1] : "mytextfile.txt";
	readFile.open(fileName);
	if (!readFile.good()){
		writeFile.open(fileName);
	}
	cout << "Welcome to TextBuddy. " << fileName << " is ready for use" <<endl;

	listenForCommand();
	return 0;
}

