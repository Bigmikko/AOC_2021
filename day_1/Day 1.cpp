	     /\
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
          |Day__1|

#include "header.h"

//Used for opening the file
#define DAY 1

int problem_1(vector <int> numbers){
	//Problem 1
	//it counts everytime a number increases
	int i, count;

	count = 0;
	for (i = 1; i < numbers.size(); i++) {
		if (numbers[i] > numbers[i - 1])
			count++;
	}
	return count;
}


int problem_2(vector <int> numbers) {
	//Problem 2
	//it counts every block of 3 if it increases compared to the previous 3 blocks, blocks are: 123 234 345 and so on
	int i,a,b, count;

	count = 0;
	a = 0;
	b = 0;
	for (i = 0; i < numbers.size()-3; i++) {
		a = numbers[i] + numbers[i + 1] + numbers[i + 2];
		b = numbers[i + 1] + numbers[i + 2] + numbers[i + 3];
		if (b > a)
			count++;
	}
	return count;
}

void day_1()
{
	
	fstream file;
	int i;
	vector <int> numbers;

	//Opens the file
	open_file(file, DAY);

	//Takes the file and saves the numbers to numbers[]
	while (file >> i) {  
		numbers.push_back(i);
	}

	//Closes the file
	file.close();

	//For Problem 1
	cout << problem_1(numbers);
	cout << problem_2(numbers);

	return;
}  