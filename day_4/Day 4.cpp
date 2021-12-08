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
          |Day__4|

#include "header.h"

//Used for bingo board size
#define BINGOSIZE 5

//Used for opening the file
#define DAY 4

class Board;
class ListOfBoards;

class Tile {
//Saves the bingonumber and if it has been drawn, together
private:
public:
	int number;
	bool drawn;

	Tile(int num) {
		drawn = false;
		number = num;
	};
};

class Board {
//One board, it uses the tiles and the size is defined as BINGOSIZE
private:
	bool is_winner();
public:
	bool win;
	int size;
	int winNum;
	vector <vector <Tile>> board;

	Board() {
		win = false;
		winNum = NULL;
		size = 0;
	};
	void add(vector <Tile> inputBoard);
	void clear();
	int sizeB();
	bool check_board(int num);
	int sum_board();
	
};

class ListOfBoards {
	//A class to handle multiple boards
private:

public:
	vector <Board> list;
	vector <int> winOrder;
	int size;
	void add(Board inputBoard);
	int sizeB();
	void fill();
	void check_boards(vector <int>& num);
	int sum_board(int placing);
	ListOfBoards() {
		size = 0;
	};
};

void Board::add(vector <Tile> inputBoard) {
	//Adds one row of Tiles to the Board
	this->size++;
	board.push_back(inputBoard);
}

void Board::clear() {
	//Clears the Board
	this->size = 0;
	board.clear();
}

int Board::sizeB() {
	//Outputs the size of the board, in rows
	return this->size;
}

bool Board::check_board(int num) {
//Takes one number and check if it occurs on the board, if it does it calls the is_Winner() function
	int i, j;
		for (i = 0; i < BINGOSIZE; i++) {
			for (j = 0; j < BINGOSIZE; j++) {
				if (win == true)
					return true;
				else if (board[i][j].number == num && board[i][j].drawn == false) {
					board[i][j].drawn = true;
					win=is_winner();
					if (win == true) {
						winNum = num;
						return true;
					}
				}

			}
		}
		return false;
}

bool Board::is_winner() {
//Checks the board if it has won
	int i, j;
	//Checks the vertical lines
	for (i = 0; i < BINGOSIZE; i++) {
		for (j = 0; j < BINGOSIZE; j++) {
			if (board[i][j].drawn != true)
				break;
			
			else if (j == BINGOSIZE - 1) {
				win = true;
				return true;
			}
		}		
	}
	//Checks the horizontal lines
	for (i = 0; i < BINGOSIZE; i++) {
		for (j = 0; j < BINGOSIZE; j++) {
			if (board[j][i].drawn != true)
				break;

			else if (j == BINGOSIZE - 1) {
				win = true;
				return true;
			}

		}
	}
	return false;
}

int Board::sum_board() {
//Outputs the sum of all non drawn numbers of the board * the winning number
	int i, j;
	int sum;

	sum = 0;
	for (i = 0; i < BINGOSIZE; i++) {
		for (j = 0; j < BINGOSIZE; j++) {
			if (board[i][j].drawn == false)
				sum += board[i][j].number;
		}
	}


	return sum * winNum;
}

void ListOfBoards::add(Board inputBoard) {
//Adds one board to the list
	list.push_back(inputBoard);
	this->size++;
}

int ListOfBoards::sizeB() {
//Outputs the number of boards it contains
	return this->size;
}

void ListOfBoards::fill(){
	//Saves the bingo boards from the file to the list
	string temp;
	vector <Tile> row;
	Board board;
	fstream file;
	int i;

	open_file(file, DAY);
	file >> temp;
	while (file >> i) {
		row.push_back(i);
		
		if (row.size() == BINGOSIZE) {
			board.add(row);
			row.clear();
		}

		if (board.sizeB() == BINGOSIZE) {
			add(board);
			board.clear();
		}
	}
	file.close();
}

void ListOfBoards::check_boards(vector <int>& num){
//Goes through all of the boards and send them to check_board, also adds a winOrder if it finds a winner
	int i, j;

	for (i = 0; i < num.size(); i++) {
		for (j = 0; j < list.size(); j++) {
			if (list[j].win == false) {

				list[j].check_board(num[i]);
				if (list[j].win == true)
					winOrder.push_back(j);
			}
		}
	}
}

int ListOfBoards::sum_board(int placing) {
//Calls the sum_board for a specific board
	return list[winOrder[placing]].sum_board();
}

void fill_drawn_numbers(vector <int>& drawnNumbers) {
//Fills the drawn numbers list with the drawn numbers at the top of the file
	int i;
	char c;
	string temp;
	fstream file;

	open_file(file, DAY);

	while (getline(file, temp, ',')){
		drawnNumbers.push_back(stoi(temp));
	}

	file.close();
}

void day_4()
{

	ListOfBoards list;
	vector <int> drawnNumbers;

	//Takes the file and saves the drawn numbers at the top to drawnNumbers
	fill_drawn_numbers( drawnNumbers);
	
	//Fills the list from the file
	list.fill();

	//Check the list of boards to find which order they won, and which numbers were the winning numbers
	list.check_boards(drawnNumbers);

	//For problem 1, outputs sum*winning_number of the winner
	cout << list.sum_board(0) << endl;

	//For problem 2, outputs sum*winning_number of the last board to get a bingo
	cout << list.sum_board(list.sizeB()-1);

	return;
}