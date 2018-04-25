#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <sys/timeb.h>
#include <unistd.h>
#include "node.h"
#include "marble.h"
#include "state.h"

#ifndef _MCTSH_
#define _MCTSH_

typedef struct MCTS_Tree {
	struct MCTS_Tree* parent;
	struct Queue* move_queue;
	struct Queue* children;
	struct Moves* move;
	int win_score;
	int visits;
	int player;
} MCTS_Tree;

/*
 * Purpose: using MCTS process to choose a favoured move and return it to the main program for action
 * Parameters: state - an pointer of State struct variables referencing the actual game state
 			duration - a constant intager indicating desired MCTS executing time
 * Return value: a pointer of Moves struct referencing the chosen move
 */
void MCTS (State* state, struct Moves* next_move, const int dur);

/*
 * Purpose: create a new MCTS_Tree struct and its root
 * Parameters: player - an int variable indicating current player
 			moveList - a Queue list of Moves struct variable
 			count - an int variable indicating number of moves in moveList array
 * Return value: a pointer of MCTS_Tree struct as root node
 */
MCTS_Tree* createTree (int new_player, struct Queue* moves);

/*
 * Purpose: create a new leaf of MCTS_Tree struct 
 * Parameters: player - an int variable indicating current player
 			moveList - a Queue list of Moves struct variable
 			count - an int variable indicating number of moves in moveList array
 			new_move - a pointer of Moves struct variable referencing the latest move
 			parent - a pointer of MCTS_Tree struct referencing the parent of this leaf node
 * Return value: a pointer of MCTS_Tree struct as new leaf node
 */
MCTS_Tree* createLeaf (int new_player, struct Queue* moves, struct Moves* newMove, MCTS_Tree* new_parent);

/*
 * Purpose: add a new leaf of the MCTS_Tree struct to the tree
 * Parameters: parent - a pointer of MCTS_Tree struct referencing the parent of this leaf node
 			cur_state - a pointer of State struct referencing the current game state
 * Return value: a pointer of MCTS_Tree struct as a leaf node
 */
MCTS_Tree* addLeaf (MCTS_Tree* parent, State* cur_state);

/*
 * Purpose: select the optimal child node for expansion
 * Parameters: cur_node - a pointer of MCTS_Tree struct referencing the current node
 			cur_state - a pointer of State struct referencing the current game state
 * Return value: none
 */
MCTS_Tree* selection(MCTS_Tree** cur_node, State* cur_state);

/*
 * Purpose: expand the child node by appending all possible states
 * Parameters: cur_node - a pointer of MCTS_Tree struct referencing the current node
 			cur_state - a pointer of State struct referencing the current game state
 * Return value: none
 */
void expansion (MCTS_Tree** cur_node, State* cur_state);

/*
 * Purpose: simulate the random game untill reach the end of the game
 * Parameters: cur_state - a pointer of State struct referencing the current game state
 * Return value: none
 */
int simulation (State* cur_state);

/*
 * Purpose: traverse back to the node to update the win score of all visited node
 * Parameters: result - an int variable indicating which player won the game
 			tree - a pointer of MCTS_Tree struct referencing the MCTS tree
 * Return value: none
 */
void backPropagation (MCTS_Tree** tree, int result);

/*
 * Purpose: destroy the tree struct and free up space
 * Parameters: tree - a pointer of MCTS_Tree struct referencing the MCTS tree
 * Return value: none
 */
void destroyTree (MCTS_Tree* tree);

/*
 * Purpose: find the "best" child node based on the result of UCT value calculation
 * Parameters: tree - a pointer of MCTS_Tree struct referencing the MCTS tree
 * Return value: a pointer of MCTS_Tree struct referencing the chosen node
 */
MCTS_Tree* findBestNode (MCTS_Tree* tree);

/*
 * Purpose: calculate the node value using UCT algorithm
 * Parameters: node - a pointer of MCTS_Tree struct referencing the node for calculation
 			r_visits - an int variable indicating the number of root visit
 * Return value: uct - a double variable indicating the node value
 */
double uctValue (MCTS_Tree* node, int r_visits);

#endif
