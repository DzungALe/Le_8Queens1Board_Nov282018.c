/*=====================================================================================================================================
FileName: Le_LongDiv_Dec282018.c
FileType: C Source File
Author : Dung Le
Created On : 12/28/2018 9:12:00 PM
Last Modified On : 12/28/2018 10:32:00 PM
Description : 
Editor: Notepad++ Ver. 7.5.9
Complier: Raspbian 6.3.0
Kernel: Linux raspberrypi 4.9.59-v7+
=====================================================================================================================================*/
#include <stdio.h>
#include <string.h> //mem.cpy()

#define CHESSBOARDMAX 8 

typedef char chess_board_t[CHESSBOARDMAX][CHESSBOARDMAX]; //Chess board is an 8x8 array
typedef int int32_t; 
typedef struct{ //Queen_pos_t struct contains two int values
	int32_t x;
	int32_t y;
}	queen_pos_t; 

queen_pos_t queen_pos_board[CHESSBOARDMAX]; //1 dimensional array contain 8 values 

void print_board();

static int sol_count = 0; //Solution counter

/*
	Removes all spaces that the queen threatens once placed
*/
void removepos(int32_t x, int32_t y, chess_board_t board)
{
	int32_t pos_x, pos_y, i;
	
	//Removes rows and columns at position x, y
	for(i = 0; i < CHESSBOARDMAX; i++)
		board[x][i] = board[i][y] = 1;
	//Removes all diagonal positions going up and right
	for(pos_x = x, pos_y = y; (pos_x >= 0) && (pos_y < CHESSBOARDMAX); pos_x--, pos_y++)
		board[pos_x][pos_y] = 1;
	//Removes all diagonal positions going down and left
	for(pos_x = x, pos_y = y; (pos_x < CHESSBOARDMAX) && (pos_y >= 0); pos_x++, pos_y--)
		board[pos_x][pos_y] = 1;
	//Removes all diagonal positions going up and left
	for(pos_x = x, pos_y = y; (pos_x >= 0) && (pos_y >= 0); pos_x--, pos_y--)
		board[pos_x][pos_y] = 1;
	//Removes all diagonal positions going down and right
	for(pos_x = x, pos_y = y; (pos_x < CHESSBOARDMAX) && (pos_y < CHESSBOARDMAX); pos_x++, pos_y++)
		board[pos_x][pos_y] = 1;
}	

/*
	Calculates all possibilities of 8 queens on one chess board
*/
void calcqueens(int queenindex, chess_board_t board)
{
	int32_t y;
	chess_board_t local_board; //One local board, changes after every step

	for(y = 0; y < CHESSBOARDMAX; y++){
		if(board[queenindex][y] == 0){
			//Assigns queen index value and y value if space contains a 0; queen can be placed in that space
			queen_pos_board[queenindex].x = queenindex; 
			queen_pos_board[queenindex].y = y;
			memcpy((void *)local_board, board, sizeof(chess_board_t)); //
			removepos(queenindex, y, local_board);
			if(queenindex < CHESSBOARDMAX - 1)
				calcqueens(queenindex + 1, local_board);	
			else
				print_board();
		}
	}	
}

/*
	Prints out chess board with solutions 
*/
void print_board() 
{
	int32_t pos_x, pos_y;
	
	printf("Solution #%d\n", ++sol_count);
	printf("    a  b  c  d  e  f  g  h\n"); //Prints letters for notation
	for(pos_x = 0; pos_x < CHESSBOARDMAX; pos_x++){
		printf(" %d ", 8-pos_x); //Prints columns
		for(pos_y = 0; pos_y < CHESSBOARDMAX; pos_y++){
			
			if(pos_x == queen_pos_board[pos_x].x && pos_y == queen_pos_board[pos_x].y)
				printf(" Q "); //Prints letter Q for queen
			else{
				//If the row is an even row (starting from 0)
				if(pos_x % 2 == 0){ 
					if(pos_y % 2 == 0)
						printf(" ■ "); //If even column, prints light square
					else
						printf(" □ "); //If odd column, prints dark square
				}
				//If the row is an odd row 
				else{
					if(pos_y % 2 == 0) 
						printf(" □ "); //If even column, prints dark square
					else
						printf(" ■ "); //If odd column, prints light square
				}	
			}
		}
		
		printf(" %d ", 8 - pos_x); //Prints columns
		printf("\n");
	}
	
	printf("    a  b  c  d  e  f  g  h \n\n"); //Prints letters for notation
}	

void main()
{
	int32_t x,y;
    chess_board_t board;
	
	//Initiates 8x8 chess board with all values to 0
	for(x = 0; x < CHESSBOARDMAX; x++){
		for(y = 0; y < CHESSBOARDMAX; y++){
			board[x][y] = 0;
		}
	}
	calcqueens(0, board);
}
	