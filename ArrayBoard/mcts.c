#include "mcts.h"

void MCTS(State* state, struct Moves* next_move, const int dur)
{
	struct Queue* moves = createQueue();
	getMoves(state, &moves);
	if (state->prev_player != 1 && state->prev_player != 2) {
		printf("Error! Previous player = %d\n", state->prev_player);
	}

	MCTS_Tree* tree = createTree(state->player, moves);

	int search = 0;
	int elap = 0;

	//use millisecond as unit to check for time
	struct timeb begin, cur_time;
	ftime(&begin);

	while (elap < dur) {

		//point to the root of the tree and make a copy of the actual current game state
		MCTS_Tree* cur_node = tree;
		State* cur_state = copyState(state);

		//select the most promising node
		cur_node = selection(&cur_node, cur_state);

		//expand the most promising node
		expansion(&cur_node, cur_state);

		//play a random simulation game and check which player wins
		int player = simulation(cur_state);

		//get the game result based on the winner
		int game_result = result(state, player);

		//update the win score for all node in the chosen path based on the game result
		backPropagation(&cur_node, game_result);

		//check if the elapsed time exeeded the time limit
		ftime(&cur_time);
		elap = ((cur_time.time - begin.time) * (int)1000) + (cur_time.millitm - begin.millitm);

		if(cur_state != NULL)
			free(cur_state);

		search++;
	}

	printf("Elapsed Time: %d - Number of Search: %d\n", elap, search);

	//struct Queue* r_children = tree->children;
	Node* cur = tree->children->first;
	MCTS_Tree* max = (MCTS_Tree*) cur->data;
	cur = cur->next;
	MCTS_Tree* tmp;

	//go through children node and select the one with the largest win score
	while(cur) {
		tmp = (MCTS_Tree*) cur->data;
		if(tmp->win_score > max->win_score)
			max = tmp;
		cur = cur->next;
	}

	//record the information of the selected move
	next_move->from[0] = max->move->from[0];
	next_move->from[1] = max->move->from[1];
	next_move->to[0] = max->move->to[0];
	next_move->to[1] = max->move->to[1];
	next_move->value = max->move->value;

	//destroy the current MCTS tree and free up all memory allocated
	destroyTree(tree);
}

MCTS_Tree* createTree(int player, struct Queue* moves)
{
	return createLeaf(player, moves, NULL, NULL); //call createLeaf() function to set the root node
}

MCTS_Tree* createLeaf(int player, struct Queue* moves, struct Moves* new_move, MCTS_Tree* parent)
{
	MCTS_Tree* node = (MCTS_Tree*)malloc(sizeof(MCTS_Tree));

	node->parent = parent; //set the previous node as parent
	node->move_queue = moves; //add all avaliable moves in current game state
	node->children = createQueue(); //initialize a queue of children nodes
	if (new_move != NULL) { //copy the information of the newly performed move
		node->move = (struct Moves*)malloc(sizeof(struct Moves));
		node->move->from[0] = new_move->from[0];
		node->move->from[1] = new_move->from[1];
		node->move->to[0] = new_move->to[0];
		node->move->to[1] = new_move->to[1];
		node->move->value = new_move->value;
	} else
		node->move = NULL;

	node->win_score = 0; //initialize the win score to 0
	node->visits = 0; //initialize the number of node visit to 0
	node->player = player; //set the player as the player in the current game state

	return node;
}

MCTS_Tree* addLeaf(MCTS_Tree* parent, State* cur_state)
{
	int new_player = 3 - parent->player;
	struct Queue* r_moves = createQueue();
	struct Moves* c_move = (struct Moves*)malloc(sizeof(struct Moves));

	selectRandom(parent->move_queue, c_move); //randomly select a move with a preference of higher value moves
	performMove(cur_state, c_move); //perform the selected move and update game state
	getMoves(cur_state, &r_moves); //check moves for the new game state

	MCTS_Tree* child = createLeaf(new_player, r_moves, c_move, parent); //create a new leaf node
	enqueue(&(parent->children),(void*)child); //add this new leaf node to the tree

	free(c_move);
    return child; //return this new created leaf node
}

MCTS_Tree* selection(MCTS_Tree** cur_node, State* cur_state)
{
	MCTS_Tree* node = *cur_node;

	//select the best node using UCT algorithm
	while(node->children->count > 4) {
		node = findBestNode(node);
		performMove(cur_state, node->move);
	}

	//return the most promising node
	return node;
}

void expansion(MCTS_Tree** cur_node, State* cur_state)
{
	// expand the node and add to the MCTS tree
	if ((*cur_node)->move_queue) {
		*cur_node = addLeaf(*cur_node, cur_state);
	}
}

int simulation(State* cur_state)
{
    //play a simulated game by performing moves untill either player wins
	while(endGameSimu(cur_state) == 0) {
		struct Queue* moves = createQueue();
		getMoves(cur_state, &moves);
		struct Moves* c_move = (struct Moves*)malloc(sizeof(struct Moves));
		selectRandom(moves, c_move);
		performMove(cur_state, c_move);
		cur_state->player = cur_state->prev_player;
    	cur_state->prev_player = 3 - cur_state->player;

    	//free all the memory allocated in each simulation to prevent memory leak
		free(c_move);
		destroyNode(moves);
		destroyQueue(moves);
	}

	//return simulation game result
	return endGameSimu(cur_state);
}

void backPropagation(MCTS_Tree** tree, int result)
{
	MCTS_Tree* node = *tree;

	//traverse back from leaf node to root node and update their win values
	while (node) {
		node->visits += 1;
		node->win_score += result;
		node = node->parent;
	}
}

void destroyTree(MCTS_Tree* tree)
{
	if (tree == NULL)
		return;

	MCTS_Tree* node;

	//recursively destroy all child nodes and free up the space
	while ((node = dequeue(tree->children)) != NULL)
		destroyTree(node);

	//free all memory allocated in Moves struct and destroy the queue containing move pointers
	destroyNode(tree->move_queue);
	destroyQueue(tree->move_queue);

	//destroy the queue containing all children pointers
	destroyQueue(tree->children);
	
	//free up the root of the tree
	if (tree != NULL) {
		if (tree->move != NULL)
			free(tree->move);
		free(tree);
	}
}

MCTS_Tree* findBestNode(MCTS_Tree* tree)
{
	int r_visits = tree->visits; //total number of root visits
	Node* cur = tree->children->first;
	MCTS_Tree* best = cur->data;
	Node* tmp;
	double cur_value, max;

	//initialize the maximum UCT value to the first child node
	max = uctValue(best, r_visits);
	cur = cur->next;

	//go through all children to find the node with maximum UCT value
	while(cur) {
		tmp = cur->next;
		cur_value = uctValue(cur->data, r_visits);
		if (cur_value > max) {
			best = cur->data;
			max = cur_value;
		}
		cur = tmp;
	}

	return best;
}

double uctValue(MCTS_Tree* node, int r_visits)
{
	double constant = sqrt((double)2); //use sqaure of 2 as the constant
	double uct;

	if(node->visits == 0) //if the node has never been visited, set the UCT value to 0
		uct = 0;
	else //otherwise, calculate the value using the UCT algorithm
		uct = (node->win_score / (double)node->visits) + constant * sqrt(log((double)r_visits) / node->visits);

	return uct;
}
