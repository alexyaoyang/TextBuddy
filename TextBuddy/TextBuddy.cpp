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

#include "TextBuddy.h"

int main(int argc, char* argv[]){
	TextBuddy tb;
	tb.getFileNameFromArgument(argv);
	tb.makeFile();
	tb.printWelcome();
	tb.listenForCommands();

	return 0;
}

TextBuddy::TextBuddy(){
	size = 0;
}

void TextBuddy::getFileNameFromArgument(char* argv[]){
    if (!argv[1]){ //if argument not found
        printMsg(MESSAGE_ARGUMENT_ERROR + DEFAULT_FILE_NAME);
        fileName = DEFAULT_FILE_NAME;
    } else {
        fileName = argv[1];
        if(fileName.find(".txt")== string::npos){ //if .txt extension not found
            fileName = fileName + ".txt";
        }
    }
}

void TextBuddy::makeFile(){
    writeFile.open(fileName);
}

void TextBuddy::printWelcome(){
    printMsg("Welcome to TextBuddy. " + fileName + " is ready for use");
}

string TextBuddy::getInputString(){
    string cmd;
    getline(cin, cmd);
    return cmd;
}

void TextBuddy::printMsg(string msg){
    cout << msg << endl;
}

void TextBuddy::delegateTaskWithCommand(string cmd){
    closeFiles(); //prepare for new operations
    
    if (keyFoundInString(cmd, COMMAND_ADD)){
		getParamAdd(cmd);
    } else if (keyFoundInString(cmd, COMMAND_DELETE)){
		getParamDelete(cmd);
    } else if (keyFoundInString(cmd, COMMAND_DISPLAY)){
		fileOperation(FILE_MODE_DISPLAY, "");
    } else if (keyFoundInString(cmd, COMMAND_CLEAR)){
        clearFileContents();
    } else if (keyFoundInString(cmd, COMMAND_QUIT)){
        exit(0);
    } else if (keyFoundInString(cmd, COMMAND_SEARCH)){
		fileOperation(FILE_MODE_SEARCH, getCommandParams(cmd));
	} else if (keyFoundInString(cmd, COMMAND_SORT)){
		printSorted();
	} else {
        printMsg(MESSAGE_INVALID_COMMAND);
    }
}

void TextBuddy::getParamAdd(string cmd){
	if (getCommandParams(cmd).empty()){
		printMsg(MESSAGE_PARAM_ERROR);
	} else {
		writeToFile(getCommandParams(cmd), OPERATION_APPEND); 
	}
	closeFiles();
}

void TextBuddy::getParamDelete(string cmd){
	if (getCommandParams(cmd).empty()){
		printMsg(MESSAGE_PARAM_ERROR);
	} else {
		fileOperation(FILE_MODE_DELETE, getCommandParams(cmd));
	}
}

void TextBuddy::listenForCommands(){
    while (1){
        cout << "command: ";
        delegateTaskWithCommand(getInputString());
    }
}

bool TextBuddy::keyFoundInString(string& cmd, string key){
    return cmd.find(key) == 0;
}

string TextBuddy::getCommandParams(string cmd){
    int found = cmd.find(' ');
    if (found == string::npos){
        return "";
    } else {
        cmd = cmd.substr(found + 1);
        return trim(cmd);
    }
}

string TextBuddy::trim(string& str){
    int first = str.find_first_not_of(' ');
    int last  = str.find_last_not_of(' ');
    if(first == string::npos || last == string::npos){
        return "";
    }
    return str.substr(first, last-first+1);
}

void TextBuddy::closeFiles(){
    readFile.close();
    writeFile.close();
}

void TextBuddy::writeToFile(string toStore, int mode){
    if (mode == OPERATION_APPEND){
        writeFile.open(fileName, ios::app);
    } else if (mode == OPERATION_OVERWRITE){
        writeFile.open(fileName);
		size = 0;
    }
    if (writeFile.good()){
        writeFile << toStore;
		size++;
        if (mode == 1){
            writeFile << DELIM;
            printMsg("added to " + fileName + ": \"" + toStore + "\"");
        }
    } else {
        printMsg(MESSAGE_UNABLE_TO_OPEN_FILE);
    }
}

void TextBuddy::deleteLine(string lineString){
	int line;
	try {
		line = stoi(lineString);
	} catch(exception e){
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
	size--;
	readFile.close();
	writeToFile(value, OPERATION_OVERWRITE);
}

void TextBuddy::fileOperation(int mode, string key){
	readFile.open(fileName);
	if (isEmptyFile()){
		printMsg(fileName + " is empty");
	} else if (readFile.good()){
		if (mode == FILE_MODE_DELETE){
			deleteLine(key);
		} else if (mode == FILE_MODE_DISPLAY) {
			readFromFile(FILE_MODE_DISPLAY, "");
		} else if (mode == FILE_MODE_SEARCH) {
			readFromFile(FILE_MODE_SEARCH, key);
		} else if (mode == FILE_MODE_STORE) {
			readFromFile(FILE_MODE_STORE, "");
		}
	} else {
		printMsg(MESSAGE_UNABLE_TO_OPEN_FILE);
	}
}

void TextBuddy::readFromFile(int printMode, string key){
    string line;
    int i = 1;
	bool found = false;
    while (!readFile.eof()){
        getline(readFile, line, DELIM);
        if (line != ""){
			if (printMode == FILE_MODE_SEARCH && line.find(key) == string::npos){
				continue;
			} else if (printMode == FILE_MODE_STORE){
				storage.insert(line);
				continue;
			}
            printMsg(to_string(i) + ". " + line);
            i++;
			found = true;
        }
    }
	if (printMode == FILE_MODE_SEARCH && !found){
		printMsg(MESSAGE_NO_RESULTS);
	}
}

void TextBuddy::printSorted(){
	fileOperation(FILE_MODE_STORE, "");
	printFromSet();
}

void TextBuddy::printFromSet(){
	if (storage.size() == 0){
		printMsg(MESSAGE_EMPTY_FILE);
		return;
	}
	int i = 1;
	for (set<string>::iterator it = storage.begin(); it != storage.end(); ++it){
		printMsg(to_string(i) + ". " + *it);
		i++;
	}
}

bool TextBuddy::isEmptyFile(){
    readFile.seekg(0, ios::end);
    int length = (int)readFile.tellg();
    readFile.seekg(0, ios::beg);
    return length == 0;
}

void TextBuddy::clearFileContents(){
    remove(fileName.c_str());
    printMsg(MESSAGE_CLEARED + fileName);
    writeFile.open(fileName);
	size = 0;
}

void TextBuddy::getReadyToTest(){
	fileName = "mytextfile.txt";
	clearFileContents();
	writeToFile("", 0);
	closeFiles();
}

int TextBuddy::getSize(){
	return size;
}

string TextBuddy::returnFromFile(int printMode, string key){
	string line;
	int i = 1;
	bool found = false;
	while (!readFile.eof()){
		getline(readFile, line, DELIM);
		if (line != ""){
			if (printMode == FILE_MODE_SEARCH && line.find(key) == string::npos){
				continue;
			} else if (printMode == FILE_MODE_STORE){
				storage.insert(line);
				continue;
			}
			return to_string(i) + ". " + line;
			i++;
			found = true;
		}
	}
	if (printMode == FILE_MODE_SEARCH && !found){
		return MESSAGE_NO_RESULTS;
	}
}

string TextBuddy::returnSearch(string key){
	readFile.open(fileName);
	if (isEmptyFile()){
		return fileName + " is empty";
	} else if (readFile.good()){
		return returnFromFile(FILE_MODE_SEARCH, key);
	} else {
		return MESSAGE_UNABLE_TO_OPEN_FILE;
	}
}

string TextBuddy::returnSorted(int mode){
	fileOperation(FILE_MODE_STORE, "");
	return returnFromSet(mode);
}

string TextBuddy::returnFromSet(int mode){
	if (storage.size() == 0){
		return MESSAGE_EMPTY_FILE;
	}
	set<string>::iterator it;
	if (mode == SORT_FIRST){
		it = storage.begin();
	} else if (mode == SORT_LAST) {
		it = storage.end();
		it--;
	}

	return *it;
}