#include "main.h" 

//define initial board, -1 representing null position, 0 representing empty slots,
//1 and 2 representing two players
int board[17][13] = {{-1,  -1,  -1,  -1,  -1,  -1,  1,  -1,  -1,  -1,  -1,  -1,  -1},
					{-1,  -1,  -1,  -1,  -1,  -1,  1,  1,  -1,  -1,  -1,  -1,  -1},
					{-1,  -1,  -1,  -1,  -1,  1,  1,  1,  -1,  -1,  -1,  -1,  -1},
					{-1,  -1,  -1,  -1,  -1,  1,  1,  1,  1,  -1,  -1,  -1,  -1},
					{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
					{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
					{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  -1},
					{-1,  -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  -1},
					{-1,  -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  -1,  -1},
					{-1,  -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  -1},
					{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  -1},
					{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
					{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
					{-1,  -1,  -1,  -1,  -1,  2,  2,  2,  2,  -1,  -1,  -1,  -1},
					{-1,  -1,  -1,  -1,  -1,  2,  2,  2,  -1,  -1,  -1,  -1,  -1},
					{-1,  -1,  -1,  -1,  -1,  -1,  2,  2,  -1,  -1,  -1,  -1,  -1},
					{-1,  -1,  -1,  -1,  -1,  -1,  2,  -1,  -1,  -1,  -1,  -1,  -1}};

//the offset index for each row
const int rowIndex[17] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};

//set global signal flag variable
int sig_flag;

int main (int argc, char *argv[])
{
	int eg_check = endGame();
	int i, j, opt, move_count = 1;
    char *fn, *buf;
	clock_t begin, end;

	//struct contains information for the current game state
	State state;

	struct sigaction siga;
	siga.sa_handler = &handle; //handle exit signal
	siga.sa_flags = SIGINT;
	sigemptyset(&siga.sa_mask);
	if (sigaction(SIGINT, &siga, 0) == -1) { //check signal error
		perror("Sigaction Error!");
		sig_flag = 1;
	}

	//if user input a filename using "-v" flag, then print the result to that file
	state.fp = 0;
	while ((opt = getopt(argc, argv, "v:")) != -1) {
		switch (opt) {
		case 'v':
			fn = optarg;
			state.fp = open(fn, O_WRONLY | O_APPEND | O_CREAT, 0666);
			if (state.fp == -1) {
				write(STDOUT_FILENO, "Open file error!\n", 18);
				state.fp = 0;
			}
			break;
		case '?':
			write(STDOUT_FILENO, "Usage: ./game [-v filename]\n", 40);
			return 0;
		}
	}

	begin = clock();
	buf = (char *)malloc(4096);

	//initialize the marbles, the game board and the game state for both players
	for (i = 0; i < 10; i++) {
		initialBlack(&(state.black[i]), i);
		surroundingPosition(&(state.black[i]), board, rowIndex);
		initialRed(&(state.red[i]), i);
		surroundingPosition(&(state.red[i]), board, rowIndex);
	}
	updateRangeFlag(&state);
	for (i = 0; i < 17; i++) {
		for (j = 0; j < 13; j++)
			state.cur_board[i][j] = board[i][j];
	}
	state.player = 1;
	state.prev_player = 3 - state.player;
	
	//each player perform one move on its turn and repeatly switch turns untill 
	//an end game state is reached
	while (sig_flag != 1 && eg_check == 0) {
		sprintf(buf, "Move number: %d Current player: %d\n", move_count, state.player);
		write(state.fp, buf, strnlen(buf, 4096));
		
		if (state.player == 1) //player 1 uses MCTS AI agent to make moves
			mctsAgent(&state);
		else
			weightedMoveAgent(&state); //player 2 uses weighted random agent to make moves

		//update the surrounding slots occupation status for each marble
		for(i = 0; i < 10; i++){ 
			surroundingPosition(&(state.black[i]), board, rowIndex);
			surroundingPosition(&(state.red[i]), board, rowIndex);
		}
		
		//alternate turns for players
		state.prev_player = state.player;
		state.player = 3 - state.player;

		updateRangeFlag(&state);
 		printBoard(state.fp);	
		eg_check = endGame(); // check if either player wins the game after each turn
		move_count++;
		
		memset(buf, 0, 4096);
	}

	//print the game board the winner information
	printBoard(0);
	if (eg_check == 1 || eg_check == 2) {
		sprintf(buf, "Congratulations! Player %d wins the game!\n", eg_check);
		write(state.fp, buf, strnlen(buf, 4096));
	}

	free(buf);
	end = clock();
	executionTime(begin, end, 0); //print the total game time

	return 0;
}

void mctsAgent (State *state)
{	
	//construct a Moves struct and call MCTS agent to find the "best" move
	struct Moves* move = (struct Moves*)malloc(sizeof(struct Moves));
	MCTS(state, move, 10000);

	//record the information in the Moves struct
	int from_row = move->from[0];
	int from_col = move->from[1];
	int to_row = move->to[0];
	int to_col = move->to[1];

	//check for errors
	if(from_col > 12 || to_col > 12 || from_col < 0 || to_col < 0 || from_row > 16 || to_row > 16 || from_row < 0 || to_row < 0){
		printf("Something is wrong here!\n");
		printf("Moves: From (%d %d) to (%d %d)\n", from_row, from_col, to_row, to_col);
		printBoard(state->fp);
		exit(1);
	}

	//perform the selected move and update the game board
	performMove(state, move);	
	board[to_row][to_col] = board[from_row][from_col];
	board[from_row][from_col] = 0;

	free(move);
}

void weightedMoveAgent (State *state)
{
	int i;
	struct Queue* moves = createQueue(); //constrct a queue struct containing Moves struct pointers

	//go through all marbles and check for available moves for the current player in the current game state
	for (i = 0; i < 10; i++) {
		if (state->player == 1)
			checkMoves(&(state->black[i]), &moves, board, rowIndex, state->player, state->b_range);
		else
			checkMoves(&(state->red[i]), &moves, board, rowIndex, state->player, state->r_range);
	}

	//construct a Moves struct and randomly select a move with a preference of higher value moves
	struct Moves* selected = (struct Moves*)malloc(sizeof(struct Moves));
	selectRandom(moves, selected);
	
	//record the information in the Moves struct
	int from_row = selected->from[0];
	int from_col = selected->from[1];
	int to_row = selected->to[0];
	int to_col = selected->to[1];

	//check for errors
	if(from_col > 12 || to_col > 12 || from_col < 0 || to_col < 0 || from_row > 16 || to_row > 16 || from_row < 0 || to_row < 0){
		printf("Something is wrong here!\n");
		printf("Moves: From (%d %d) to (%d %d)\n", from_row, from_col, to_row, to_col);
		printBoard(state->fp);
		exit(1);
	}

	//perform the selected move and update the game board
	performMove(state, selected);
	board[to_row][to_col] = board[from_row][from_col];
	board[from_row][from_col] = 0;
	
	//free all the memory allocated to prevent memory leak
	free(selected);
	destroyNode(moves);
	destroyQueue(moves);
}

void handle (int arg)
{
	if (arg == SIGINT) { //if SIGINT signal received, update flag and print message
		sig_flag = 1;
		printf("Successfully Exit!\n");
	}
}

double executionTime (clock_t begin, clock_t end, int fp)
{
	double time_elapsed;
	int hr, min;
	float sec;
	char *buf;

	//calculate time in the unit of seconds
	time_elapsed = ((double) (end - begin)) / CLOCKS_PER_SEC;

	//format time for clearer display
	hr = time_elapsed / 3600;
	min = (time_elapsed - hr * 3600) / 60;
	sec = time_elapsed - hr * 3600 - min * 60;

	//print the time
	buf = (char *)malloc(4096);
	sprintf(buf, "Total game time: %d hours, %d minuetes and %f seconds.\n", hr, min, sec);
	write(fp, buf, strnlen(buf, 4096));
	free(buf);

	return time_elapsed;
}

void printBoard (int fp)
{
	int i, j;
	char *buf;

	buf = (char *)malloc(4096);

	for (i = 0; i < 17; i++) {
		if (i % 2 == 0) { //add extra space in the begining of a even number row
			memset(buf, 0, 4096);
			sprintf(buf, " ");
			write(fp, buf, strnlen(buf, 4096));
		}
		for (j = 0; j < 13; j++) {
			if (board[i][j] == -1) { //print space if the value of the specified position in the array is -1
				memset(buf, 0, 4096);
				sprintf(buf, "   ");
				write(fp, buf, strnlen(buf, 4096));
			} else { //otherwise, print the value of that specified postion
				memset(buf, 0, 4096);
				sprintf(buf, "  %d", board[i][j]);
				write(fp, buf, strnlen(buf, 4096));
			}
		}
		sprintf(buf, "\n");
		write(fp, buf, strnlen(buf, 4096));
	}

    free(buf);
}

int endGame ()
{
	//if the desired corner is fully occupied and at least one slot is filled with opponet's marble,
	//then opponent player wins. Then return the winner's number.
	if (board[16][6] != 0 && board[15][6] != 0 && board[15][7] != 0 && board[14][5] != \
		0 && board[14][6] != 0 && board[14][7] != 0 && board[13][5] != 0 && board[13][6] != \
		0 && board[13][7] != 0 && board[13][8] != 0) {
		if (board[16][6] == 1 || board[15][6] == 1 || board[15][7] == 1 || board[14][5] == \
			1 || board[14][6] == 1 || board[14][7] == 1 || board[13][5] == 1 || board[13][6] == \
			1 || board[13][7] == 1 || board[13][8] == 1) {
			return 1;
		}
	} else if (board[0][6] != 0 && board[1][6] != 0 && board[1][7] != 0 && board[2][5] != \
		0 && board[2][6] != 0 && board[2][7] != 0 && board[3][5] != 0 && board[3][6] != \
		0 && board[3][7] != 0 && board[3][8] != 0) {
		if (board[0][6] == 2 || board[1][6] == 2 || board[1][7] == 2 || board[2][5] == \
			2 || board[2][6] == 2 || board[2][7] == 2 || board[3][5] == 2 || board[3][6] == \
			2 || board[3][7] == 2 || board[3][8] == 2) {
			return 2;
		}
	}

	//if neither player wins, return 0
	return 0;
}
