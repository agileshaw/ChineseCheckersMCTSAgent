#include "marble.h"

//the static position value for player 1 (black marbles)
int const eval1[17][13] = {{-1,  -1,  -1,  -1,  -1,  -1,  0,  -1,  -1,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  -1,  5,  5,  -1,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  10,  10,  10,  -1,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  15,  15,  15,  15,  -1,  -1,  -1,  -1},
							{15,  16,  20,  22,  25,  25,  25,  25,  25,  22,  20,  16,  15},
							{-1,  18,  26,  30,  35,  35,  35,  35,  35,  30,  26,  18,  18},
							{-1,  22,  33,  38,  45,  45,  45,  45,  45,  38,  33,  22,  -1},
							{-1,  -1,  40,  47,  55,  55,  55,  55,  55,  47,  40,  35,  -1},
							{-1,  -1,  48,  56,  65,  65,  65,  65,  65,  56,  48,  -1,  -1},
							{-1,  -1,  58,  67,  75,  75,  75,  75,  75,  67,  58,  44,  -1},
							{-1,  52,  65,  78,  85,  85,  85,  85,  85,  78,  65,  52,  -1},
							{-1,  62,  72,  90,  95,  95,  95,  95,  95,  90,  72,  62,  62},
							{70,  72,  80,  98,  105,  105,  105,  105,  105,  98,  80, 72,  70},
							{-1,  -1,  -1,  -1,  -1,  115,  115,  115,  115,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  117,  117,  117,  -1,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  -1,  119,  119,  -1,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  -1,  120,  -1,  -1,  -1,  -1,  -1,  -1}};

//the static position value for player 2 (red marbles)
int const eval2[17][13] = {{-1,  -1,  -1,  -1,  -1,  -1,  120,  -1,  -1,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  -1,  119,  119,  -1,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  117,  117,  117,  -1,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  115,  115,  115,  115,  -1,  -1,  -1,  -1},
							{70,  72,  80,  98,  105,  105,  105,  105,  105,  98,  80, 72,  70},
							{-1,  62,  72,  90,  95,  95,  95,  95,  95,  90,  72,  62,  62},
							{-1,  52,  65,  78,  85,  85,  85,  85,  85,  78,  65,  52,  -1},
							{-1,  -1,  58,  67,  75,  75,  75,  75,  75,  67,  58,  44,  -1},
							{-1,  -1,  48,  56,  65,  65,  65,  65,  65,  56,  48,  -1,  -1},
							{-1,  -1,  40,  47,  55,  55,  55,  55,  55,  47,  40,  35,  -1},
							{-1,  22,  33,  38,  45,  45,  45,  45,  45,  38,  33,  22,  -1},
							{-1,  18,  26,  30,  35,  35,  35,  35,  35,  30,  26,  18,  18},
							{15,  16,  20,  22,  25,  25,  25,  25,  25,  22,  20,  16,  15},
							{-1,  -1,  -1,  -1,  -1,  15,  15,  15,  15,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  10,  10,  10,  -1,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  -1,  5,  5,  -1,  -1,  -1,  -1,  -1},
							{-1,  -1,  -1,  -1,  -1,  -1,  0,  -1,  -1,  -1,  -1,  -1,  -1}};


void initialBlack (struct Marble *black, int index)
{
	black->move_total = 0;

	//initialize the starting position of each black marble based on their index
	switch(index) {
		case 0:
			black->position[0] = 0;
			black->position[1] = 6;
			break;
		case 1:
			black->position[0] = 1;
			black->position[1] = 6;
			break;
		case 2:
			black->position[0] = 1;
			black->position[1] = 7;
			break;
		case 3:
			black->position[0] = 2;
			black->position[1] = 5;
			break;
		case 4:
			black->position[0] = 2;
			black->position[1] = 6;
			break;
		case 5:
			black->position[0] = 2;
			black->position[1] = 7;
			break;
		case 6:
			black->position[0] = 3;
			black->position[1] = 5;
			break;
		case 7:
			black->position[0] = 3;
			black->position[1] = 6;
			break;
		case 8:
			black->position[0] = 3;
			black->position[1] = 7;
			break;
		case 9:
			black->position[0] = 3;
			black->position[1] = 8;
			break;
	}
}

void initialRed (struct Marble *red, int index)
{
	red->move_total = 0;

	//initialize the starting position of each red marble based on their index
	switch(index) {
		case 0:
			red->position[0] = 13;
			red->position[1] = 5;
			break;
		case 1:
			red->position[0] = 13;
			red->position[1] = 6;
			break;
		case 2:
			red->position[0] = 13;
			red->position[1] = 7;
			break;
		case 3:
			red->position[0] = 13;
			red->position[1] = 8;
			break;
		case 4:
			red->position[0] = 14;
			red->position[1] = 5;
			break;
		case 5:
			red->position[0] = 14;
			red->position[1] = 6;
			break;
		case 6:
			red->position[0] = 14;
			red->position[1] = 7;
			break;
		case 7:
			red->position[0] = 15;
			red->position[1] = 6;
			break;
		case 8:
			red->position[0] = 15;
			red->position[1] = 7;
			break;
		case 9:
			red->position[0] = 16;
			red->position[1] = 6;
			break;
	}
}

void surroundingPosition (struct Marble *marble, int board[17][13], const int rowIndex[17])
{	
	int row = marble->position[0];
	int col = marble->position[1];
	int check = rowIndex[row];

	//check for special cases to prevent reaching out of array's range
	if(row == 0) {
		marble->surrounding[0] = -1;
		marble->surrounding[1] = -1;
		marble->surrounding[2] = -1;
		marble->surrounding[3] = board[1][7];
		marble->surrounding[4] = board[1][6];
		marble->surrounding[5] = -1;
	} else if(row == 16){
		marble->surrounding[0] = board[15][6];
		marble->surrounding[1] = board[15][7];
		marble->surrounding[2] = -1;
		marble->surrounding[3] = -1;
		marble->surrounding[4] = -1;
		marble->surrounding[5] = -1;
	} else if (col == 0) {
		marble->surrounding[0] = -1;
		marble->surrounding[1] = board[row-1][col-check+1];
		marble->surrounding[2] = board[row][col+1];
		marble->surrounding[3] = board[row+1][col-check+1];
		marble->surrounding[4] = -1;
		marble->surrounding[5] = -1;
	} else if (col == 12) {
		marble->surrounding[0] = board[row-1][col-check];
		marble->surrounding[1] = -1;
		marble->surrounding[2] = -1;
		marble->surrounding[3] = -1;
		marble->surrounding[4] = board[row+1][col-check];
		marble->surrounding[5] = board[row][col-1];
	} else { //if it is not a special case, then check all six surrounding positions and update values
		marble->surrounding[0] = board[row-1][col-check];
		marble->surrounding[1] = board[row-1][col-check+1];
		marble->surrounding[2] = board[row][col+1];
		marble->surrounding[3] = board[row+1][col-check+1];
		marble->surrounding[4] = board[row+1][col-check];
		marble->surrounding[5] = board[row][col-1];
	}
}

void checkMoves (struct Marble *marble, struct Queue** moves, int board[17][13], const int rowIndex[17], int player, int range[])
{
	int i, avoid;
	int tmp_row, tmp_col, row, col;
	bool suc_jump = false;

	row = marble->position[0];
	col = marble->position[1];

	for (i = 0; i < 6; i++) {
		if (marble->surrounding[i] == -1) //if the checked position is not a valid game slot, skip
			continue;
		else if (marble->surrounding[i] == 0) { //if the checked position is an valid empty slot, make adjacent move
			struct Moves* new_move = (struct Moves*)malloc(sizeof(struct Moves));
			
			//perform an adjacent move
			adjacentMove(row, col, new_move, board, rowIndex, i);
			tmp_row = new_move->to[0];
			tmp_col = new_move->to[1];

			//calculate the value of this move
			if (player == 1)
				moveValueBlack(new_move, row, col, tmp_row, tmp_col, range);
			else
				moveValueRed(new_move, row, col, tmp_row, tmp_col, range);

			//add this move to the queue struct
			enqueue(moves, (void *)new_move);
		} else { //if the checked postion is occupied, check if it can jump over
			struct Moves* new_move = (struct Moves*)malloc(sizeof(struct Moves));
			
			//check if a jump move is possible
			suc_jump = jumpMove(row, col, new_move, board, i);
			
			if (suc_jump) {
				new_move->from[0] = row;
				new_move->from[1] = col;
				tmp_row = new_move->to[0];
				tmp_col = new_move->to[1];

				//calculate the value of the move
				if (player == 1)
					moveValueBlack(new_move, row, col, tmp_row, tmp_col, range);
				else
					moveValueRed(new_move, row, col, tmp_row, tmp_col, range);

				//add this move to the queue struct
				enqueue(moves, (void *)new_move);
				
				//avoid jumping back to the original position
				avoid = (i + 3) % 6;
				
				//check if sequential jump is possible
				sequentialJump(row, col, tmp_row, tmp_col, avoid, moves, board, rowIndex, player, range);
			} else //if the jump attempt is not successful, free the Moves struct
				free(new_move);
		}
	}
}

void adjacentMove (int row, int col, struct Moves *move, int board[17][13], const int rowIndex[17], int index)
{
	int check = rowIndex[row];
	move->from[0] = row;
	move->from[1] = col;

	//perform an adjacent move base on the direction index
	switch(index){
		case 0:
			move->to[0] = row-1;
			move->to[1] = col-check;
			break;
		case 1:
			move->to[0] = row-1;
			move->to[1] = col-check+1;
			break;
		case 2:
			move->to[0] = row;
			move->to[1] = col+1;
			break;
		case 3:
			move->to[0] = row+1;
			move->to[1] = col+1-check;
			break;
		case 4:
			move->to[0] = row+1;
			move->to[1] = col-check;
			break;
		case 5:
			move->to[0] = row;
			move->to[1] = col-1;
			break;
	}
}

bool jumpMove (int row, int col, struct Moves *move, int board[17][13], int index)
{
	//check for special cases to prevent jump out of the range of the game board array
	//return true if a jump is successfully performed, otherwise return false
	switch(index){
		case 0:
			if (row < 2 || col < 1) {
				return false;
			}
			if(board[row-2][col-1] == 0){
				move->to[0] = row-2;
				move->to[1] = col-1;
				return true;
			} 
			break;
		case 1:
			if (row < 2 || col > 11) {
				return false;
			}
			if(board[row-2][col+1] == 0){
				move->to[0] = row-2;
				move->to[1] = col+1;
				return true;
			} 
			break;
		case 2:
			if (col > 10) {
				return false;
			}
			if(board[row][col+2] == 0){
				move->to[0] = row;
				move->to[1] = col+2;
				return true;
			} 
			break;
		case 3:
			if (row > 14 || col > 11) {
				return false;
			}
			if(board[row+2][col+1] == 0){
				move->to[0] = row+2;
				move->to[1] = col+1;
				return true;
			} 
			break;
		case 4:
			if (row > 14 || col < 1) {
				return false;
			}
			if(board[row+2][col-1] == 0){
				move->to[0] = row+2;
				move->to[1] = col-1;
				return true;
			} 
			break;
		case 5:
			if (col < 2) {
				return false;
			}
			if(board[row][col-2] == 0) {
				move->to[0] = row;
				move->to[1] = col-2;
				return true;
			} 
			break;
	}
	return false;
}

void sequentialJump (int ori_row, int ori_col, int tmp_row, int tmp_col, int avoid, struct Queue** moves, int board[17][13], const int rowIndex[17], int player, int range[]) 
{
	bool jump_check = false, exist = false;
	int i, k;
	struct Marble marble;
	struct Moves* data;
	
	marble.position[0] = tmp_row;
	marble.position[1] = tmp_col;
	surroundingPosition(&marble, board, rowIndex);
	for (i = 0; i < 6; i++) {
		if (i == avoid) { //avoid the direction where the marble jumped from
			continue;
		}
		if (marble.surrounding[i] == 1) { //if the checked position is occupied, check if check if it can jump over
			struct Moves* new_move = (struct Moves*)malloc(sizeof(struct Moves));
			
			//check if a jump move is possible
			jump_check = jumpMove(tmp_row, tmp_col, new_move, board, i);
			
			if (jump_check) {
				tmp_row = new_move->to[0];
				tmp_col = new_move->to[1];

				Node* tmp = (*moves)->first;
				
				//go through the queue and make sure no duplicate move exists
				while (tmp != NULL) {
					data = (struct Moves*)(tmp->data);
					if(data->from[0] == ori_row && data->from[1] == ori_col){
						if (data->to[0] == tmp_row && data->to[1] == tmp_col) {
							exist = true;
						}
					}
					tmp = tmp->next;
				}
				if (!exist) { //if this is a new move, add to the queue
					new_move->from[0] = ori_row;
					new_move->from[1] = ori_col;
					
					//calculate the value of this move
					if (player == 1)
						moveValueBlack(new_move, ori_row, ori_col, tmp_row, tmp_col, range);
					else
						moveValueRed(new_move, ori_row, ori_col, tmp_row, tmp_col, range);
					
					//add this move to the queue struct
					enqueue(moves, (void *)new_move);
					
					//avoid jumping back to the original position
					k = (i + 3) % 6;

					//recursively check all the available sequential jump
					sequentialJump(ori_row, ori_col, tmp_row, tmp_col, k, moves, board, rowIndex, player, range);
				} else { //if this move already existed in the queue, free the Moves struct
					free(new_move);
					continue;
				}
			} else //if the jump attempt is not successful, free the Moves struct
				free(new_move);
		}
	}
}

void moveValueBlack(struct Moves* move, int row, int col, int tmp_row, int tmp_col, int range[])
{
	float val = 0;

	//use the range flag to add cluster factor to the move value
	int row_distance = abs(tmp_row - range[0]) + abs(tmp_row - range[1]);
	int col_distance = abs(tmp_row - range[2]) + abs(tmp_row - range[3]);
	if (row_distance * col_distance > 25) {
		val = 0.001 * row_distance * col_distance;
	}
	move->value = (float)(eval1[tmp_row][tmp_col] - eval1[row][col]) - val;
}

void moveValueRed(struct Moves* move, int row, int col, int tmp_row, int tmp_col, int range[])
{
	float val = 0;

	//use the range flag to check how spread out are the marbles
	int row_distance = abs(tmp_row - range[0]) + abs(tmp_row - range[1]);
	int col_distance = abs(tmp_row - range[2]) + abs(tmp_row - range[3]);

	//add cluster factor to the move value if the marbles are too spread out
	if (row_distance * col_distance > 25)
		val = 0.001 * row_distance * col_distance;

	//calculate the value of move by considering both static position value and cluster factor
	move->value = (float)(eval2[tmp_row][tmp_col] - eval2[row][col]) - val;
}

void selectRandom(struct Queue* moves, struct Moves* selected)
{
	int i, k;
	float random, val;

	//if the queue is empty, escape from this function
	if (moves->first == NULL)
		return;

	Node* tmp = moves->first;
	Node* prev = tmp;
	struct Moves* data = (struct Moves*)(tmp->data);

	//if the queue contains only one node, select this move
	if (moves->first == moves->last) {
		selected->from[0] = data->from[0];
		selected->from[1] = data->from[1];
		selected->to[0] = data->to[0];
		selected->to[1] = data->to[1];
		selected->value = data->value;
		return;
	}


	val = data->value;
	while (tmp->next) { //go through the whole queue to find the largest move value
		tmp = tmp->next;
        data = (struct Moves*)(tmp->data);
		if (val < data->value)
			val = data->value;
	}

    tmp = moves->first;
    srand(seedCurTime()); //seed the random function with current time

	if (val > 0) { //if there are positive moves, select a move with a value higher than a randomly chosen number in the range
		random = (float)rand() / (float)(RAND_MAX/val);
		while (data->value < random && tmp->next != NULL) {
			prev = tmp;
			tmp = tmp->next;
			data = (struct Moves*)(prev->data);
		}
	} else { //if no positive move is available, then random select one
		k = rand() % (moves->count);
		for (i = 0; i < k; i++) {
			if (tmp->next)
				tmp = tmp->next;
		}
		data = (struct Moves*)(tmp->data);
	}

	//record the information of the selected move
	selected->from[0] = data->from[0];
	selected->from[1] = data->from[1];
	selected->to[0] = data->to[0];
	selected->to[1] = data->to[1];
	selected->value = data->value;

}

unsigned seedCurTime()
{
	unsigned seed;
	time_t cur_time;
	unsigned char *tmp;
	size_t i;

	//initialization
	seed = 0;
	cur_time = time(0);
	tmp = (unsigned char *)&cur_time;

	//go through the range between 0 and current time to get a random seed
	for (i = 0; i < sizeof cur_time; i++)
		seed = seed * (UCHAR_MAX + 2U) + tmp[i];

	return seed;
}
