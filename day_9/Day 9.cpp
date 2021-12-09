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
          |Day__9|

#include "header.h"

//Used for opening the file
#define DAY 9

//Amount of basins to save
#define SAVEBASINS 3

class Heightmap {
private:
//Heightmap class
	vector <vector <int>> matrix;
	vector <vector <int>> lowPoints;
	vector <int> list;
	vector <vector <vector <int>>> basins;

	bool find_nearby(int x, int y);
	vector <vector <int>> find_adjacent(vector <vector <int>> start);
	void basin_count(int lowPoint);
	vector <int> int_to_pos(int x, int y);
	bool allowed_movement(int x, int y);
	bool first_time(vector <vector <int>> positions, int x, int y);

public:

	int risk_levels();
	void fill();
	void check_heights();
	void find_lowpoints(int x, int y);
	int check_basin();
};

bool Heightmap::first_time(vector <vector <int>> positions, int x, int y) {
//Checks agains positions if it's the first time trying to visit the coordinates x y 
	int i;

	for (i = 0; i < positions.size(); i++) {
		if (positions[i][0] == x && positions[i][1] == y)
			return false;
	}

	return true;
}

bool Heightmap::allowed_movement(int x, int y) {
//If the suggested x, y coordinates is within the map and if it's not a 9
	if (x < matrix.size() && x >= 0 && y >= 0 && y < matrix[0].size())
		return true;

	return false;
}

void Heightmap::basin_count(int lowPoint) {
//Takes the lowPoint and uses find_adjacent on it, then saves the number to basins
	vector <vector <int>> start;
	vector <int> pos;
	pos.push_back(lowPoints[lowPoint][0]);
	pos.push_back(lowPoints[lowPoint][1]);
	start.push_back(pos);

	basins.push_back(find_adjacent(start));

}

vector <int> Heightmap::int_to_pos(int x, int y) {
//Takes two int and truns it in to a vector <int>
	vector <int> pos;
	pos.push_back(x);
	pos.push_back(y);

	return pos;
}

int Heightmap::risk_levels() {
//Used for problem 1, returns the sum of the list[], +1 for each element where every low points value is saved
	int i;
	int sum;

	sum = 0;
	for (i = 0; i < list.size(); i++) {
		sum += list[i] + 1;
	}
	return sum;
}

vector <vector <int>> Heightmap::find_adjacent(vector <vector <int>> start) {
//Recursive function
//Steps through all available numbers next to start and returns a list of all of the positions

	int i, j;
	int x, y;
	

	x = start[start.size() - 1][0];
	y = start[start.size() - 1][1];

	if (allowed_movement(x + 1, y) && first_time(start, x + 1, y)) {
		if (matrix[x + 1][y] != 9) {
			start.push_back(int_to_pos(x + 1, y));
			start = (find_adjacent(start));
		}
	}

	if (allowed_movement(x - 1, y) && first_time(start, x - 1, y)) {
		if (matrix[x - 1][y] != 9) {
			start.push_back(int_to_pos(x - 1, y));
			start = (find_adjacent(start));
		}
	}

	if (allowed_movement(x, y + 1) && first_time(start, x, y + 1)) {
		if (matrix[x][y + 1] != 9) {
			start.push_back(int_to_pos(x, y + 1));
			start = (find_adjacent(start));
		}
	}

	if (allowed_movement(x, y - 1) && first_time(start, x, y - 1)) {
		if (matrix[x][y - 1] != 9) {
			start.push_back(int_to_pos(x, y - 1));
			start = (find_adjacent(start));
		}
	}

	return start;
}

bool Heightmap::find_nearby(int x, int y) {
//Used for problem 1 to find to find the lowest point

	if (x != (matrix.size() - 1) && x > 0) {
		if ((matrix[x][y] < matrix[x + 1][y]) && (matrix[x][y] < matrix[x - 1][y]))
			if (y != (matrix[0].size() - 1) && y > 0) {
				if ((matrix[x][y] < matrix[x][y - 1]) && (matrix[x][y] < matrix[x][y + 1]))
					return true;
			}
			else if (y == 0) {
				if((matrix[x][y] < matrix[x][y + 1]))
					return true;
			}
			else if (y == (matrix[0].size() - 1))
				if (matrix[x][y] < matrix[x][y - 1])
					return true;
		return false;
	}
	else if (x == 0) {
		if (matrix[x][y] < matrix[x + 1][y])
			if ((y > 0) && (y < (matrix[0].size() - 1))) {
				if ((matrix[x][y] < matrix[x][y - 1]) && (matrix[x][y] < matrix[x][y + 1]))
					return true;
			}
			else if (y == 0) {
				if ((matrix[x][y] < matrix[x][y + 1]))
					return true;
			}
			else if (y == (matrix[0].size() - 1))
				if (matrix[x][y] < matrix[x][y - 1])
					return true;
			return false;
	}
	else if (x == (matrix.size() - 1)) {
		if (matrix[x][y] < matrix[x - 1][y])
			if ((y > 0) && (y < (matrix[0].size() - 1))) {
				if ((matrix[x][y] < matrix[x][y - 1]) && (matrix[x][y] < matrix[x][y + 1]))
					return true;
			}
			else if (y == 0) {
				if ((matrix[x][y] < matrix[x][y + 1]))
					return true;
			}
			else if (y == (matrix[0].size() - 1))
				if (matrix[x][y] < matrix[x][y - 1])
					return true;
		return false;
	}
}

void Heightmap::fill() {
//Fills matrix with the input file
	fstream file;
	string s,s2;
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

void Heightmap::check_heights() {
//Uses find_nearby and find_lowpoints to find every instance of a lowpoint
	int i, j, k;
	int currentLow, previous;
	vector <int> low;


	for (i = 0; i < matrix.size(); i++) {
		for (j = 0; j < matrix[0].size(); j++) {
			if(find_nearby(i, j))
				find_lowpoints(i, j);
		}
	}
}

void Heightmap::find_lowpoints(int x, int y) {
//If x y coordinates has not already been added to the list
//it adds them to the list of lowpoints
	int i;
	vector <int> low;

	low.push_back(x);
	low.push_back(y);

	for (i = 0; i < lowPoints.size(); i++) {
		if (low == lowPoints[i])
			return;
	}
	lowPoints.push_back(low);
	list.push_back(matrix[x][y]);
}

int Heightmap::check_basin() {
//Problem 2, first it calculates the size of each basin
//Then it makes an ordered list of their sizes
//At last it saves the top SAVEBASINS number of basins sizes
//Then it returns their multiplied value
	int i, j;
	int totalSize;
	vector <int> basinSizes;
	vector <int> biggestBasins;
	for (i = 0; i < lowPoints.size(); i++) {
		basin_count(i);
	}
	for (i = 0; i < basins.size(); i++) {
		basinSizes.push_back(basins[i].size());
	}
	sort(basinSizes.begin(), basinSizes.end());

	for (i = 1; i < SAVEBASINS + 1; i++) {
		biggestBasins.push_back(basinSizes[basinSizes.size()-i]);
	}

	totalSize = biggestBasins[0];
	for (i = 1; i < SAVEBASINS; i++) {
		totalSize *= biggestBasins[i];
	}

	return totalSize;
}

void day_9() {

	Heightmap heightmap;

	//Fills the matrix from the input file
	heightmap.fill();

	//Finds all of the lowest points
	heightmap.check_heights();

	//For problem 1, adds the numbers of all the low points
	//adds 1 to each low point and then outputs their sum
	cout << heightmap.risk_levels() << endl; 


	//For problem 2, finds the sizes of the basins, 
	//saves the top numbers SAVEBASINS declares how many
	//and outputs their multiplied value
	cout << heightmap.check_basin() << endl;

	return;
}