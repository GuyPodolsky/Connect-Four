#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"

/* Made by Guy Podolsky, I.D. number: 206799199.
 * The program is a "connect four" game of two players.
 * Each round one of the players chooses the column number where he would like to place his sign
 * The winner is the first player that achieved a sequence of four of his signs in row, column or diagonal*/

/*********************************** Board ***********************************/

#define ROWS 6 
#define COLS 7
#define MAXIMUM_ROUNDS 42 //there are 42 cells
#define playerOneSign 'X'
#define playerTwoSign 'O'
#define emptyCell ' '
char board[ROWS][COLS];

/******************************** End of board *******************************/

/********************* Built-in functions declarations ***********************/

void initBoard();
	/// This function initializes the game board by assigning each cell
	/// with ' ' (resulting with an empty game board).

char getCell(int row, int col);
	/// This function gets a row number and a column number (a cell),
	/// and returns the character in that cell (could be 'X', 'O' or ' ').
	/// For example:
	/// char c = getCell(1, 1);

void setCell(int row, int col, char sign);
	/// This function gets a row number, a column number and a sign,
	/// and assigns the cell with the given sign.
	/// For example:
	/// setCell(1, 1, 'X');

void clearScreen();
	/// This function clears the screen.
	
/****************** End of built-in functions declaration ********************/

/*********************** Declaration of my functions *************************/

void printBoard();
	/// This function prints out the board.

int getPlayerInput(int playerNumber);
	/// This function gets the player's number
	/// The function requests input of the column number that the player willing to choose
	/// The function checks that the input is valid and if so it sets the player's sign at the chosen column
	/// The function returns the number of the column that the player chose

bool isValidInput(int input);
	/// This function gets the player's input value
	/// The function checks if the input is valid
	/// The function returns a true value if the input is a number between 1 to 7 and a false value if not
	
int numOfFreeRowsInCol(int numOfCol);
	/// The functions gets a column number
	/// The function returns the number of the latest available row

bool isThereIsWinner(int playerNumber, int numOfCol);
	/// The function gets player's number and the column number that the user chose
	/// The function checks if the player's last input caused a winning
	/// If the last player's move caused a winning the function returns true if not it returns false

bool fourInRow(char playerSign, int numOfCol);
	/// The function gets the player's character and the column number that the user chose
	/// The function checks if there is a sequence of the same 4 sign's of the player in a row
	/// The function returns a true value if yes and false if not

bool fourInColumn(char playerSign, int numOfCol);
	/// The function gets the player's character and the column number that the user chose
	/// The function checks if there is a sequence of the same 4 sign's of the player in a column
	/// The function returns a true value if yes and false if not

bool fourInDiagonal(char playerSign, int col, int row);
	/// The function gets the player's character and the column number that the user chose
    /// The function checks if there is a sequence of the same 4 sign's of the player in a diagonal
    /// The function returns a true value if yes and false if not
    
bool fourInOpsDiagonal(char playerSign, int col, int row);\
	/// The function gets the player's character and the column number that the user chose
    /// The function checks if there is a sequence of the same 4 sign's of the player in an opposite diagonal
    /// The function returns a true value if yes and false if not

/********************* End of my functions declaration ***********************/

/******************************** Main ***************************************/

int main()
{
	//variables declaration
    bool isVicOrTie;
    int playerNumber,numOfCol,numberOfRounds;
	
    //Setting a default value to the variables
    numberOfRounds = 0;
    playerNumber = 1;
    isVicOrTie = false;

    initBoard(); //clears the board
    printBoard(); //prints the empty board
    while(!isVicOrTie) //looping until one of the players is the winner
    {
        numOfCol = getPlayerInput(playerNumber); //sets an input and gets the column number.
        clearScreen(); //clears the previous outputs
        printBoard(); //prints the up to date board (after the player's input)
        numberOfRounds++; //rises the round count by 1
        isVicOrTie = isThereIsWinner(playerNumber,numOfCol); //checks if the last move caused the winning of the player
        if (isVicOrTie) //if the last move caused the winning of the player
            printf("Player number %d won! :-)\n",playerNumber); //prints out a message of winning to the winning player
        else if(numberOfRounds==MAXIMUM_ROUNDS) //if the last move does not cause the player to win and all 42 cells are occupied, it is a draw
        {
            isVicOrTie = true; //if it is a draw.
            printf("There's a tie!");
        }//end of else if(numberOfRounds==42) 
		//the next 4 lines switches between the players
        if (playerNumber == 2) 
            playerNumber = 1;
        else
            playerNumber = 2;
    }//end of while(!isVictory)
}//end of main

/**************************** End of main ************************************/

/******************** Built-in function implementations **********************/

char getCell(int row, int col)
{
    return board[row - 1][col - 1];
}

void setCell(int row, int col, char sign)
{
    board[row - 1][col - 1] = sign;
}

void initBoard()
{
    int i, j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            setCell(i+1, j+1, ' ');
        }
    }
}

void clearScreen()
{
    system("cls");
}

/****************End of built-in function implementations ********************/

/********************* My functions implementations **************************/

void printBoard()
{
    int i,j;//variables declaration
    printf("   1  2  3  4  5  6  7\n"); //prints the numbers of the columns.
    for (i=1;i<=ROWS;i++)
    {
        printf("%c  ",((char)(i-1)+'A')); //prints the character that represents the number of the row.
        for (j=1;j<=COLS;j++)
        {
            printf("%c  ",getCell(i,j)); //prints the char value of the cell that placed at row i and column j.
        }//end of for j
        printf("\n");//move to the next line.
    }//end of for i
    printf("\n");//move to the next line.
}//end of printBoard

int getPlayerInput(int playerNumber)
{
    int numOfCol,freeRow; //function's variables declaration
    printf("Player number %d:\nPlease enter column input (a number between 1-7): ", playerNumber); //prints out an input request from the player
    scanf("%d", &numOfCol); //gets the number of column that the player chose
    freeRow = numOfFreeRowsInCol(numOfCol); //gets the latest available row at the column 
    while (!isValidInput(numOfCol) || (freeRow==0)) //looping until the player's input is valid
    {
        if (!isValidInput(numOfCol)) //if the input is not a number between 1 to 7
        {
            printf("\nInvalid Input, Please enter column input (a number between 1-7): ");
        }//end of if (!isValidInput(numOfCol))
        else //if the column is full
        {
            printf("\nInvalid Input, The column is full, Please choose another column (a number between 1-7): ");
        }//end of else
        scanf("%d", &numOfCol); //gets a new input of column number from the player
        freeRow = numOfFreeRowsInCol(numOfCol); //gets the latest available row at the column 
    }//end of while (!isValidInput(numOfCol) || !numOfFreeRowsInCol(numOfCol))
    
    //the next 4 code lines set at the column's last available row the player's sign
    if (playerNumber == 1) //if this is player number 1
        setCell(freeRow, numOfCol, playerOneSign);
    else //if this is player number 2
        setCell(freeRow, numOfCol,playerTwoSign);
	
    return numOfCol; //returns the number of column that the player chose
}//end of getPlayerInput

bool isValidInput(int input)
{
    if ((input>=1)&&(input<=7)) //if the number is between 1 to 7
        return true;
    else //if the number is not between 1 to 7
        return false;
}//end of isValidInput

int numOfFreeRowsInCol(int numOfCol)
{
    int count,i; //function's variables declaration
    count = ROWS; //setting a default value to count variable
    for (i=1;i<=ROWS;i++) //this code line and the next 4 code line counts how many occupied rows at the column
    {
        if (getCell(i,numOfCol)!=emptyCell)
            count--;
    }//end of for i
    return count; //returns the number of the latest available row at the column
}//end of numOfFreeRowsInCol

bool isThereIsWinner(int playerNumber, int numOfCol)
{
    int numOfRow; //this code line and the next 2 code lines declares the function's variables
    char playerSign;
    bool isWinner;

    numOfRow = numOfFreeRowsInCol(numOfCol) + 1; //sets the number of the row where the last player set his sign at
    if (playerNumber == 1) //this code line and the next 3 code lines set the appropriate character into "playerSign" variable depending on the player's number
        playerSign = playerOneSign;
    else
        playerSign = playerTwoSign;

	//the next code line checks is there is a sequence of four player's signs in row, column and diagonal
    isWinner = fourInColumn(playerSign, numOfCol) || fourInRow(playerSign, numOfCol) || fourInOpsDiagonal(playerSign, numOfCol, numOfRow) || fourInDiagonal(playerSign, numOfCol, numOfRow);
    return isWinner;//returns true if there is a sequence of four and false if there isn't
}//end of isThereIsWinner

bool fourInRow(char playerSign, int numOfCol)
{
    int count,i,j; //function's variables declaration
    count = 0; //sets a default value into "count" variable

    for (i=(numOfFreeRowsInCol(numOfCol)+1),j=1; count != 4 && j <= COLS; j++) //this code line and the next 6 code lines check if there is a sequence of 4 in row
    {
        if (getCell(i,j)==playerSign)
            count++;
        else
            count=0;
    }//end of for

    if (count >= 4) //if there is at least a sequence of 4 signs of the player in diagonal
        return true;
    else //if there isn't a sequence of 4 in row
        return false;
} //end if fourInRow

bool fourInColumn(char playerSign, int numOfCol)
{
    int count,i,j;//function's variables declaration
    count = 0;//sets a default value into "count" variable

    for (j=numOfCol,i=1; count != 4 && i <= ROWS; i++) //this code line and the next 6 code lines check if there is a sequence of 4 in column
    {
        if (getCell(i,j)==playerSign)
            count++;
        else
            count=0;
    }//end of for

    if (count >= 4) //if there is at least a sequence of 4 signs of the player in column
        return true;
    else //if there isn't a sequence of 4 in row
        return false;
}//end of fourInColumn

bool fourInDiagonal(char playerSign, int col,int row)
{
    int i, j, countDown, countUp; //function's variables declaration
    countDown = 0; //sets a default value into "countDown" variable
    countUp = 0; //sets a default value into "countUp" variable

    for (i = row, j = col; i <= ROWS && j > 0 && (getCell(i, j) == playerSign); i++, j--) //this code line and the next 3 code lines check how many signs of the player upwards there is in succession 
    {
        countDown++;
    }//end of the first for
    for (i = row, j = col; i > 0 && j <= COLS && (getCell(i, j) == playerSign); i--, j++) //this code line and the next 3 code lines check how many signs of the player downwards there is in succession 
    {
        countUp++;
    }//end of the secound for
    if (countDown + countUp >= 5) //if there is at least a sequence of 4 signs of the player in diagonal
        return true; 
    else //if there is not a sequence of 4 numbers in diagonal
        return false;
}//end of fourInDiagonal

bool fourInOpsDiagonal(char playerSign, int col,int row)
{
    int i,j,countDown, countUp; //function's variables declaration
    countDown = 0; //sets a default value into "countDown" variable
    countUp = 0; //sets a default value into "countUp" variable

    for (i = row, j = col; i <= ROWS && j <= COLS && (getCell(i, j) == playerSign); i++, j++) //this code line and the next 3 code lines check how many signs of the player upwards there is in succession
	{
		countDown++;
	}//end of the first for
    for (i = row, j = col; i > 0 && j > 0 && (getCell(i, j) == playerSign); i--, j--) //this code line and the next 3 code lines check how many signs of the player downwards there is in succession
    {
        countUp++;
    }//end of the secound for
	if (countDown+countUp>=5) //if there is at least a sequence of 4 signs of the player in diagonal
        return true;
    else //if there is not a sequence of 4 numbers in diagonal
        return false;
}//end of fourInOpsDiagonal

/******************** End of my functions implementations ********************/