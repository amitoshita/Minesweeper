#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define NumOfCols 22
#define NumOfRows 22
#define TotalSteps8x8 64
#define TotalSteps12x12 144

void FloodFill(char real[][NumOfCols], int curRow, int curCol, int R, int C);
void initboard(char real[][NumOfCols], int R, int C); //This function put '*' and numbers that are not visible for user.
void putX(char board[][NumOfCols], int R, int C);                   // This function put X all over "show" board
void ShowBoard(char board[][NumOfCols], int R, int C);// This function is what user can see on display.
void OpenXfirsts(char real[][NumOfCols], char show[][NumOfCols], int C, int R);  // This function open first X colnums that user choose.
char CheakAround(int R, int C, char real[][NumOfCols]); // This funtion count num of bombs around.
void print_menu();                                    // Board game options
void OpenXfirsts(char real[][NumOfCols], char show[][NumOfCols], int C, int R);
void cases(int choice, int real[][NumOfCols], int show[][NumOfCols]);
bool checkStep(char show[][NumOfCols], int row, int colNum, int R, int C, int TotalSteps); // This function check if  user put invalid input
bool isLose(char real[][NumOfCols], char show[][NumOfCols], int row, int col, int R, int C); //This function check if input is a bumb
bool Won(char show[][NumOfCols], int R, int C);                     // This function cheak if you done.

void clearScreen()
{
	system("cls");
}

int main() {

	char real[NumOfRows][NumOfCols];
	char show[NumOfRows][NumOfCols];
	int choice;
	print_menu();
	scanf_s("%d", &choice);
	cases(choice, real, show);

}

void cases(int choice, int real[][NumOfCols], int show[][NumOfCols]) {

	bool win = false;

	switch (choice)
	{
	case 1:
	{
		putX(show, 8, 8);
		initboard(real, 8, 8);
		ShowBoard(show, 8, 8);

		while (win != true) {
			int row, col;
			printf("Welcome to Minesweeper. Please enter row and colnum:\n");
			scanf_s("%d %d", &row, &col);
			while (!checkStep(show, row, col, 8, 8, TotalSteps8x8))
			{
				printf("Invalid step. Try again\n");
				scanf_s("%d %d", &row, &col);
			}
			if (isLose(real, show, row, col, 8, 8) == true)
				break;
			if (Won(show, 8, 8))
				win = true;
			ShowBoard(show, 8, 8);
		}

		if (win == false)
		{
			ShowBoard(show, 8, 8);
			printf("You have hit by a bomb. You loose\n");
		}

		else
			printf("You won!!!\n");
	}
	break;
	case 2:
	{

		putX(show, 12, 12);
		initboard(real, 12, 12);
		ShowBoard(show, 12, 12);

		while (win != true) {
			int row, col;
			printf("Welcome to Minesweeper. Please enter row and colnum:\n");
			scanf_s("%d %d", &row, &col);
			while (!checkStep(show, row, col, 12, 12, TotalSteps12x12))
			{
				printf("Invalid step. Try again\n");
				scanf_s("%d %d", &row, &col);
			}
			if (isLose(real, show, row, col, 12, 12) == true)
				break;
			if (Won(show, 12, 12))
				win = true;
			ShowBoard(show, 12, 12);
		}

		if (win == false)
		{
			ShowBoard(show, 12, 12);
			printf("You have hit by a bomb. You loose\n");
		}

		else
			printf("You won!!!\n");
	}
	default:
		break;
	}

}

char CheakAround(int R, int C, char real[][NumOfCols])
{
	int cnt = 0;

	if (R + 1 < NumOfRows && real[R + 1][C] == '*')
		cnt++;
	if (C + 1 < NumOfCols && real[R][C + 1] == '*')
		cnt++;
	if (R - 1 >= 0 && real[R - 1][C] == '*')
		cnt++;
	if (C - 1 >= 0 && real[R][C - 1] == '*')
		cnt++;
	if (R + 1 < NumOfRows && C + 1 < NumOfCols && real[R + 1][C + 1] == '*')
		cnt++;
	if (R - 1 >= 0 && C + 1 < NumOfCols && real[R - 1][C + 1] == '*')
		cnt++;
	if (R - 1 >= 0 && C - 1 >= 0 && real[R - 1][C - 1] == '*')
		cnt++;
	if (R + 1 < NumOfRows && C - 1 >= 0 && real[R + 1][C - 1] == '*')
		cnt++;


	char countBombs;
	if (cnt == 0)
	{
		countBombs = ' ';
	}
	
	else
		countBombs = cnt + '0';

	return countBombs;
}

void print_menu()
{
	printf("Welcome to MineSweeper!\n\n");
	printf("Please choose one of the following options:\n\n");
	printf("1 - for size 8X8\n\n");
	printf("2 - for size 12X12\n\n");
	printf("3 - for size 15X15\n\n");
	printf("4 - for custom size\n\n");
	printf("0 - Exit\n");
}

bool checkStep(char show[][NumOfCols], int row, int colNum, int R, int C, int TotalSteps)
{
	if (colNum >= 0 && colNum < C && row >= -1 && row < R && show[row][colNum] == 'X')
	{
		return true;
	}
	if (row == -1 && colNum <= TotalSteps)
		return true;

	return false;
}

void initboard(char real[][NumOfCols], int R, int C) {
	srand(time(NULL));

	int Kefel = R * C;
	int numOfBombs = sqrt(Kefel);
	int i, j, cnt = 0;
	for (i = 0; i < R; i++)
		for (j = 0; j < C; j++)
		{
			real[i][j] = 'O';
		}
	while (cnt < numOfBombs)
	{
		int row = rand() % R;
		int col = rand() % C;

		if (real[row][col] == 'O' && real[row][col] != '*')
		{
			real[row][col] = '*';
			cnt++;
		}
	}
	for (i = 0; i < R; i++)
		for (j = 0; j < C; j++)
		{
			if (real[i][j] != '*')
				real[i][j] = CheakAround(i, j, real);
		}

}
void ShowBoard(char show[][NumOfCols], int R, int C)
{
	int i, j;
	system("cls");
	printf("  ");
	for (int i = 0; i < R; i++)
		printf("%4d", i);
	printf("\n");
	for (int i = 0; i < C * 5 - 5; i++)
		printf("_");
	printf("\n");
	for (int i = 0; i < R; i++)
	{
		printf("%4d|", i);
		for (int j = 0; j < C; j++)
		{
			printf("%c | ", show[i][j]);
		}
		printf("\n");
	}


}

void putX(char show[][NumOfCols], int R, int C) {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			show[i][j] = 'X';
}

bool isLose(char real[][NumOfCols], char show[][NumOfCols], int row, int col, int R, int C)
{
	if (real[row][col] == '*') {
		show[row][col] = '*';
		return true;
	}
	else if (row > -1)
		show[row][col] = CheakAround(row, col, real);
	else if (row == -1)
		OpenXfirsts(real, show, -1,  col);
	return false;
}

bool Won(char show[][NumOfCols], int R, int C)
{
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (show[i][j] == 'X')
				return false;
	return true;
}

void OpenXfirsts(char real[][NumOfCols], char show[][NumOfCols], int R, int C) {
	int j;
	for (j = 0; j < C; j++)
		if (real[0][j] != '*')
			show[0][j] = CheakAround(0, j, real);

}

void FloodFill(char real[][NumOfCols], int curRow, int curCol, int R, int C)
{
	if (real[curRow][curCol] == 'O')
	{
		real[curRow][curCol] = ' ';

		if (curRow < R - 1)
			FloodFill(real, curRow + 1, curCol, R, C); 
		if (curCol < C - 1)
			FloodFill(real, curRow, curCol + 1, R, C);
		if (curRow > 0)
			FloodFill(real, curRow - 1, curCol, R, C);
		if (curRow > 0)
			FloodFill(real, curRow, curCol - 1, R, C);

	}
}