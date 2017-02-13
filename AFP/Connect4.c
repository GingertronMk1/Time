#include <stdio.h>
#include <string.h>

#define NUM_ROWS 6
#define NUM_COLS 7

int drawBoard(char board[NUM_ROWS][NUM_COLS]) {
  int row, col;
  int pieces = 0;
  for(row = 1; row <= NUM_ROWS; row++) {
    printf("|");
    for(col = 0; col < NUM_COLS; col++) {
      char currentPiece = board[NUM_ROWS-row][col];
      printf("%c|", currentPiece);
      if(currentPiece != ' ') {
        pieces++;
      }
    }
    printf("\n");
  }
  printf(" 1 2 3 4 5 6 7\n");
  return pieces;
}

int winCheck(char board[NUM_ROWS][NUM_COLS]) {
  int row, col, hasWon;
  char current;
  for (row = 0; row < NUM_ROWS-4; row++) {
    for (col = 0; col < NUM_COLS-4; col++) {
      current = board[row][col];
      if(current != ' ') {
        if(current == board[row][col+1] && current == board[row][col+2] && current == board[row][col+3]) {
          printf("\n\n%c has won!\n\n", current);
          return 1;
        } else if(current == board[row+1][col] &&current == board[row+2][col] &&current == board[row+3][col]) {
          printf("\n\n%c has won!\n\n", current);
          return 1;
        } else if(current == board[row+1][col] &&current == board[row+2][col] &&current == board[row+3][col]) {
          printf("\n\n%c has won!\n\n", current);
          return 1;
        } else if(current == board[row+1][col+1] &&current == board[row+2][col+2] &&current == board[row+3][col+3]) {
          printf("\n\n%c has won!\n\n", current);
          return 1;
        } else if(current == board[row-1][col-1] &&current == board[row-2][col-2] &&current == board[row-3][col-3]) {
          printf("\n\n%c has won!\n\n", current);
          return 1;
        }
      }
    }
  }
  return 0;
}

int main(int argc, char* argv[]) {
  /* Variable Declaration */
  int choice, noOfPieces; // choice is the chosen column, noOfPieces keeps track of turn
  int endState = 0;       // if this turns 1, the game ends
  char choices[2] = {'x', 'o'};   // for determining which char to use
  char gameBoard[NUM_ROWS][NUM_COLS] = {{' ',' ',' ',' ',' ',' ',' '},
                                        {' ',' ',' ',' ',' ',' ',' '},
                                        {' ',' ',' ',' ',' ',' ',' '},
                                        {' ',' ',' ',' ',' ',' ',' '},
                                        {' ',' ',' ',' ',' ',' ',' '},
                                        {' ',' ',' ',' ',' ',' ',' '}};
  int height[NUM_COLS] = {0, 0, 0, 0, 0, 0, 0}; // so we know how high to build

  /* Game Logic */
  do {
    noOfPieces = drawBoard(gameBoard);
    printf("What column would you like to play?\n");
    scanf("%d", &choice);
    if(0 < choice && choice < 8 && height[choice-1] < NUM_ROWS){
      choice--;
      gameBoard[height[choice]++][choice] = choices[noOfPieces%2];
      printf("You have selected column %d.\n", choice+1);
    } else {
      printf("Please select a valid input\n");
    }
    endState = winCheck(gameBoard);
  } while(noOfPieces < NUM_COLS*NUM_ROWS && endState == 0);
  drawBoard(gameBoard);
  return 0;
}
