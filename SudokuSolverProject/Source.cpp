#include <iostream>
using namespace std;

const int rows = 9;
const int columns = 9;

void display(int list[rows][columns]);
void start(int list[rows][columns], int number);
void clearArray(int tempList[rows][columns]);
void crossHatching(int i, int j, int tempList[rows][columns]);
void checkAndAssignNumber(int& tempRows, int& tempColumns, int tempList[rows][columns], int list[rows][columns], int number);

bool isFilled(int list[rows][columns]);

int main() {
	int list[rows][columns] = { {5,3,4,0,7,0,9,1,2},
								{6,0,0,1,9,5,0,0,8},
								{0,9,8,0,0,0,0,6,0},
								{8,0,0,0,6,0,0,0,3},
								{4,0,0,8,0,3,0,0,1},
								{7,0,0,0,2,0,0,0,6},
								{0,6,0,0,0,0,2,8,4},
								{2,8,7,4,1,9,0,0,5},
								{3,4,5,0,8,0,0,7,9} };
	cout << "Soduku Puzzle: " << endl;
	display(list);

	while (isFilled(list) == false) {			 //trying numbers 1-9 using cross hatching, If List still has 0 (isFilled = false) 
		for (int i = 0; i <= 9; i++) {			// do the while loop again until the list is filled
			start(list, i);

		}
	}


	cout << "\n""\n";
	cout << "Solved Soduku Puzzle: " << endl;
	display(list);

	return 0;
	}

void display(int list[rows][columns]) {
	cout << "********************************" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (list[i][j] == 0) {
				cout << "   ";

			}
			else {
				cout << " " << list[i][j] << " ";
			}
			if (j == 2 || j == 5) {
				cout << "|";
			}
		}
		cout << "\n";
		if (i == 2 || i == 5 || i == 8){
			cout << "********************************\n" << endl;
		}
	}
}


void clearArray(int tempList[rows][columns]) {
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			tempList[i][j] = 0;
		}

	}
}


void crossHatching(int tempArrayRows, int tempArrayColumns, int tempList[rows][columns]) {
	for (int i = 0; i < rows; i++){		//cross out all the elements that have the same value of column
		tempList[i][tempArrayColumns] = 1;
	}
	for (int j = 0; j < columns; j++){ // cross out all the elements that have the same value of row
		tempList[tempArrayRows][j] = 1;
	}
	tempList[tempArrayRows][tempArrayColumns] = 2; //highlight the specfic position
}

void start(int list[rows][columns], int number) {
	int tempList[rows][columns]; // help using cross hatching 
	clearArray(tempList);
	int tempRows = 0;
	int tempColumns = 0;

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			if (list[i][j] == number){
				crossHatching(i, j, tempList);
			}
		}
	}
	while (tempRows != 9 && tempColumns != 9){ //check every 3x3 matrix 
		checkAndAssignNumber(tempRows, tempColumns, tempList, list, number);
	}
}

void checkAndAssignNumber(int& tempRows, int& tempColumns, int tempList[rows][columns], int list[rows][columns], int number) {

	int count = 0;
	int assignRow;
	int assignColumn;
	bool isInside = false;
	
	for (int i = tempRows; i < tempRows + 3 && isInside == false; i++){
		for (int j = tempColumns; j < tempColumns + 3 && isInside == false; j++){
			if (tempList[i][j] == 2) {		//the number already exists in the 3X3 matrix
											// we go to the next matrix

				count = 0;
				isInside = true;			//Breaking out the double for loop 
			}
			else if (tempList[i][j] == 0 && list[i][j] == 0) {	//get the position for the entry that is not cross hatched and
																//also is empty (0)
				count = count + 1;								//If the count is 1, get the position. If it's greater than 1
				assignRow = i;									//we can still replace the value for assignRow and the assign Column
				assignColumn = j;								//But we will not use them since count > 1.
			}
		}
	}
	if (count == 1){											//it's the only empty entry and we assign number to that position 
		list[assignRow][assignColumn] = number;
		crossHatching(assignRow, assignColumn, tempList);		// cross hatch the entry 
	}
	tempColumns = tempColumns + 3;
	if (tempColumns == 9 && tempRows != 9) {

		tempRows = tempRows + 3;
		tempColumns = 0;
	}
}

bool isFilled(int list[rows][columns]) {
	int count = 0;
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++) {
			if (list[i][j] == 0) {
				count = count + 1;
			}
		}
	}
	if (count != 0) {
		return false;
	}
	else {
		return true;
	}
}


