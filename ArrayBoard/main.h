#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "marble.h"
#include "state.h"
#include "mcts.h"
#include "node.h"

#ifndef _MAINH_
#define _MAINH_

/*
 * Purpose: generate move based on MCTS agent
 * Parameters: state - an pointer of State struct variables cotaining game state info
 * Return value: none
 */
void mctsAgent (State *state);

/*
 * Purpose: generate random move with the consideration of move evaluation values
 * Parameters: state - an pointer of State struct variables cotaining game state info
 * Return value: none
 */
void weightedMoveAgent (State *state);

/*
 * Purpose: handle SIGINT terminate signal and print exit message
 * Parameters: arg - an integer variable
 * Return value: none
 */
void handle (int arg);

/*
 * Purpose: print total execution time 
 * Parameters: begin - a time variable indicating start time,
 *			end - a time variable indicating finish time
 *			fp - an integer variable indicating the write out path
 * Return value: a double variable representing the elapse time
 */
double executionTime (clock_t begin, clock_t end, int fp);

/*
 * Purpose: print the Chinese Checkers board with current game status
 * Parameters: fp - an integer variable indicating the write out path
 * Return value: none
 */
void printBoard (int fp);

/*
 * Purpose: check if either player wins the game
 * Parameters: none
 * Return value: an int variable indicating the winner
 */
int endGame ();

#endif
