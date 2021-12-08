/////////////////////////////////
/////	Advent of Code 2021	/////
/////		Day 3			/////
/////						/////
/////	by Bigmikko			/////
/////////////////////////////////

#include "header.h"

//Used for opening the file
#define DAY 3

class Lifesupport {
//Lifesupport class
private:
	vector <vector <int>> matrix;
	vector <int> keepers;

	int binary_to_decimal(vector <int> binaryNum);
	void reset_keepers();
	int keep_one(int keep, int position);
	void purge(int keep, int position);

public:
	void fill();
	int problem1();
	int problem2();
};

int Lifesupport::binary_to_decimal(vector <int> binaryNum) {
//Takes an int vector where each element is a 0 or 1 and returns the decimal number
	int temp;
	int i;

	temp = 0;
	for (i = 0; i < binaryNum.size(); i++) {
		if (binaryNum[binaryNum.size() -1 - i] == 1)
			temp += pow(2, i);
	}
	return temp;
}

int Lifesupport::keep_one(int keep, int position) {
//Takes which number to keep and which position
//then counts the zeros and ones, then calls purge and returns the specified number
	int i;
	int ones, zeros;

	ones = 0;
	zeros = 0;
	if (keepers.size() == 0)
		reset_keepers();

	for (i = 0; i < matrix.size(); i++) {
		if (keepers[i] == 1) {
			if (matrix[i][position] == 1)
				ones++;
			else
				zeros++;
		}
	}
	if (keep == 1 && ones >= zeros) {
		purge(1, position);
		return 1;
	}
	else if (keep == 1 && ones < zeros) {
		purge(0, position);
		return 0;
	}
	else if (keep == 0 && (zeros > ones && ones > 0) || zeros == 0) {
		purge(1, position);
		return 1;
	}
	else if ((keep == 0 && zeros <= ones) || ones == 0) {
		purge(0, position);
		return 0;
	}
}

void Lifesupport::purge(int keep, int position) {
//Takes the numbers to keep based on keep and position
	int i;

	for (i = 0; i < matrix.size(); i++) {
		if (matrix[i][position] != keep)
			keepers[i] = 0;
	}

}

void Lifesupport::reset_keepers() {
//Resets the keeper list
	int i;
	keepers.clear();
	for (i = 0; i < matrix.size(); i++) {
		keepers.push_back(1);
	}
}

void Lifesupport::fill(){
//fills the list with the input from the file
	fstream file;
	string s, s2;
	int i, j;
	vector <int> line;

	//Opens the file
	open_file(file, DAY);

	//Takes the file and saves the numbers to matrix[line][column]
	while (getline(file, s, '\n')) {
		for (i = 0; i < s.size(); i++) {
			line.push_back(((int) s[i])-48);
		}
		matrix.push_back(line);
		line.clear();
		}
	//closes the file
	file.close();

}

int Lifesupport::problem1() {
//Problem 1, looks through each column for 
//the most common one for gamma
//the least common one for epsilon
//returns the decimal form of gamma*epsilon

	vector <int> gamma;
	vector <int> epsilon;
	int i, j, g, e;

	for (i = 0; i < matrix[0].size(); i++) {
		g = 0;
		e = 0;
		for (j = 0; j < matrix.size(); j++) {
			if (matrix[j][i] == 1)
				g++;
			else
				e++;			
		}
		if (g > e) {
			gamma.push_back(1);
			epsilon.push_back(0);
		}
		else {
			gamma.push_back(0);
			epsilon.push_back(1);
		}
	}

	return (binary_to_decimal(gamma)) * (binary_to_decimal(epsilon));
}

int Lifesupport::problem2() {
//Problem 2, looks through one column and calculates 
//the most common one for oxygenGenerator and
//then purges the list and looks throguh the next column
//after oxygenGenerator is done, it resets the keepers list
//and does the same for the least common one for c02Scrubber
//then it returns the decimal versions of the two multiplied together

	vector <int> oxygenGenerator;
	vector <int> c02Scrubber;
	int i, j;

	for (i = 0; i < matrix[0].size(); i++)
		oxygenGenerator.push_back(keep_one(1, i));

	reset_keepers();
	for (i = 0; i < matrix[0].size(); i++)
		c02Scrubber.push_back(keep_one(0, i));

	return (binary_to_decimal(oxygenGenerator)) * (binary_to_decimal(c02Scrubber));
}

void day_3()
{
	Lifesupport lifesupport;

	//Fills the list from the input file
	lifesupport.fill();

	//Problem 1 lifesupport.problem1();
	//Problem 2 lifesupport.problem2();
	cout << lifesupport.problem2();

	return;
}