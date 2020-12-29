#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//declaring functions
void playerMove(int theSeed);
void updateGame(int theSeed, int currentRow, int currentCol);
bool isDraw();
bool hasWon(int theSeed, int currentRow, int currentCol);
void printBoard();
void printCell(int content);

//defining constants to represent the seeds and cell contents
#define EMPTY  0
#define CROSS  1
#define NOUGHT 2
//defining constants to represent various game states
#define PLAYING 0
#define DRAW  1
#define CROSS_WON  2
#define NOUGHT_WON  3
//defining the number of rows and columns for the game board
#define ROWS  3
#define COLS  3

//declaring global variables
int board [ROWS][COLS]; //game board in 2D array, containing (EMPTY, CROSS, NOUGHT)
int currentState; //the current state of the game (PLAYING, DRAW, CROSS_WON, NOUGHT_WON)
int currentPlayer; //the current player (CROSS or NOUGHT)
int currentRow, currentCol; //current seed's row and column
char player1_name[20], player2_name[20]; //name of Player 1 and Player 2

int main () {
	//user input for the names of Player 1 and Player 2
	printf("Please enter the name of player 1 (X): ");
	scanf("%s", player1_name);
	printf("Please enter the name of player 2 (0): ");
	scanf("%s", player2_name);
	
	//initializing the game board contents and its current states
	for (int row = 0; row < ROWS; ++row) {
         for (int col = 0; col < COLS; ++col) {
            board[row][col] = EMPTY; //when all cells are empty
         }
      }
    printBoard();
	currentState = PLAYING; //ready to play
	currentPlayer = CROSS; //cross plays first, Player 1 is cross
	
	//play the game once
	do {
		playerMove(currentPlayer); //update current row and current column
		updateGame(currentPlayer, currentRow, currentCol); //update current state
		printBoard();
		//message that is printed when game is over
		if (currentState == CROSS_WON) {
		printf("Congrats Player 1! You are the winner.");
		printf("\n\n---GAME END---");
		} else if (currentState == NOUGHT_WON) {
		printf("Congrats Player 2! You are the winner.");
		printf("\n\n---GAME END---");
		} else if (currentState == DRAW) {
		printf("Game draw.");
		printf("\n\n---GAME END---");
		} 
		currentPlayer = (currentPlayer == CROSS) ? NOUGHT : CROSS; //switch player
	} while (currentState == PLAYING); //repeat if game is not over
	   
	return 0;
}

//player with the "theSeed" makes one move, with input validation
//update global variables "currentRow" and "currentCol"
void playerMove(int theSeed) {
      bool validInput = false; //for input validation
	  char position[20];
	  char quit[] =("quit");
	  char quit1[] =("Quit");
	  char quit2[] =("QUIT");
      int row, col;
      do {
         if (theSeed == CROSS) {
            printf("Player 1 (%s), please enter your move: ", player1_name);
         } else {
            printf("Player 2 (%s), please enter your move: ", player2_name);
         }
         scanf("%s", position);
         if(strcmp(position, quit) == 0||strcmp(position, quit1) == 0||strcmp(position, quit2) == 0){
			printf("\n\n---GAME END---");
         	exit(0);
		 }
         row = (position[0]-'0')-1; //since array index starts at 0 
         col = (position[2]-'0')-1;
         printf("board[%d][%d](%d)",row,col,board[row][col]);
         printf("\n");
         if (row >= 0 && row < ROWS && col >= 0 && col < COLS && board[row][col] == EMPTY) {
            currentRow = row;
            currentCol = col;
            board[currentRow][currentCol] = theSeed; //update game board content 
            validInput = true; //exit loop if input is valid
         } 
         else {
            printf("\nInvalid move. Please try again.\n");
         }
      } while (!validInput); //repeat until input is valid
}

//update the "currentState" after the player with "theSeed" has placed on (currentRow, currentCol)
void updateGame(int theSeed, int currentRow, int currentCol) {
	if (hasWon(theSeed, currentRow, currentCol)) { //check if it's the winning move
	 currentState = (theSeed == CROSS) ? CROSS_WON : NOUGHT_WON;
	} else if (isDraw()) { //check for draw
	 currentState = DRAW;
	}
	//otherwise, no change to currentState; so the game will continue
}

//return true if it is a draw, which means there are no empty cells left
bool isDraw() {
  for (int row = 0; row < ROWS; ++row) {
	 for (int col = 0; col < COLS; ++col) {
		if (board[row][col] == EMPTY) {
		   return false; //if an empty cell is found, it is not a draw
		}
	 }
  }
  return true; //when there are no empty cells, it is a draw
}

//return true if the player with "theSeed" has won after placing at (currentRow, currentCol)
bool hasWon(int theSeed, int currentRow, int currentCol) {
      return ((board[currentRow][0] == theSeed)			//3-in-the-row
				&& (board[currentRow][1] == theSeed) 
				&& (board[currentRow][2] == theSeed)
             || (board[0][currentCol] == theSeed)		//3-in-the-column
				&& (board[1][currentCol] == theSeed) 
				&& (board[2][currentCol] == theSeed)
             || (currentRow == currentCol)				//3-in-the-diagonal
				&& (board[0][0] == theSeed) 
				&& (board[1][1] == theSeed) 
				&& (board[2][2] == theSeed)
             || (currentRow + currentCol == 2)			//3-in-the-opposite-diagonal
				&& (board[0][2] == theSeed) 
				&& (board[1][1] == theSeed) 
				&& (board[2][0] == theSeed));
}

//print the game board
void printBoard() {
      printf("\n--- Tic Tac Toe Board ---\n");
      for (int row = 0; row < ROWS; ++row) {
		  printf("\t");
         for (int col = 0; col < COLS; ++col) {
            printCell(board[row][col]); //print each of the cell
            if (col != COLS - 1) {
               printf("|");	//print vertical partition
            }
         }
         printf("\n");
         if (row != ROWS - 1) {
            printf("\t-----------\n"); //print horizontal partition
         }
      }
      printf("\n");
}

//print a cell with the specified "content"
void printCell(int content) {
      switch (content) {
         case EMPTY:  printf("   "); break;
         case NOUGHT: printf(" O "); break;
         case CROSS:  printf(" X "); break;
      }
}
