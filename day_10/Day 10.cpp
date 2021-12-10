            //\\
           //__\\
          //____\\
         //______\\
        //_Advent_\\
       //____Of____\\
      //____Code____\\
     //______________\\
    //______2021______\\
   //__________________\\ 
  //____by Bigmikko_____\\
 //______________________\\
//________________________\\
          |Day_10|

#include "header.h"

//Used for opening the file
#define DAY 10

class Chunks {
//Chunks class
private:
	vector <string> matrix;
	vector <char> corruptedChars;
	vector <int> corruptedLines;
	vector <vector <char>> listIncomplete;

	void is_corrupted(int line);
	bool is_opener(char character);
	char matching_closer(char character);

public:
	void fill();
	void find_corrupted();
	int corrupted_points();
	long long incomplete_points();
};

bool Chunks::is_opener(char character){
//Returns true if it an opener, false if closer
	if (character == '(' || character == '[' || character == '{' || character == '<')
		return true;

	else if (character == ')' || character ==  ']' || character == '}' || character == '>')
		return false;

	else {
		cout << "Error, invalid characters in input" << endl;
		exit(0);
	}
}

char Chunks::matching_closer(char character){
//Returns the closer variant of the character
	if (character == '(' )
		return ')';

	else if (character == '[')
		return ']';

	else if (character == '{')
		return '}';

	else if (character == '<')
		return '>';

}

void Chunks::is_corrupted(int line) {
//Saves the character that is corrupted in corruptedChars.
//Saves the missing brackets if the line is incomplete in listIncomplete
	int i;
	vector <char> openers;
	vector <char> closers;
	vector <char> missingClosers;

	for (i = 0; i < matrix[line].size(); i++) {
		if (is_opener(matrix[line][i]))
			openers.push_back(matrix[line][i]);
		else {
			closers.push_back(matrix[line][i]);
			if (closers[closers.size() - 1] == matching_closer(openers[openers.size() - 1])) {
				openers.pop_back();
				closers.pop_back();
			}
			else {
				corruptedChars.push_back(closers[closers.size() - 1]);
				corruptedLines.push_back(i);
				missingClosers.push_back('z');
				listIncomplete.push_back(missingClosers);
				return;
			}
		}
	}
	for (i = openers.size() - 1; i >= 0; i--) {
		missingClosers.push_back(matching_closer(openers[i]));
	}
	listIncomplete.push_back(missingClosers);

}

void Chunks::fill() {
//Fills matrix with the input file
	fstream file;
	string s;

	open_file(file, DAY);

	while (getline(file, s)) {
		matrix.push_back(s);
	}
	file.close();

}

void Chunks::find_corrupted() {
//Problem 1, finds all corrupted characters
	int i;

	for (i = 0; i < matrix.size(); i++) {
		is_corrupted(i);
	}
}

int Chunks::corrupted_points() {
//Problem 1, Returns the points for the corrupted lines
	int i;
	int a, b, c, d;

	a = 0;
	b = 0;
	c = 0;
	d = 0;

	for (i = 0; i < corruptedChars.size(); i++) {
		if (corruptedChars[i] == ')')
			a++;

		else if (corruptedChars[i] == ']')
			b++;

		else if (corruptedChars[i] == '}')
			c++;

		else if (corruptedChars[i] == '>')
			d++;
	}

	return (a * 3) + (b * 57) + (c * 1197) + (d * 25137);
}

long long Chunks::incomplete_points() {
//Returns the points for the incomplete lines
	int i, j;
	vector <long long> sumAll;
	long long sum;

	for (i = 0; i < listIncomplete.size(); i++) {
		sum = 0;

		if (listIncomplete[i][0] != 'z'){

			for (j = 0; j < listIncomplete[i].size(); j++) {
					sum *= 5;

				if (listIncomplete[i][j] == ')')
					sum += 1;

				else if (listIncomplete[i][j] == ']')
					sum += 2;

				else if (listIncomplete[i][j] == '}')
					sum += 3;

				else if (listIncomplete[i][j] == '>')
					sum += 4;
			}
			sumAll.push_back(sum);
		}
	}

	sort(sumAll.begin(), sumAll.end());


	return sumAll[sumAll.size()/2];
}

void day_10() {

	Chunks chunks;

	//Fills the list from the input file
	chunks.fill();

	//Finds corrupted lines and incomplete lines
	chunks.find_corrupted();

	//For problem 1
	cout << chunks.corrupted_points() << endl;

	//for problem 2
	cout << chunks.incomplete_points();

	return;
}