#include "header.h"
#include "printAscii.hpp"
using namespace std;

int SIDE; 
int MINES;
void Intro();
void Rules();
void Exit(); 

//to confirm the validity of the position
bool isValidPosition(int row, int col) {
	return ((row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE));
}

//to check the position of the mine
bool minePosition(int row, int col, char board[][25]) {
	if (board[row][col] == '*')
		return true;
	else
		return false;
}

//to get the input from user for cordinates
void getInput(int *x, int *y) {
	cout << "Enter the coordinates: "<<endl;
  cout << "Row number: "<< endl;
	cin >> *x;
  cout << "Columne number: "<< endl;
	cin >> *y;
	cout << CLRSCR;
}

//to print the board
void printBoard(char myBoard[][25]) {
	cout<<MAGENTA;
	cout<<"Board: "<<endl<<endl;
	cout<<WHITE;
	cout<<"  ";
	for(int i = 0; i < SIDE; i++) {
		cout<<BLUE;
		cout<<" "<<i;
		cout<<WHITE;
	}
	cout<<endl;
	for (int i = 0; i < SIDE; i++) {
		cout<<BLUE;
		cout<<" "<<i;
		cout<<WHITE;
		for(int j = 0; j < SIDE; j++) {
			if(myBoard[i][j] == '*') {
				cout<<RED;
			}
			else if(myBoard[i][j] == '-') {
				cout<<WHITE;
			}
			else {
				cout<<GREEN;
			}
			cout<<" "<<myBoard[i][j];
			cout<<WHITE;
		}
		cout<<endl;
	}
	cout<<endl;
}

//to count the mines throughout the field all position possibilities
int countMines(int row, int col, int mines[][2],  char realBoard[][25]) {
	int count = 0;

	if(isValidPosition(row-1, col) && (minePosition(row-1, col, realBoard))) {
		count++;
	}

	if(isValidPosition(row+1, col) && (minePosition(row+1, col, realBoard))) {
		count++;
	}

	if(isValidPosition(row, col+1) && (minePosition(row, col+1, realBoard))) {
		count++;
	}

	if(isValidPosition(row, col-1) && (minePosition(row, col-1, realBoard))) {
		count++;
	}

	if(isValidPosition(row-1, col+1) && (minePosition(row-1, col+1, realBoard))) {
		count++;
	}

	if(isValidPosition(row-1, col-1) && (minePosition(row-1, col-1, realBoard))) {
		count++;
	}

	if(isValidPosition(row+1, col+1) && (minePosition(row+1, col+1, realBoard))) {
		count++;
	}

	if(isValidPosition(row+1, col-1) && (minePosition(row+1, col-1, realBoard))) {
		count++;
	}

	return count;
}

//main playing function
bool playUntil(char myBoard[][25], char realBoard[][25], int mines[][2], int row, int col, int *movesLeft) {

	if (myBoard[row][col] != '-')
		return false;

	if (realBoard[row][col] == '*') {
		myBoard[row][col]='*';

		for (int i = 0; i < MINES; i++) {
			myBoard[mines[i][0]][mines[i][1]] = '*';
		}
		
		printBoard(myBoard);
		cout<<RED;
		cout<<"OH NO! You stepped on a MINE! "<<endl;
		cout<<"\t\tGAME OVER! "<<endl;
		cout<<WHITE;
		return true;
	}
	else {
		int count = countMines(row, col, mines, realBoard);
		(*movesLeft)--;
	
		myBoard[row][col] = count + '0';
		
		if(!count) {
			if(isValidPosition(row-1, col) && (!minePosition(row-1, col, realBoard))) {
				playUntil(myBoard, realBoard, mines, row-1, col, movesLeft);
			}

			if(isValidPosition(row+1, col) && (!minePosition(row+1, col, realBoard))) {
				playUntil(myBoard, realBoard, mines, row+1, col, movesLeft);
			}

			if(isValidPosition(row, col+1) && (!minePosition(row, col+1, realBoard))) {
				playUntil(myBoard, realBoard, mines, row, col+1, movesLeft);
			}

			if(isValidPosition(row, col-1) && (!minePosition(row, col-1, realBoard))) {
				playUntil(myBoard, realBoard, mines, row, col-1, movesLeft);
			}

			if(isValidPosition(row-1, col+1) && (!minePosition(row-1, col+1, realBoard))) {
				playUntil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
			}

			if(isValidPosition(row-1, col-1) && (!minePosition(row-1, col-1, realBoard))) {
				playUntil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
			}

			if(isValidPosition(row+1, col+1) && (!minePosition(row+1, col+1, realBoard))) {
				playUntil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
			}

			if(isValidPosition(row+1, col-1) && (!minePosition(row+1, col-1, realBoard))) {
				playUntil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
			}
		}
		return false;
	}
}

//function that places mine randomly
void placeMines(int mines[][2], char realBoard[][25]) {
	bool mark[25 * 25];
	memset(mark, false, sizeof (mark));

	for (int i = 0; i < MINES; ) {
		int ran = rand() % (SIDE*SIDE);
		int x = ran / SIDE;
		int y = ran % SIDE;

		if (!mark[ran]) {
			mines[i][0]= x;
			mines[i][1] = y;

			realBoard[mines[i][0]][mines[i][1]] = '*';
			mark[ran] = true;
			i++;
		}
	}
}
//intializing fucntion
void initialise(char realBoard[][25], char myBoard[][25]) {
	srand(time(NULL));

	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			myBoard[i][j] = realBoard[i][j] = '-';
		}
	}
}

void getMineLocation(char realBoard[][25]) {
	cout<<"Mine Locations are: ";
	printBoard(realBoard);
}

void replaceMine(int row, int col, char board[][25]) {
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			if (board[i][j] != '*') {
				board[i][j] = '*';
				board[row][col] = '-';
				return;
			}
		}
	}
}

void playGame() {
	bool gameOver = false;

	char realBoard[25][25], myBoard[25][25];

	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[99][2]; 

	initialise (realBoard, myBoard);

	placeMines (mines, realBoard);
	
	int moveCount = 0;
	while(!gameOver) {
		printBoard(myBoard);
		getInput(&x, &y);

		if(moveCount == 0) {
			if(minePosition (x, y, realBoard)) {
				replaceMine (x, y, realBoard);
			}
		}
		moveCount ++;
		gameOver = playUntil(myBoard, realBoard, mines, x, y, &movesLeft);

		if ((!gameOver) && (movesLeft == 0)) {
			printBoard(myBoard);
			cout<<GREEN;
			cout<<"******************** YOU WON! ********************"<<endl;
			cout<<WHITE;
			gameOver = true;
		}
	}
}

void getInput() {
	cout<<CLRSCR;
	cout<<"Enter number of sides for board: ";
	cin>>SIDE;

	cout<<"Enter number of mines: ";
	cin>>MINES;
	cout<<endl;
	cout<<CLRSCR;
}

void Rules() {
	char back;
	cout<<CLRSCR;
	cout<<"RULES: "<<endl<<endl;
	cout<<"1) The board is divided into cells, with mines randomly distributed. "<<endl;
	cout<<"2) To win, you need to open all the cells. "<<endl;
	cout<<"3) The number on a cell indicates the number of mines adjacent to it. "<<endl;
	cout<<"4) Using this you can determine which cells are safe and which contain mines. "<<endl<<endl;
	cout<<"Press B to go back: ";
	cin>>back;
	if(back == 'b' || back == 'B') {
		Intro();
	}
	else {
		cout<<RED;
		cout<<"Please press b to go to the main menu! "<<endl<<WHITE;
		sleep(2);
		Rules();
	}
}
void Credits() {
	char back;
	cout<<CLRSCR;
	cout<<"Credits: "<<endl<<endl;
	cout<<"1) This is made with the help of my clanmates at Outscal"<<endl;
	cout<<"2) Some Internet devouring(references from outscal material, assignments, youtube videos and geeksforgeeks) "<<endl;
	cout<<"4) You can follow my work on GitHub/Justrishimudaliyar "<<endl<<endl;
	cout<<"Press B to go back: ";
	cin>>back;
	if(back == 'b' || back == 'B') {
		Intro();
	}
	else {
		cout<<RED;
		cout<<"Please press b to go to the main menu! "<<endl<<WHITE;
		sleep(2);
		Credits();
	}
}

void Exit() {
	char choice;
	cout<<endl<<RED;
	cout<<"\t\t\t\t Do you want to exit the game (Y/N): ";
	cin>>choice;
	if(choice == 'y' || choice == 'Y') {
		cout<<RED;
		cout<<T;cout<<"\tBYE!"<<endl<<WHITE;
		sleep(2);
		return;
	}
	else if(choice == 'n' || choice == 'N') {
		Intro();
	}
	else {
		cout<<RED;
		cout<<"Please press Y for Yes or N for No! "<<endl<<WHITE;
		sleep(2);
		Exit();
	}
}


void Intro() { 
  string fileName = "ascii-art.txt";
  printAscii(fileName);
  cin.get();
  cout << "\e[2J\e[H";
	int choice;
	while(true) {
		cout<<CLRSCR;
    string fileName = "minesweeper.txt";
    printAscii(fileName);
		cout<<MAGENTA;
		cout<<T;cout<<"  1) PLAY "<<endl;
		cout<<T;cout<<"  2) RULES "<<endl;
    cout<<T;cout<<"  3) CREDITS "<<endl;
		cout<<T;cout<<"  4) EXIT "<<endl<<endl;

		cout<<"\t\t\t\t\t\t Enter your Input: ";
		cin>>choice;
		if(choice == 1) {
			getInput();
			playGame();
			break;
		}
		else if(choice == 2) {
			Rules();
			break;
		}
    else if(choice == 3) {
			Credits();
			break;
		}
		else if(choice == 4) {
			Exit();
			break;
		}
		else {
			cout<<RED;
			cout<<"\t\t\t\t\t  Please Enter a valid Choice! "<<WHITE;
			sleep(2);
		}
	}
}

int main() {	
	Intro();	
}