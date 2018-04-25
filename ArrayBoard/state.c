#include "state.h"

//the offset index for each row
const int rowId[17] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};

State* copyState (State *state)
{
	State *new_state = (State*) malloc(sizeof (State));
	int i, j;
    
    //copy all the information from the current state
    new_state -> player = 3 - state->player;
	new_state->prev_player = state->player;
	for (i = 0; i < 10; i++) {
		new_state->black[i] = state->black[i];
		new_state->red[i] = state->red[i];
	}
	for (i = 0; i < 17; i++) {
		for (j = 0; j < 13; j++)
			new_state->cur_board[i][j] = state->cur_board[i][j];
	}
	new_state->game_result = state->game_result;

	return new_state;
}

int result (State *state, int player)
{
	//if the winner is the current player, return 1; otherwise, return 0
	if (state->player == player)
		return 1;
	else
		return 0;
}

void getMoves (State *state, struct Queue** moves)
{
	int i;

	//go through all marbles and check for available moves for the current player in the current game state
	for (i = 0; i < 10; i++) {
		if (state->player == 1)
			checkMoves(&(state->black[i]), moves, state->cur_board, rowId, state->player, state->b_range);
		else
			checkMoves(&(state->red[i]), moves, state->cur_board, rowId, state->player, state->r_range);
	}
}

void performMove (State *state, struct Moves* move)
{
	int from_row = move->from[0];
	int from_col = move->from[1];
	int to_row = move->to[0];
	int to_col = move->to[1];
	float value = move->value;

	int i = 0;
	int done = 0;

	//update the information for the marble which performed the current move
	while (i < 10 && (!done)) {
		if (state->black[i].position[0] == from_row && state->black[i].position[1] == from_col) {
			state->black[i].position[0] = to_row;
			state->black[i].position[1] = to_col;
			state->black[i].last_move.from[0] = from_row;
			state->black[i].last_move.from[1] = from_col;
			state->black[i].last_move.to[0] = to_row;
			state->black[i].last_move.to[1] = to_col;
			state->black[i].last_move.value = value;
			state->black[i].move_total += 1;
			state->move.from[0] = from_row;
			state->move.from[1] = from_col;
			state->move.to[0] = to_row;
			state->move.to[1] = to_col;
			state->move.value = value;
			state->cur_board[to_row][to_col] = state->cur_board[from_row][from_col];
			state->cur_board[from_row][from_col] = 0;
			done = 1;
		} else if (state->red[i].position[0] == from_row && state->red[i].position[1] == from_col) {
			state->red[i].position[0] = to_row;
			state->red[i].position[1] = to_col;
			state->red[i].last_move.from[0] = from_row;
			state->red[i].last_move.from[1] = from_col;
			state->red[i].last_move.to[0] = to_row;
			state->red[i].last_move.to[1] = to_col;
			state->red[i].last_move.value = value;
			state->red[i].move_total += 1;
			state->move.from[0] = from_row;
			state->move.from[1] = from_col;
			state->move.to[0] = to_row;
			state->move.to[1] = to_col;
			state->move.value = value;
			state->cur_board[to_row][to_col] = state->cur_board[from_row][from_col];
			state->cur_board[from_row][from_col] = 0;
			done = 1;
		}
		i++;
	}

	//update the surrounding positions for all marbles after each move
	for(i = 0; i < 10; i++){
		surroundingPosition(&(state->black[i]), state->cur_board, rowId);
		surroundingPosition(&(state->red[i]), state->cur_board, rowId);
	}

	//update range flags after each move
	updateRangeFlag(state);
}

int endGameSimu (State *state)
{
	//if the desired corner is fully occupied and at least one slot is filled with opponet's marble,
	//then opponent player wins. Then return the winner's number.
	if (state->cur_board[16][6] != 0 && state->cur_board[15][6] != 0 && state->cur_board[15][7] != 0 && state->cur_board[14][5] != \
		0 && state->cur_board[14][6] != 0 && state->cur_board[14][7] != 0 && state->cur_board[13][5] != 0 && state->cur_board[13][6] != \
		0 && state->cur_board[13][7] != 0 && state->cur_board[13][8] != 0) {
		if (state->cur_board[16][6] == 1 || state->cur_board[15][6] == 1 || state->cur_board[15][7] == 1 || state->cur_board[14][5] == \
			1 || state->cur_board[14][6] == 1 || state->cur_board[14][7] == 1 || state->cur_board[13][5] == 1 || state->cur_board[13][6] == \
			1 || state->cur_board[13][7] == 1 || state->cur_board[13][8] == 1) {
			return 1;
		}
	} else if (state->cur_board[0][6] != 0 && state->cur_board[1][6] != 0 && state->cur_board[1][7] != 0 && state->cur_board[2][5] != \
		0 && state->cur_board[2][6] != 0 && state->cur_board[2][7] != 0 && state->cur_board[3][5] != 0 && state->cur_board[3][6] != \
		0 && state->cur_board[3][7] != 0 && state->cur_board[3][8] != 0) {
		if (state->cur_board[0][6] == 2 || state->cur_board[1][6] == 2 || state->cur_board[1][7] == 2 || state->cur_board[2][5] == \
			2 || state->cur_board[2][6] == 2 || state->cur_board[2][7] == 2 || state->cur_board[3][5] == 2 || state->cur_board[3][6] == \
			2 || state->cur_board[3][7] == 2 || state->cur_board[3][8] == 2) {
			return 2;
		}
	}

	//if neither player wins, return 0
	return 0;
}

void updateRangeFlag (State *state)
{
	int b_max = state->black[0].position[0];
	int b_min = state->black[0].position[0];
	int b_left = state->black[0].position[1];
	int b_right = state->black[0].position[1];
	int r_max = state->red[0].position[0];
	int r_min = state->red[0].position[0];
	int r_left = state->red[0].position[1];
	int r_right = state->red[0].position[1];
	int i;

	//go through all marbles to check for the max and min range flags
	for (i = 0; i < 10; i++) {
		if (b_max < state->black[i].position[0])
			b_max = state->black[i].position[0];
		if (b_min > state->black[i].position[0])
			b_min = state->black[i].position[0];
		if (b_left > state->black[i].position[1])
			b_left = state->black[i].position[1];
		if (b_right < state->black[i].position[1])
			b_right = state->black[i].position[1];

		if (r_max < state->red[i].position[0])
			r_max = state->red[i].position[0];
		if (r_min > state->red[i].position[0])
			r_min = state->red[i].position[0];
		if (r_left > state->red[i].position[1])
			r_left = state->red[i].position[1];
		if (r_right < state->red[i].position[1])
			r_right = state->red[i].position[1];
	}

	//update the range flags for black marbles
	state->b_range[0] = b_max;
	state->b_range[1] = b_min;
	state->b_range[2] = b_left;
	state->b_range[3] = b_right;

	//update the range flags for red marbles
	state->r_range[0] = r_max;
	state->r_range[1] = r_min;
	state->r_range[2] = r_left;
	state->r_range[3] = r_right;
}

void printCurBoard (State *state)
{
	int i, j;
	for (i = 0; i < 17; i++) {
		if (i % 2 == 0) //add extra space in the begining of a even number row
			printf(" ");
		for (j = 0; j < 13; j++) {
			if (state->cur_board[i][j] == -1) //print space if the value of the specified position in the array is -1
				printf("   ");
			else //otherwise, print the value of that specified postion
				printf("  %d", state->cur_board[i][j]);
		}
		printf("\n");
	}
}
