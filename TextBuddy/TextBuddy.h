#define TEXTBUDDY __declspec(dllexport)

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

class TextBuddy{
public:
	int main(int argc, char* argv[]);
	TEXTBUDDY int returnOne();
	TEXTBUDDY string getDisplayFromFile();
	TEXTBUDDY void getFileNameFromArgument(char* argv[]);
	TEXTBUDDY void makeFile();
	TEXTBUDDY void printWelcome();
	TEXTBUDDY void listenForCommands();
	TEXTBUDDY void printMsg(string msg);
	TEXTBUDDY void delegateTaskWithCommand(string cmd);
	TEXTBUDDY void getParamAdd(string cmd);
	TEXTBUDDY void getParamDelete(string cmd);
	TEXTBUDDY void TextBuddy::searchInFile(string key);
	TEXTBUDDY void closeFiles();
	TEXTBUDDY void writeToFile(string toStore, int mode);
	TEXTBUDDY void deleteFromFile(string lineString);
	TEXTBUDDY void deleteLine(string lineString);
	TEXTBUDDY void displayFromFile();
	TEXTBUDDY void readFromFile(int printMode, string key);
	TEXTBUDDY void printSorted();
	TEXTBUDDY void printFromStorage();
	TEXTBUDDY void readIntoStorage();
	TEXTBUDDY string returnFromFile();
	TEXTBUDDY void clearFileContents();
	TEXTBUDDY bool isEmptyFile();
	TEXTBUDDY bool keyFoundInString(string& cmd, string key);
	TEXTBUDDY string getInputString();
	TEXTBUDDY string getCommandParams(string cmd);
	TEXTBUDDY string trim(string& str);
	const char DELIM = '^';
	const string DEFAULT_FILE_NAME = "mytextfile.txt";
	const string MESSAGE_UNABLE_TO_OPEN_FILE = "Unable to open file";
	const string MESSAGE_PARAM_ERROR = "Please specify correct parameters!";
	const string MESSAGE_ARGUMENT_ERROR = "Argument not found, defaulting file name to ";
	const string MESSAGE_CLEARED = "all content deleted from ";
	const string MESSAGE_INVALID_COMMAND = "Invalid command, please re-enter.";
	const string COMMAND_ADD = "add";
	const string COMMAND_DISPLAY = "display";
	const string COMMAND_DELETE = "delete";
	const string COMMAND_CLEAR = "clear"; 
	const string COMMAND_SEARCH = "search";
	const string COMMAND_SORT = "sort";
	const string COMMAND_QUIT = "exit";
	const int OPERATION_OVERWRITE = 0;
	const int OPERATION_APPEND = 1;
	const int PRINT_MODE_DISPLAY = 0;
	const int PRINT_MODE_SEARCH = 1;
	const int PRINT_MODE_STORE = 2;
	ofstream writeFile;
	ifstream readFile;
	string fileName;
	set<string> storage;
};