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
const string ADD = "add";
const string display = "display";
const string del = "delete";
const string clear = "clear";
const string quit = "exit";
const int overwrite = 0;
const int append = 1;

void getFileNameFromArgument(char* argv[]);
void makeFile();
void printWelcome();
void listenForCommands();
void printMsg(string msg);
void delegateTaskWithCommand(string cmd);
void closeFiles();
void writeToFile(string toStore, int mode);
void deleteFromFile(string l);
void displayFromFile();
void clearFileContents();
bool isEmptyFile();
bool searchKeyInString(string& cmd, string key);
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
    if (!argv[1]){
        printMsg("Argument not found, defaulting file name to " + DEFAULT_FILE_NAME);
        fileName = DEFAULT_FILE_NAME;
    }
    else {
        fileName = argv[1];
        if(fileName.find(".txt")== string::npos){
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
}

void delegateTaskWithCommand(string cmd){
    closeFiles(); //prepare for new operations
    
    if (searchKeyInString(cmd, ADD)){
        if (getCommandParams(cmd).empty()){
            printMsg(MESSAGE_PARAM_ERROR);
        }
        else {
            writeToFile(getCommandParams(cmd), append);
        }
    }
    else if (searchKeyInString(cmd, del)){
        if (getCommandParams(cmd).empty()){
            printMsg(MESSAGE_PARAM_ERROR);
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

void listenForCommands(){
    while (1){
        cout << "command: ";
        delegateTaskWithCommand(getInputString());
    }
}

bool searchKeyInString(string& cmd, string key){
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
    if (mode == append){
        writeFile.open(fileName, ios::app);
    }
    else if (mode == overwrite){
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

void deleteFromFile(string l){
    readFile.open(fileName);
    if (isEmptyFile()){
        printMsg(fileName + " is empty");
    }
    else if (readFile.good()){
        int line = stoi(l);
        if(line <= 0){
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
        if(toDel.empty()){
            printMsg(MESSAGE_PARAM_ERROR);
            return;
        }
        printMsg("deleted from " + fileName + ": " + toDel);
        value.erase(start, end - start);
        readFile.close();
        writeToFile(value, overwrite);
    }
    else {
        printMsg(MESSAGE_UNABLE_TO_OPEN_FILE);
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
            getline(readFile, line, DELIM);
            if (line != ""){
                cout<<i;
                printMsg(". " + line);
                i++;
            }
        }
    }
    else {
        printMsg(MESSAGE_UNABLE_TO_OPEN_FILE);
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
