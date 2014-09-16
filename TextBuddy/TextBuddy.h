#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class TextBuddy{
public:
	TextBuddy(void);
	~TextBuddy(void);
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
	string getDisplayFromFile();
	void printFromFile();
	string returnFromFile();
	void clearFileContents();
	bool isEmptyFile();
	bool keyFoundInString(string& cmd, string key);
	string getInputString();
	string getCommandParams(string cmd);
	string trim(string& str);
	ofstream writeFile;
	ifstream readFile;
	string fileName;
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
	const string COMMAND_QUIT = "exit";
	const int OPERATION_OVERWRITE = 0;
	const int OPERATION_APPEND = 1;
};