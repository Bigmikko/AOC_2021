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
#define DAY 11

class Octopuses {
//Octoposes class
private:
	vector <vector <int>> matrix;

	void flash(vector <vector <int>>& flashed, int x, int y);
	vector <int> int_to_pos(int x, int y);
	bool already_flashed(vector <vector <int>> flashed, int x, int y);
	bool allowed_movement(vector <vector <int>> flashed, int x, int y);
	bool is_synchronized();
public:

	void fill();
	int days_passed(int n);
	int days_to_synchronize();

};

bool Octopuses::is_synchronized() {
//Checks if all numbers in the grid is equal to 0
	int i, j;

	for (i = 0; i < matrix.size(); i++) {
		for (j = 0; j < matrix[i].size(); j++) {
			if (matrix[i][j] != 0)
				return false;
		}
	}
	return true;
}

vector <int> Octopuses::int_to_pos(int x, int y) {
//Takes two int and turns it in to a vector <int>
	vector <int> pos;
	pos.push_back(x);
	pos.push_back(y);

	return pos;
}

bool Octopuses::allowed_movement(vector <vector <int>> flashed, int x, int y) {
//Checks if x y coordinates is a valid place in the grid, and also if it hasn't flashed yet
	if ((x < matrix.size()) && (x >= 0) && (y < matrix.size()) && (y >= 0) && !already_flashed(flashed, x, y)) {
		return true;
	}
	return false;
}

bool Octopuses::already_flashed(vector <vector <int>> flashed, int x, int y) {
//Checks the flashed list if x y coordinates has already flashed
	int i;

	for (i = 0; i < flashed.size(); i++) {
		if (flashed[i][0] == x && flashed[i][1] == y)
			return true;
	}
	return false;

}

void Octopuses::flash(vector <vector <int>>& flashed, int x, int y) {
//Recursive function
//Checks the matrix if the requests coordinates is a 9 and makes it in to a 0 and saves the location
//if the place in the grid has not been visited yet. It then call all adjacent ones in the grid and does the same
	int i, j;
	vector <vector <vector <int>>> list;

	if (allowed_movement(flashed, x, y)) {
		if (matrix[x][y] > 9) {
			matrix[x][y] = 0;
			flashed.push_back(int_to_pos(x, y));

			if (allowed_movement(flashed, x, y + 1))
				matrix[x][y + 1]++;
			if (allowed_movement(flashed, x, y - 1))
				matrix[x][y - 1]++;
			if (allowed_movement(flashed, x + 1, y + 1))
				matrix[x + 1][y + 1]++;
			if (allowed_movement(flashed, x + 1, y - 1))
				matrix[x + 1][y - 1]++;
			if (allowed_movement(flashed, x - 1, y + 1))
				matrix[x - 1][y + 1]++;
			if (allowed_movement(flashed, x - 1, y - 1))
				matrix[x - 1][y - 1]++;
			if (allowed_movement(flashed, x + 1, y))
				matrix[x + 1][y]++;
			if (allowed_movement(flashed, x - 1, y))
				matrix[x - 1][y]++;

			flash(flashed, x, y + 1);
			flash(flashed, x, y - 1);
			flash(flashed, x + 1, y + 1);
			flash(flashed, x + 1, y - 1);
			flash(flashed, x - 1, y + 1);
			flash(flashed, x - 1, y - 1);
			flash(flashed, x + 1, y);
			flash(flashed, x - 1, y);
		}
	}
}

void Octopuses::fill() {
//Fills matrix with the input file
	fstream file;
	string s, s2;
	vector <int> line;
	int i;

	open_file(file, DAY);

	while (getline(file, s)) {
		for (i = 0; i < s.size(); i++) {
			s2 = s[i];
			line.push_back(stoi(s2));
		}
		matrix.push_back(line);
		line.clear();
	}
	file.close();

}

int Octopuses::days_passed(int n) {
//Passes the day by n amount, returns the amount of flashes that happened
	int i, j, k;
	int flashes;
	int count;

	vector <vector <int>> flashed;

	flashes = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < matrix.size(); j++) {
			for (k = 0; k < matrix[j].size(); k++) {
				matrix[j][k]++;
			}
		}

		for (j = 0; j < matrix.size(); j++) {
			for (k = 0; k < matrix[j].size(); k++) {
				flash(flashed, j, k);
			}
		}
		flashes += flashed.size();
		flashed.clear();
	}
	return flashes;
}

int Octopuses::days_to_synchronize() {
//Checks if all of the days are == 0
//Advances the day by one if it's not
//Returns the amount of days it took to get them synchronized
	int i;

	i = 0;
	while(1==1) {
		if (is_synchronized())
			break;

		i++;
		days_passed(1);
	}
	return i;
}

void day_11() {

	Octopuses octopuses;

	//Fills the list from the input file
	octopuses.fill();

	//Problem 1
	//cout << octopuses.days_passed(100);

	//Problem 2, only do one of the problems at a time or it messes with the output
	cout << octopuses.days_to_synchronize();

	return;
}