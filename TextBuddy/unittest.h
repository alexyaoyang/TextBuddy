#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
#pragma once

#ifdef EXPORT_TEST_FUNCTIONS

#define TEXTBUDDY __declspec(dllexport)
#else
#define TEXTBUDDY
#endif

TEXTBUDDY string getDisplayFromFile();