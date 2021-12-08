/////////////////////////////
/////	Advent of Code 	/////
/////	2021		/////
/////			/////
/////	by Bigmikko	/////
/////////////////////////////

#include "header.h"

void open_file(std::fstream& file, int day) {
	//Opens the file

	file.open(input.txt, ios::in);

	//Checks if it can be opened, otherwise quits out
	if (!file.is_open()) {
		cout << "Error Reading File";
		exit(0);
	}
	return;
}