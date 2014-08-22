// TextBuddy.cpp
// Alex Yao Yang
// A0097699X

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
ofstream writeFile;
ifstream readFile;
const char delim = '^';
string fileName;
const string defaultFileName = "mytextfile.txt";
const string unableToOpenFile = "Unable to open file";
const string noParamsError = "Please specify parameters!";
const string add = "add";
const string display = "display";
const string del = "delete";
const string clear = "clear";
const string quit = "exit";
const int overwrite = 0;
const int append = 1;

void getFileNameFromArgument(char* argv[]);
void getFileReady();
void printWelcome();
void listenForCommands();
string getInputString();
void printMsg(string msg);
void delegateTaskWithCommand(string& cmd);
bool searchKeyInString(string& cmd, string key);
string getCommandParams(string& cmd);
void closeFiles();
void writeToFile(string& toStore, int mode);
void deleteFromFile(string& l);
void displayFromFile();
bool isEmptyFile();
void clearFileContents();

int main(int argc, char* argv[]){
	getFileNameFromArgument(argv);
	getFileReady();
	printWelcome();
	listenForCommands();

	return 0;
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

void listenForCommands(){
	while (1){
		cout << "command: ";
		delegateTaskWithCommand(getInputString());
	}
}

string getInputString(){
	string cmd;
	getline(cin, cmd);
	return cmd;
}

void printMsg(string msg){
	cout << msg << endl;
}

void delegateTaskWithCommand(string& cmd){
	closeFiles(); //prepare for new operations

	if (searchKeyInString(cmd,add)){
		if (getCommandParams(cmd).empty()){
			printMsg(noParamsError);
		}
		else {
			writeToFile(getCommandParams(cmd), append);
		}
	}
	else if (searchKeyInString(cmd, del)){
		if (getCommandParams(cmd).empty()){
			printMsg(noParamsError);
		}
		else {
			deleteFromFile(getCommandParams(cmd));
		}
	}
	else if (searchKeyInString(cmd, display)){
		displayFromFile();
	}
	else if (searchKeyInString(cmd, clear)){
		clearFileContents();
	}
	else if (searchKeyInString(cmd, quit)){
		exit(0);
	}
	else {
		printMsg("Invalid command, please re-enter.");
	}
}

bool searchKeyInString(string& cmd, string key){
	return cmd.find(key) == 0;
}

string getCommandParams(string& cmd){
	int found = cmd.find(' ');
	if (found < 0){
		return "";
	}
	else {
		return cmd.substr(found + 1);
	}
}

void closeFiles(){
	readFile.close();
	writeFile.close();
}

void writeToFile(string& toStore, int mode){
	if (mode == append){
		writeFile.open(fileName, ios::app);
	}
	else if (mode == overwrite){
		writeFile.open(fileName);
	}
	if (writeFile.good()){
		writeFile << toStore;
		if (mode == 1){
			writeFile << delim;
			printMsg("added to " + fileName + ": \"" + toStore + "\"");
		}
	}
	else {
		printMsg(unableToOpenFile);
	}
}

void deleteFromFile(string& l){
	readFile.open(fileName);
	if (isEmptyFile()){
		printMsg(fileName + " is empty");
	}
	else if (readFile.good()){
		int line = stoi(l);
		int start = 0;
		int end = 0;
		string value;
		getline(readFile, value);
		for (int i = 0; i < line; i++){
			start = end;
			end = value.find(delim, start) + 1;
		}
		printMsg("deleted from " + fileName + ": " + value.substr(start, end - start - 1));
		value.erase(start, end - start);
		readFile.close();
		writeToFile(value, overwrite);
	}
	else {
		printMsg(unableToOpenFile);
	}
}

void displayFromFile() {
	readFile.open(fileName);
	if (isEmptyFile()){
		printMsg(fileName + " is empty");
	}
	else if (readFile.good()){
		string line;
		int i = 1;
		while (!readFile.eof()){
			getline(readFile, line, delim);
			if (line != ""){
				printMsg(i + ". " + line);
				i++;
			}
		}
	}
	else {
		printMsg(unableToOpenFile);
	}
}

bool isEmptyFile(){
	readFile.seekg(0, ios::end);
	int length = (int)readFile.tellg();
	readFile.seekg(0, ios::beg);
	return length == 0;
}

void clearFileContents(){
	remove(fileName.c_str());
	printMsg("all content deleted from " + fileName);
	writeFile.open(fileName);
}
