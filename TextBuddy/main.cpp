#include "TextBuddy.h"

int main(int argc, char* argv[]){
	TextBuddy tb;

	tb.getFileNameFromArgument(argv);
	tb.makeFile();
	tb.printWelcome();
	tb.listenForCommands();

	return 0;
}