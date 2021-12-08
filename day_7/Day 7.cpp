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
          |Day__7|

#include "header.h"

//Used for opening the file
#define DAY 7

class Crab {
//Crab class
private:
	vector <int> crab;
	int maxPos;
public:
	void fill();
	int calculate();
	int calculate2();
	int calc_distance(int distance);
	Crab(){
		maxPos = 0;
	};
};

void Crab::fill() {
//Takes the input and saves the crabs location
	fstream file;
	char c;
	int i;

	open_file(file, DAY);

	while (file >> i) {
		crab.push_back(i);
		if(i > maxPos)
			maxPos = i;
		file >> c;
	}
}

int Crab::calculate() {
//Problem 1, calculates the distance to every possible location
	int count, temp;
	int i, j;

	count = 0;
	for (i = 0; i <= maxPos+1; i++ ) {
		temp = 0;
		for (j = 0; j < crab.size(); j++ ) {
			if(crab[j] >= i)
				temp += (crab[j] - i);
			else
				temp += (i - crab[j]);
		}
		if (i == 0)
			count = temp;
		else if (temp < count)
			count = temp;
	}
	return count;
}

int Crab::calculate2() {
//Problem 2, same as problem one except that you take the !distance
	int count, temp;
	int i, j;

	count = 0;
	for (i = 0; i <= maxPos + 1; i++) {
		temp = 0;
		for (j = 0; j < crab.size(); j++) {
			if (crab[j] >= i)
				temp += calc_distance(crab[j] - i);
			else
				temp += calc_distance(i - crab[j]);
		}
		if (i == 0)
			count = temp;
		else if (temp < count)
			count = temp;
	}
	return count;
}

int Crab::calc_distance(int distance) {
//Recursive function to calculate !distance
	int temp;
	temp = 0;

	if (distance > 1)
		return temp= distance + calc_distance(distance - 1);
	else
		return 1;
}

void day_7() {
	Crab crab;

	crab.fill();

	//Problem 1 crab.calculate()
	//Problem 2 crab.calculate2()
	cout << crab.calculate2();

	return;
}