//MINESWEEPER

#include<bits/stdc++.h>
using namespace std;


#define MAXSIDE 25
#define MAXMINES 99
#define MOVESIZE 526 

int SIDE ; // LENGTH OF THE BOARD
int MINES ; // NUMBER OF MINES ON THE BOARD
bool isValid(int row, int col);
bool isMine (int row, int col, char board[][MAXSIDE]);
void makeMove(int *x, int *y);// FUNCTION TO GET USER'S MOVE
int i = 0;



// FUNCTION TO PRINT CURRENT GAMEPLAY
void printBoard(char myBoard[][MAXSIDE])
{
	int i, j;

	printf (" ");

	for (i=0; i<SIDE; i++)
		printf ("%d ", i);

	printf ("\n\n");

	for (i=0; i<SIDE; i++)
	{
		printf ("%d ", i);

		for (j=0; j<SIDE; j++)
			printf ("%c ", myBoard[i][j]);
		printf ("\n");
	}
	return;
}

int countAdjacentMines(int row, int col, int mines[][2],
					char realBoard[][MAXSIDE])
{

	int i;
	int count = 0;


	//----------- 1ST NEIGBOR (NORTH) ------------

		// Only process this cell if this is a valid one
		if (isValid (row-1, col) == true)
		{
			if (isMine (row-1, col, realBoard) == true)
			count++;
		}

	//----------- 2ND NEIGBOR (SOUTH) ------------

		// Only process this cell if this is a valid one
		if (isValid (row+1, col) == true)
		{
			if (isMine (row+1, col, realBoard) == true)
			count++;
		}

	//----------- 3RD NEIGBOR (EAST) ------------

		// Only process this cell if this is a valid one
		if (isValid (row, col+1) == true)
		{
			if (isMine (row, col+1, realBoard) == true)
			count++;
		}

	//----------- 4TH NEIGBOR (WEST) ------------

		// Only process this cell if this is a valid one
		if (isValid (row, col-1) == true)
		{
			if (isMine (row, col-1, realBoard) == true)
			count++;
		}

	//----------- 5TH NEIGBOR (NORTH-EAST) ------------

		// Only process this cell if this is a valid one
		if (isValid (row-1, col+1) == true)
		{
			if (isMine (row-1, col+1, realBoard) == true)
			count++;
		}

	//-----------6TH NEIGBOR (NORTH-WEST) ------------

		// Only process this cell if this is a valid one
		if (isValid (row-1, col-1) == true)
		{
			if (isMine (row-1, col-1, realBoard) == true)
			count++;
		}

	//----------- 7TH NEIGBOR (SOUTH-EAST) ------------

		// Only process this cell if this is a valid one
		if (isValid (row+1, col+1) == true)
		{
			if (isMine (row+1, col+1, realBoard) == true)
			count++;
		}

	//----------- 8TH NEIGBOR (SOUTH-WEST) ------------


		if (isValid (row+1, col-1) == true)
		{
			if (isMine (row+1, col-1, realBoard) == true)
			count++;
		}

	return (count);
}

bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE],
			int mines[][2], int row, int col, int *movesLeft)
{

	if (myBoard[row][col] != 'X')
		return (false);

	int i, j;

	if (realBoard[row][col] == '*')
	{
		myBoard[row][col]='*';

		for (i=0; i<MINES; i++)
			myBoard[mines[i][0]][mines[i][1]]='*';

		printBoard (myBoard);
		printf ("\nYou lost!\n");
		return (true) ;
	}

	else
	{
		//CALCULATE THE NUMBER OF ADJACENT MINES AND PUT IT ON THE BOARD
		
		int count = countAdjacentMines(row, col, mines, realBoard);
		(*movesLeft)--;

		myBoard[row][col] = count + '0';

		if (!count)
		{

			if (isValid (row-1, col) == true)
			{
				if (isMine (row-1, col, realBoard) == false)
				playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft);
			}

			//----------- 2ND NEIGBOR (SOUTH) ------------

			
			if (isValid (row+1, col) == true)
			{
				if (isMine (row+1, col, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft);
			}

			//----------- 3RD NEIGBOR (EAST) ------------

			if (isValid (row, col+1) == true)
			{
				if (isMine (row, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft);
			}

			//----------- 4TH NEIGBOR (WEST) ------------

			if (isValid (row, col-1) == true)
			{
				if (isMine (row, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft);
			}

			//----------- 5TH NEIGBOR (NORTH-EAST) ------------

			if (isValid (row-1, col+1) == true)
			{
				if (isMine (row-1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
			}

			//----------- 6TH NEIGBOR NORTH-WEST) ------------

			if (isValid (row-1, col-1) == true)
			{
				if (isMine (row-1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
			}

			//----------- 7TH NEIGBOR (SOUTH-EAST) ------------

			if (isValid (row+1, col+1) == true)
			{
				if (isMine (row+1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
			}

			//----------- 8TH NEIGBOR (SOUTH-WEST) ------------

			if (isValid (row+1, col-1) == true)
			{
				if (isMine (row+1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
			}
		}

		return (false);
	}
}

//FUNCTION TO PLACE MINES RANDOMLY
void placeMines(int mines[][2], char realBoard[][MAXSIDE])
{
	bool mark[MAXSIDE*MAXSIDE];

	memset (mark, false, sizeof (mark));

	for (int i=0; i<MINES; )
	{
		int random = rand() % (SIDE*SIDE);
		int x = random / SIDE;
		int y = random % SIDE;

		if (mark[random] == false)
		{
			// ROW INDEX OF MINE
			mines[i][0]= x;
			// COLUMN INDEX OF MINE
			mines[i][1] = y;

			// PLACE OF THE MINE
			realBoard[mines[i][0]][mines[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}

	return;
}

void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE])
{
	
	srand(time (NULL));

	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
		{
			myBoard[i][j] = realBoard[i][j] = 'X';
		}
	}

	return;
}

void cheatMinesweeper (char realBoard[][MAXSIDE])
{
	printf ("The mines locations are-\n");
	printBoard (realBoard);
	return;
}

//PUTTING MINE IN RANDOM PLACE
void replaceMine (int row, int col, char board[][MAXSIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
			{
				
				if (board[i][j] != '*')
				{
					board[i][j] = '*';
					board[row][col] = 'X';
					return;
				}
			}
	}
	return;
}

// FUNCTION TOPLAY MINE
void playMinesweeper ()
{
	
	bool gameOver = false;

	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];

	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[MAXMINES][2]; // STORES (X,Y) COORDINATES OF ALL MINES.

	initialise (realBoard, myBoard);

	// PLACING THE MINES RANDOMLY
	placeMines (mines, realBoard);

	int currentMoveIndex = 0;
	while (gameOver == false)
	{
		printf ("\nCurrent Status of Board : \n", i + 1);
		printBoard (myBoard);
		makeMove (&x, &y);
		i++;
		// THIS IS TO GUARANTEE THAT THE FIRST MOVE IS ALWAYS SAFE
		if (currentMoveIndex == 0)
		{
			
			if (isMine (x, y, realBoard) == true)
				replaceMine (x, y, realBoard);
		}

		currentMoveIndex ++;

		gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft);

		if ((gameOver == false) && (movesLeft == 0))
		{
			printf ("\nYou won !\n");
			gameOver = true;
		}
	}
	return;
}

//FUNCTION TO CHOOSE LEVEL
void chooseLevel()
{

	int level;

	printf ("Enter the Level:\n");
	printf ("Enter 0 for (5 * 5 Cellse and 6 Mines)\n");
	printf ("Enter 1 for (6 * 6 Cellse and 7 Mines)\n");
	printf ("Enter 2 for (7 * 7 Cellse and 8 Mines)\n");
	printf ("Enter 3 for (8 * 8 Cellse and 9 Mines)\n");
	printf ("Enter 4 for (9 * 9 Cellse and 10 Mines)\n");
	printf ("Enter 5 for (10 * 10 Cellse and 11 Mines)\n->");

	scanf ("%d", &level);

	if (level == 0)
	{
		SIDE = 5;
		MINES = 6;
	}

	if (level == 1)
	{
		SIDE = 6;
		MINES = 7;
	}

	if (level == 2)
	{
		SIDE = 7;
		MINES = 8;
	}
	if (level == 2)
	{
		SIDE = 8;
		MINES = 9;
	}
	if (level == 2)
	{
		SIDE = 9;
		MINES = 10;
	}
	if (level == 2)
	{
		SIDE = 10;
		MINES = 11;
	}

	return;
}

// EXECUTION
int main()
{

	chooseLevel ();

	playMinesweeper ();

	return (0);
}

bool isValid(int row, int col)
{
	
	return (row >= 0) && (row < SIDE) &&
		(col >= 0) && (col < SIDE);
}

bool isMine (int row, int col, char board[][MAXSIDE])
{
	if (board[row][col] == '*')
		return (true);
	else
		return (false);
}

// FUNCTION TO GET USER'S MOVE
void makeMove(int *x, int *y)
{
	//TAKE THE INPUT MOVE
	printf("Enter row: \n");
	scanf("%d", x);
	printf("Enter column: \n");
	scanf("%d", y);
	return;
}
