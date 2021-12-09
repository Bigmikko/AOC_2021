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
          |Day__6|

#include "header.h"

//Used for opening the file
#define DAY 6

//The age a new fish spawns with until reproduction
#define MAXAGE 8

//The counts how many days to reproduction
#define REPRODUCTIONAGE 6

//The amount of days which should be calculated
#define DAYS 256

class Fish {
//The fish class
private:
	long long fish[MAXAGE+1];

	void spawn();
	void spawn(int age);
public:
	long long amount;

	void fill();
	void days_passed(int days);
	Fish() {
		int i;
		amount = 0;
		for (i = 0; i < MAXAGE + 1; i++) {
			fish[i] = 0;
		}
	}

};
void Fish::fill() {
//Takes the input and spawns the fish
	int i;
	char c;
	fstream file;
	open_file(file, DAY);
	while (file >> i) {
		spawn(i);
		file >> c;
	}
	file.close();
};
void Fish::spawn(){
//Adds a fish at MAXAGE
	fish[MAXAGE]++;
	amount++;
}
void Fish::spawn(int age) {
//adds one fish at desired age
	fish[age]++;
	amount++;
}
void Fish::days_passed(int days) {
//Calculates the amount of fish per age to reproduction
	int i, j;
	long long temp;

	amount = 0;
	for (i = 0; i < days; i++)
	{
		//Saves all of the fish that are at age zero to put them at REPRODUCTIONAGE and MAXAGE
		temp = fish[0];

		for (j = 0; j < MAXAGE; j++){
			fish[j] = fish[j+1];
			//If a fish is at reproduction age it goes to both, last place and reproduction age
			if (j == REPRODUCTIONAGE)
				fish[j] += temp;
		}

		fish[MAXAGE] = temp;
	}
	//Adds all of the fish together
	for (i = 0; i < MAXAGE+1; i++)
		amount += fish[i];
}

void day_6() {
	Fish Fish;

	//Fills the Fish with the input
	Fish.fill();

	//Calculates the fish after a certain amount of days
	Fish.days_passed(DAYS);

	//Outputs the amount of fish
	cout << Fish.amount;

	return;
}