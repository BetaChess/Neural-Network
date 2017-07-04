#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>

#include "words.h"

std::ifstream FILEI;

words::words() 
{

}


double words::char_to_int(char input) {
	char temp = toupper(input);
	double value;

	if (temp == 'Z') {
		value = 1;
	}
	else if (temp == 'Y') {
		value = 25 / 26.0;
	}
	else if (temp == 'X') {
		value = 24 / 26.0;
	}
	else if (temp == 'W') {
		value = 23 / 26.0;
	}
	else if (temp == 'V') {
		value = 22 / 26.0;
	}
	else if (temp == 'U') {
		value = 21 / 26.0; 
	}
	else if (temp == 'T') {
		value = 20 / 26.0; 
	}
	else if (temp == 'S') {
		value = 19 / 26.0;
	}
	else if (temp == 'R') {
		value = 18 / 26.0;
	}
	else if (temp == 'Q') {
		value = 17 / 26.0;
	}
	else if (temp == 'P') {
		value = 16 / 26.0;
	}
	else if (temp == 'O') {
		value = 15 / 26.0;
	}
	else if (temp == 'N') {
		value = 14 / 26.0;
	}
	else if (temp == 'M') {
		value = 13 / 26.0;
	}
	else if (temp == 'L') {
		value = 12 / 26.0;
	}
	else if (temp == 'K') {
		value = 11 / 26.0;
	}
	else if (temp == 'J') {
		value = 10 / 26.0;
	}
	else if (temp == 'I') {
		value = 9 / 26.0;
	}
	else if (temp == 'H') {
		value = 8 / 26.0;
	}
	else if (temp == 'G') {
		value = 7 / 26.0;
	}
	else if (temp == 'F') {
		value = 6 / 26.0;
	}
	else if (temp == 'E') {
		value = 5 / 26.0;
	}
	else if (temp == 'D') {
		value = 4 / 26.0;
	}
	else if (temp == 'C') {
		value = 3 / 26.0;
	}
	else if (temp == 'B') {
		value = 2 / 26.0;
	}
	else if (temp == 'A') {
		value = 1 / 26.0;
	}
	else {
		value = 0.0;
	}
	return value;
}