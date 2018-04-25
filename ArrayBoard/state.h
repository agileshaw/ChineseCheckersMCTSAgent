#include <stdlib.h>
#include <stdio.h>
#include "marble.h"
//#include "node.h"

#ifndef _STATEH_ 
#define _STATEH_

typedef struct State
{
	int player;
	int prev_player;
	int cur_board[17][13];
	struct Marble black[10];
	struct Marble red[10];
	struct Moves move;
	//int H;
	int game_result;
	struct State* copy_state;
	int fp;
	int b_range[4];
	int r_range[4];
} State;

/*
 * Purpose: create a copy of current state
 * Parameters: state - a pointer of State struct referencing the current game state
 * Return value: a pointer of State struct as root node
 */
State* copyState (State *state);

/*
 * Purpose: check if the current player won the simulation game
 * Parameters: state - a pointer of State struct referencing the current game state
 				player - an integer variable indicating the current player
 * Return value: an integer variable indicating the game result
 */
int result (State *state, int player);

/*
 * Purpose: check available moves of each marble in current state
 * Parameters: state - a pointer of State struct referencing the current game state
 			move - an array of struct Moves,
 			count - a pointer of int variable indicating total available moves
 * Return value: none
 */
void getMoves (State *state, struct Queue** moves);

/*
 * Purpose: check available moves of each marble in current state
 * Parameters: state - a pointer of State struct referencing the current game state
 			move - a pointer of Moves struct referencing the selected move
 * Return value: none
 */
void performMove (State *state, struct Moves* move);

/*
 * Purpose: check if either player wins the simulation game
 * Parameters: state - a pointer of State struct referencing the current game state
 * Return value: an int variable indicating the winner
 */
int endGameSimu (State *state);

/*
 * Purpose: update the range flag based on the position of all marbles
 * Parameters: state - a pointer of State struct referencing the current game state
 * Return value: none
 */
void updateRangeFlag (State *state);

/*
 * Purpose: print the game board in current game state
 * Parameters: state - a pointer of State struct referencing the current game state
 * Return value: none
 */
void printCurBoard (State *state);

#endif