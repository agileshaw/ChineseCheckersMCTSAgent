#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "node.h"

#ifndef _MARBLEH_
#define _MARBLEH_

struct Moves
{
	int from[2];
	int to[2];
	float value;
	int visits;
};

struct Marble 
{
	int position[2];
	int surrounding[6];
	struct Moves last_move;
	int move_total;
};

/*
 * Purpose: initialize a Marble struct for player 1 (black marbles)
 * Parameters: black - a pointer to a Marble struct, 
 *			index - an int variable indicating direction
 * Return value: none
 */
void initialBlack (struct Marble *black, int index);

/*
 * Purpose: initialize a Marble struct for player 2 (red marbles)
 * Parameters: red - a pointer to a Marble struct, 
 *			index - an int variable indicating direction
 * Return value: none
 */
void initialRed (struct Marble *black, int index);

/*
 * Purpose: check the surrounding slots occupation status for each marble
 * Parameters: marble - a pointer to a Marble struct,
 *			board - the 2D Array board representation,
 *			rowIndex - the constant array of row index
 * Return value: none
 */
void surroundingPosition (struct Marble *marble, int board[17][13], const int rowIndex[17]);

/*
 * Purpose: check all available moves of each marble
 * Parameters: marble - a pointer to a Marble struct,
 *			moves - a pointer to a queue of Node struct pointers containing a Move Struct pointer as data,
 *			board - the 2D array of game board,
 *			rowIndex - the constant array of row index,
 *			player - an int variable indicating player,
 *			range - an array of integers indicating the range of positions for a player's marbles
 * Return value: none
 */
void checkMoves (struct Marble *marble, struct Queue** moves, int board[17][13], const int rowIndex[17], int player, int range[]);

/*
 * Purpose: make an adjacent single move
 * Parameters: row - an int variable indicating row number, 
 *			col - an int variable indicating column number,
 *			move - a pointer of struct Moves,
 *			board - the 2D array of game board,
 *			rowIndex - the constant array of row index,
 *			index - an int variable indicating direction of movement
 * Return value: none
 */
void adjacentMove (int row, int col, struct Moves *move, int board[17][13], const int rowIndex[17], int index);

/*
 * Purpose: make an single jump move
 * Parameters: row - an int variable indicating row number, 
 *			col - an int variable indicating column number,
 *			move - a pointer of struct Moves,
 *			board - an 2D array of game board,
 *			index - an int variable indicating direction of movement
 * Return value: a bool variable indicating whether the jump move is valid
 */
bool jumpMove (int row, int col, struct Moves *move, int board[17][13], int index);

/*
 * Purpose: check and perform a sequence of jump moves
 * Parameters: ori_row - an int variable indicating row number of the original position, 
 *			ori_col - an int variable indicating column number of the original position,
 *			tmp_row - an int variable indicating row number of the temporary position, 
 *			tmp_col - an int variable indicating column number of the temporary position,
 *			avoid - an int variable indicating the direction of previous location,
 *			moves - a pointer to a queue of Node struct pointers containing a Move Struct pointer as data,
 *			board - the 2D array of game board,
 *			rowIndex - the constant array of row index,
 *			player - an int variable indicating player
 *			range - an array of integers indicating the range of positions for a player's marbles
 * Return value: none
 */
void sequentialJump (int ori_row, int ori_col, int tmp_row, int tmp_col, int avoid, struct Queue** moves, int board[17][13], const int rowIndex[17], int player, int range[]);

/*
 * Purpose: calculate the value of a black marble's move by considering both static position value and cluster factor
 * Parameters: move - a pointer of struct Moves,
 * 			row - an int variable indicating row number of the original position, 
 *			col - an int variable indicating column number of the original position,
 *			tmp_row - an int variable indicating row number of the temporary position, 
 *			tmp_col - an int variable indicating column number of the temporary position,
 *			range - an array of integers indicating the range of positions for a player's marbles
 * Return value: none
 */
void moveValueBlack (struct Moves* move, int row, int col, int tmp_row, int tmp_col, int range[]);

/*
 * Purpose: calculate the value of a red marble's move by considering both static position value and cluster factor
 * Parameters: move - a pointer of struct Moves,
 * 			row - an int variable indicating row number of the original position, 
 *			col - an int variable indicating column number of the original position,
 *			tmp_row - an int variable indicating row number of the temporary position, 
 *			tmp_col - an int variable indicating column number of the temporary position,
 *			range - an array of integers indicating the range of positions for a player's marbles
 * Return value: none
 */
void moveValueRed (struct Moves* move, int row, int col, int tmp_row, int tmp_col, int range[]);

/*
 * Purpose: calculate the value of a red marble's move by considering both static position value and cluster factor
 * Parameters: moves - a pointer to a queue of Node struct pointers containing a Move Struct pointer as data,
 * 			selected - a pointer of struct Moves,
 * Return value: none
 */
void selectRandom(struct Queue* moves, struct Moves* selected);

/*
 * Purpose: using current time as a random seed for rand() library function
 * Parameters: none
 * Return value: seed - an unsigned int variable
 */
unsigned seedCurTime();

#endif