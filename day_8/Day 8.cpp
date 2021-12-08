/////////////////////////////
/////	Advent of Code 	/////
/////	2021	Day 8	/////
/////			/////
/////	by Bigmikko	/////
/////////////////////////////

#include "header.h"

//Used for opening the file
#define DAY 8

class SevenSegments {
//class for the seven segments
private:
	bool check_num(vector <char> segment, int number, int compare);
	void reset_answers();
	void calc_segment(vector <char> segment);
	void calc_rest(vector <char> segment);

public:
	vector <vector <vector <char>>> segments;
	vector <char> answers[10];

	void fill();
	int calculate();
	int calculate2();

	SevenSegments(){
		int i;
		vector <char> line;

		line.push_back('h');
		for (i = 0; i < 10; i++)
			answers[i]=line;
	};
};

bool SevenSegments::check_num(vector <char> segment, int number, int compare) {
//Takes the segment and compares it with the number from the answers and it has to match exactly compare times

	int i, j;
	int count;

	count = 0;
	for (i = 0; i < segment.size(); i++) {
		for (j = 0; j < answers[number].size(); j++) {
			if (segment[i] == answers[number][j])
				count++;
		}
	}
	if (count == compare)
		return true;

	return false;
}

void SevenSegments::reset_answers() {
//sets answers to 'h' which is an invalid answer
	int i;
	vector <char> line;

	line.push_back('h');
	for (i = 0; i < 10; i++)
		answers[i] = line;
}

void SevenSegments::calc_segment(vector <char> segment) {
//Calculates the numbers 1, 4, 7, 8 based on the sizes
	if (segment.size() == 2) 
		answers[1] = segment;

	else if (segment.size() == 4) 
		answers[4] = segment;

	else if (segment.size() == 3) 
		answers[7] = segment;

	else if (segment.size() == 7) 
		answers[8] = segment;
}

void SevenSegments::calc_rest(vector <char> segment) {
//calculates the numbers 0, 2, 3, 5, 6, 9 based on the below, you need do to calc_segment first
	int i;

	for (i = 0; i < 10; i++) {
		if (answers[i] == segment)
			return;
	}

	//number 0
	if ((answers[0][0] == 'h')) {
		if (check_num(segment, 8, 6) && check_num(segment, 4, 3) && check_num(segment, 7, 3))
			answers[0] = segment;
	}

	//number 9
	else if(answers[0][0] != 'h' && answers[9][0] == 'h') {
		if (check_num(segment, 7, 3) && check_num(segment, 4, 4))
			answers[9] = segment;
	}

	//number 3
	else if(answers[9][0] != 'h' && answers[3][0] == 'h' && check_num(segment, 7, 3))
		answers[3] = segment;


	//number 2
	else if (answers[3][0] != 'h' && answers[2][0] == 'h' && check_num(segment, 9, 4)) 
		answers[2] = segment;


	//number 6
	else if (answers[2][0] != 'h' && answers[6][0] == 'h' && check_num(segment, 8, 6))
		answers[6] = segment;


	//number 5
	else if (answers[6][0] != 'h' && answers[5][0] == 'h')
		answers[5] = segment;


}

void SevenSegments::fill() {
//Fills segments with the input from the file
	fstream file;
	string s;
	vector <char> temp;
	vector <vector <char>> line;
	int i;
	int tempNum;

	open_file(file, DAY);


	tempNum = 0;
	while (getline(file,s)) {
		for (i = 0; i <= s.size(); i++){
			if (s[i] != '|')
				if (i > 0)
					tempNum = i - 1;

				if ((s[i] == ' ' && s[tempNum] != '|') || i == s.size()) {
					sort(temp.begin(), temp.end());
					line.push_back(temp);
					temp.clear();
				}
				else {
					if((s[i] != '|' && s[i] != ' ' ) || i == s.size())
						temp.push_back(s[i]);
				}
		}
		segments.push_back(line);
		line.clear();
	}
	file.close();
}

int SevenSegments::calculate(){
//Problem 1, only uses check_num and calculates amount of those numbers
	int i, j, k;
	int sum;
	sum = 0;

	for (i = 0; i < segments.size(); i++) {
		for (j = 0; j < 10; j++) {
			calc_segment(segments[i][j]);
		}
		for (j = 0; j < segments[i].size() - 10; j++) {
			for (k = 0; k < 10; k++) {
				if (answers[k] == segments[i][10 + j])
					sum++;
			}
		}
	}

	return sum;
}

int SevenSegments::calculate2() {
//For problem 2, makes use of calc_segment and calc_rest to find each number
//It then takes each row as a number and sum all of the rows together
	int i, j, k;
	int temp, sum;
	sum = 0;
	temp = 0;
	for (i = 0; i < segments.size(); i++) {
		for (j = 0; j < 10; j++) {
			calc_segment(segments[i][j]);
		}

		for (j = 0; j < 10; j++) {
			calc_rest(segments[i][j]);
			if (j == 9 && answers[5][0] == 'h')
				j = -1;
		}
		for (j = 0; j < segments[i].size()-10; j++) {
			for (k = 0; k < 10; k++) {
				if (answers[k] == segments[i][10 + j]) {
					temp = (temp * 10) + k;
				}
			}
		}
		sum += temp;
		temp = 0;
		reset_answers();
	}

	return sum;
}

void day_8() {
	SevenSegments segments;

	//Fills segments with the input from the file
	segments.fill();

	//segments.calculate()	for problem 1
	//segments.calculate2() for problem 2
	cout << segments.calculate2();

	return;
}