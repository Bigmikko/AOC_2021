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
          |Day__5|

#include "header.h"

//Used for opening the file
#define DAY 5

class matrix;
class positions;

class positions {   
//Saves the positions for the lines
public:             
	vector<int> x1;
	vector<int> x2;
	vector<int> y1;
	vector<int> y2;

	void fill(matrix &matrix);
};

class matrix {
//Saves the matrix where it draws and calculates lines
public:
	vector<vector<int>> grid;
	int sizeofX, sizeofY;

	matrix() {
		sizeofX = 0;
		sizeofY = 0;
	}

	void fill();
	void draw_Hlines(positions positions);
	void draw_Vlines(positions positions);
	void draw_Dlines(positions positions);
	int count_intersections();
	void largest_X(vector <int> x);
	void largest_Y(vector <int> y);
};

void positions::fill(matrix &matrix) {
//Takes the file and saves the positions to x1, x2, y1, y2
	int i, j, k, l;
	char c;
	fstream file;

	open_file(file, DAY);

	 while(file >> i >> c >> j >> c >> c >> k >> c >> l){
		x1.push_back(i);
		y1.push_back(j);
		x2.push_back(k);
		y2.push_back(l);
		vector <int> bigX = { i, k };
		vector <int> bigY = { j, l };
		matrix.largest_X(bigX);
		matrix.largest_Y(bigY);
	}
	 file.close();
}

void matrix::fill() {
//Fills the matrix with 0s
	int i, j;
	vector <int> row;

	for (i = 0; i <= sizeofX; i++) {
		for (j = 0; j <= sizeofY; j++) {
			row.push_back(0);
		}
		grid.push_back(row);
		row.clear();
	}
}

void matrix::draw_Hlines(positions positions) {
//Adds 1 to everywhere the line goes as a line, only horizontal
	int i, j;
	int bigNum, smallNum;

	for (i = 0; i < positions.x1.size(); i++) {
		if (positions.x1[i] == positions.x2[i]) {
			if (positions.y1[i] <= positions.y2[i]) {
				bigNum = positions.y2[i];
				smallNum = positions.y1[i];
			}
			else {
				bigNum = positions.y1[i];
				smallNum = positions.y2[i];
			}

			for (j = smallNum; j <= bigNum; j++) {
				grid[positions.x1[i]][j]++;
			}
		}
	}

}

void matrix::draw_Vlines(positions positions) {
//Adds 1 to everywhere the line goes as a line, only Vertical
	int i, j;
	int bigNum, smallNum;

	for (i = 0; i < positions.y1.size(); i++) {
		if (positions.y1[i] == positions.y2[i]) {
			if (positions.x1[i] <= positions.x2[i]) {
				bigNum = positions.x2[i];
				smallNum = positions.x1[i];
			}
			else {
				bigNum = positions.x1[i];
				smallNum = positions.x2[i];
			}

			for (j = smallNum; j <= bigNum; j++) {
				grid[j][positions.y1[i]]++;
			}
		}
	}

}

void matrix::draw_Dlines(positions positions) {
//Adds 1 to everywhere the line goes as a line, only diagonal
	int i, j;
	int bigNumX, smallNumX, bigNumY, smallNumY;

	for (i = 0; i < positions.x1.size(); i++) {
		if (positions.y1[i] <= positions.y2[i]) {
			bigNumY = positions.y2[i];
			smallNumY = positions.y1[i];
		}
		else {
			bigNumY = positions.y1[i];
			smallNumY = positions.y2[i];
		}
		if (positions.x1[i] <= positions.x2[i]) {
			bigNumX = positions.x2[i];
			smallNumX = positions.x1[i];
		}
		else {
			bigNumX = positions.x1[i];
			smallNumX = positions.x2[i];
		}
		if ((bigNumX - smallNumX) == (bigNumY - smallNumY)) {
			if (positions.x1[i] > positions.x2[i] && positions.y1[i] > positions.y2[i]) {
				for (j = 0; j <= bigNumX - smallNumX; j++) {
					grid[smallNumX + j][smallNumY + j]++;
				}
			}
			else if (positions.x1[i] < positions.x2[i] && positions.y1[i] < positions.y2[i]) {
				for (j = 0; j <= bigNumX - smallNumX; j++) {
					grid[bigNumX - j][bigNumY - j]++;
				}
			}
			else if (positions.x1[i] > positions.x2[i] && positions.y1[i] < positions.y2[i]) {
				for (j = 0; j <= bigNumX - smallNumX; j++) {
					grid[smallNumX + j][bigNumY - j]++;
				}
			}
			else if (positions.x1[i] < positions.x2[i] && positions.y1[i] > positions.y2[i]) {
				for (j = 0; j <= bigNumX - smallNumX; j++) {
					grid[bigNumX - j][smallNumY + j]++;
				}
			}
		}

	}

}

int matrix::count_intersections() {
//Counts everytime in the grid where there are lines intersecting, >1
	int count;
	int i, j;
	count = 0;

	for (i = 0; i <= sizeofX; i++) {
		for (j = 0; j <= sizeofY; j++) {
			if (grid[j][i] > 1) {
				count++;
			}
		}
	}

	return count;
};

void matrix::largest_X(vector <int> x) {
//Used to determin how big the matrix should be, takes the largest X-coordinate from the file
	int i;
	for (i = 0; i < x.size(); i++) {
		if (x[i] > sizeofX)
			sizeofX = x[i];
	}
}

void matrix::largest_Y(vector <int> y) {
//Used to determin how big the matrix should be, takes the largest Y-coordinate from the file
	int i;
	for (i = 0; i < y.size(); i++) {
		if (y[i] > sizeofY)
			sizeofY = y[i];
	}
}

void day_5() {

	matrix matrix;
	positions positions;

	
	//Saves the input to positions and saves the checks the gridsize
	positions.fill(matrix);
	
	//Creates the 2D matrix used to store the lines later
	matrix.fill();

	//Creates the horizontal and vertical lines
	matrix.draw_Hlines(positions);
	matrix.draw_Vlines(positions);

	//Add only for Problem 2, adds diagonal lines
	matrix.draw_Dlines(positions);

	//Prints the amount of intersected lines
	cout << matrix.count_intersections();

	return;
}