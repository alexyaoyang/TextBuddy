// TextBuddy.cpp
// Alex Yao Yang
// A0097699X
// File name in arguments can be empty, will create a text file with default name if file name not found in arguments.
// This program saves the file after user operations: add, delete and clear.
// Reasons are
// 1) only these commands affects the file
// 2) avoid unnecessary writes
// 3) allows program to run faster
// To get duplicate of output file, run code without file name, with the given
// TestInput.txt below and output to another text file.

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

ofstream writeFile;
ifstream readFile;
string fileName;
const char DELIM = '^';
const string DEFAULT_FILE_NAME = "mytextfile.txt";
const string MESSAGE_UNABLE_TO_OPEN_FILE = "Unable to open file";
const string MESSAGE_PARAM_ERROR = "Please specify correct parameters!";
const string MESSAGE_ARGUMENT_ERROR = "Argument not found, defaulting file name to ";
const string MESSAGE_CLEARED = "all content deleted from ";
const string COMMAND_ADD = "add";
const string COMMAND_DISPLAY = "display";
const string COMMAND_DELETE = "delete";
const string COMMAND_CLEAR = "clear";
const string COMMAND_QUIT = "exit";
const int OPERATION_OVERWRITE = 0;
const int OPERATION_APPEND = 1;

void getFileNameFromArgument(char* argv[]);
void makeFile();
void printWelcome();
void listenForCommands();
void printMsg(string msg);
void delegateTaskWithCommand(string cmd);
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

int main(int argc, char* argv[]){
    getFileNameFromArgument(argv);
    makeFile();
    printWelcome();
    listenForCommands();
    
    return 0;
}

void getFileNameFromArgument(char* argv[]){
    if (!argv[1]){ //if argument not found
        printMsg(MESSAGE_ARGUMENT_ERROR + DEFAULT_FILE_NAME);
        fileName = DEFAULT_FILE_NAME;
    }
    else {
        fileName = argv[1];
        if(fileName.find(".txt")== string::npos){ //if .txt extension not found
            fileName = fileName + ".txt";
        }
    }
}

void makeFile(){
    writeFile.open(fileName);
}

void printWelcome(){
    printMsg("Welcome to TextBuddy. " + fileName + " is ready for use");
}

string getInputString(){
    string cmd;
    getline(cin, cmd);
    return cmd;
}

void printMsg(string msg){
    cout << msg << endl;
    //make to printf
}

void delegateTaskWithCommand(string cmd){
    closeFiles(); //prepare for new operations
    
    if (keyFoundInString(cmd, COMMAND_ADD)){
        if (getCommandParams(cmd).empty()){
            printMsg(MESSAGE_PARAM_ERROR);
        }
        else {
            writeToFile(getCommandParams(cmd), OPERATION_APPEND);
        }
    }
    else if (keyFoundInString(cmd, COMMAND_DELETE)){
        if (getCommandParams(cmd).empty()){
            printMsg(MESSAGE_PARAM_ERROR);
        }
        else {
            deleteFromFile(getCommandParams(cmd));
        }
    }
    else if (keyFoundInString(cmd, COMMAND_DISPLAY)){
        displayFromFile();
    }
    else if (keyFoundInString(cmd, COMMAND_CLEAR)){
        clearFileContents();
    }
    else if (keyFoundInString(cmd, COMMAND_QUIT)){
        exit(0);
    }
    else {
        printMsg("Invalid command, please re-enter.");
    }
}

void listenForCommands(){
    while (1){
        cout << "command: ";
        delegateTaskWithCommand(getInputString());
    }
}

bool keyFoundInString(string& cmd, string key){
    return cmd.find(key) == 0;
}

string getCommandParams(string cmd){
    int found = cmd.find(' ');
    if (found == string::npos){
        return "";
    }
    else {
        cmd = cmd.substr(found + 1);
        return trim(cmd);
    }
}

string trim(string& str){
    int first = str.find_first_not_of(' ');
    int last  = str.find_last_not_of(' ');
    if(first == string::npos || last == string::npos){
        return "";
    }
    return str.substr(first, last-first+1);
}

void closeFiles(){
    readFile.close();
    writeFile.close();
}

void writeToFile(string toStore, int mode){
    if (mode == OPERATION_APPEND){
        writeFile.open(fileName, ios::app);
    }
    else if (mode == OPERATION_OVERWRITE){
        writeFile.open(fileName);
    }
    if (writeFile.good()){
        writeFile << toStore;
        if (mode == 1){
            writeFile << DELIM;
            printMsg("added to " + fileName + ": \"" + toStore + "\"");
        }
    }
    else {
        printMsg(MESSAGE_UNABLE_TO_OPEN_FILE);
    }
}

void deleteFromFile(string lineString){
    readFile.open(fileName);
    if (isEmptyFile()){
        printMsg(fileName + " is empty");
    }
    else if (readFile.good()){
		deleteLine(lineString);
    }
    else {
        printMsg(MESSAGE_UNABLE_TO_OPEN_FILE);
    }
}

void deleteLine(string lineString){
	int line;
	try{
		line = stoi(lineString);
	}
	catch(...){
		printMsg(MESSAGE_PARAM_ERROR);
		return;
	}
	int start = 0;
	int end = 0;
	string value;
	getline(readFile, value);
	for (int i = 0; i < line; i++){
		start = end;
		end = value.find(DELIM, start) + 1;
	}
	string toDel = value.substr(start, end - start - 1);
	if (toDel.empty()){
		printMsg(MESSAGE_PARAM_ERROR);
		return;
	}
	printMsg("deleted from " + fileName + ": " + toDel);
	value.erase(start, end - start);
	readFile.close();
	writeToFile(value, OPERATION_OVERWRITE);
}

void displayFromFile() {
    readFile.open(fileName);
    if (isEmptyFile()){
        printMsg(fileName + " is empty");
    }
    else if (readFile.good()){
        printFromFile();
    }
    else {
        printMsg(MESSAGE_UNABLE_TO_OPEN_FILE);
    }
}

void printFromFile(){
    string line;
    int i = 1;
    while (!readFile.eof()){
        getline(readFile, line, DELIM);
        if (line != ""){
            printMsg(to_string(i) + ". " + line);
            i++;
        }
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
    printMsg(MESSAGE_CLEARED + fileName);
    writeFile.open(fileName);
}
