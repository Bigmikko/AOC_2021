/////////////////////////////
/////	Advent of Code 	/////
/////	2021	Day 2	/////
/////			/////
/////	by Bigmikko	/////
/////////////////////////////

#include "header.h"

//Used for opening the file
#define DAY 2

class Submarine{
//The submarine class
private:
	int x, y;
public:
	vector <int> num;
	vector <string> movement;

	void fill();
	int problem_1();
	int problem_2();
	Submarine() {
		x = 0;
		y = 0;
	}
};

void Submarine::fill() {
//Saves the content from the input file to num and movement
	fstream file;
	int i;
	string s;
	open_file(file, DAY);

	while (file >> s >> i) {
		movement.push_back(s);
		num.push_back(i);
	}
}
int Submarine::problem_1() {
//Checks the movements and returns the coordinates multiplied
	int i;

	for (i = 0; i < num.size(); i++) { 
		if (movement[i] == "forward")
			x += num[i];
		else if (movement[i] == "down")
			y += num[i];
		else if (movement[i] == "up")
			y -= num[i];
		else
			exit (0);
	}
	return x * y;
}

int Submarine::problem_2() {
//Checks the movements and saves it in the X Y coordinates
	int i;
	int aim;
	
	aim = 0;
	for (i = 0; i < num.size(); i++) {
		if (movement[i] == "forward") {
			x += num[i];
			y += (num[i] * aim);
		}
		else if (movement[i] == "down")
			aim += num[i];

		else if (movement[i] == "up")
			aim -= num[i];
		else
			exit (0);
	}
	return x*y;
}

void day_2()
{
	Submarine sub;

	//Fills the sub class with the input from the file
	sub.fill();

	//sub.problem_1() for problem 1
	//sub.problem_2() for problem 2
	cout << sub.problem_2();

	return;
}