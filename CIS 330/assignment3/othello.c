#include "othello.h"
#include <iostream>
CheckBoard *initBoard(CheckBoard* board){
    int i;
    //board->pieceBoard = (char**)calloc(sizeof(char*) ,  board->size);
    board->pieceBoard = new char * [board->size];
    for (i= 0; i < board->size; i++) {
        //board->pieceBoard[i] = (char*)calloc(sizeof(char) ,  board->size);
        board->pieceBoard[i] = new char[board->size];
    }
    //board->validHolder = (int**)calloc(sizeof(int*) , board->size);
    board->validHolder = new int * [board->size];
    for (i= 0; i < board->size; i++) {
        //board->validHolder[i] = (int*)calloc(sizeof(int) , board->size);
        board->validHolder[i] = new int[board->size];
    }
    return board;
}

void releaseBoard(CheckBoard* board){
    int i;
    for (i= 0; i < board->size; i++) {
        //free(board->pieceBoard[i]);
        delete[] board->pieceBoard[i];
    }
    //free(board->pieceBoard);
    delete[] board->pieceBoard;
    for (i= 0; i < board->size; i++) {
        //free(board->validHolder[i]);
        delete[] board->validHolder[i];
    }
    //free(board->validHolder);
    delete[] board->validHolder;
    //free(board);
    delete board;
}

CheckBoard* initialize(){
    //CheckBoard* board = (CheckBoard*)malloc(sizeof(CheckBoard));
    CheckBoard* board = new CheckBoard[1];
    //printf("Please enter the size of the board:");
    std::cout << "Please enter the size of the board:";

	//scanf("%d", &board->size);
	std::cin >> board->size;
    board = initBoard(board);
    //initinal 4 point in board
	board->pieceBoard[board->size / 2 - 1][board->size / 2 - 1] = BLACK;	
	board->pieceBoard[board->size / 2][board->size / 2] = BLACK;	
	board->pieceBoard[board->size / 2 - 1][board->size / 2] = WHITE;	
	board->pieceBoard[board->size / 2][board->size / 2 - 1] = WHITE;	
	ShowBoard(*board);//ShowBoard status of checkboard
	//printf("\nInitial:\n");
	std::cout << "\nInitial:\n";
    return board;
}

void printScore(CheckBoard board) {
    int row, col;
    int score[2];
	score[0] = score[1] = 0;
	for (row = 0; row < board.size; row++) {
		for (col = 0; col < board.size; col++) {
			score[0] = score[0] + (board.pieceBoard[row][col] == -1);
			score[1] = score[1] + (board.pieceBoard[row][col] == 1);
		}
	}
	//printf("socre robot :%d\nyou :%d\n", score[1], score[0]);
	std::cout << "socre robot :" << score[1] << std::endl;
	std::cout << "you :" << score[0] << std::endl;
}

void GameLoop(CheckBoard board) {
	char input[1024];
	int row, col, x, y, order = 0, i = 0,cross = 0, count = 4;
    int first = 0;
	//printf("Please choose first or second, Press 1 to be first,0 to be second:");
	std::cout << "Please choose first or second, Press 1 to be first,0 to be second:";
	//scanf("%d", &first);
	std::cin >> first;
	if (first == 0) order = 1;
	if (order == 0) order = 1;
	else order = 0;
	for (i = count; count < (board.size*board.size) && cross < 2;) {
		if (order == 1){
			order = 0;
			if (HaveSteps(board , 2)){
				for (;;){
					//printf("Please enter step(row column):");
					std::cout << "Please enter step(row column):";
					//scanf("%s", input);
					std::cin >> input;
					x = input[0] - '0';
					y = input[1];
					x--;
					if (y >= 'a') y = y - 'a' + 1;
					else y = y - 'A' + 1;
					y--;
					if (x >= 0 && y >= 0 && x < board.size && y < board.size && board.validHolder[x][y]) {
						Print(board, x, y, 2);
						count++;
						break;
					} else {
						//printf("invalid step, please re-choose .\n");
						std::cout << "invalid step, please re-choose .\n";
					}
				}
				ShowBoard(board);//ShowBoard status of checkboard
			} else if (++cross < 2) {
				//printf("ROBOT TURN.\n");
				std::cout << "ROBOT TURN.\n";
			} else{
				//printf("GAME OVER.\n");
				std::cout << "GAME OVER.\n";
			}
		} else{
			order = 1;
			if (HaveSteps(board, 1)) {
				cross = 0;
				EnemyStep(board, 1);
				count++;
				ShowBoard(board);
			} else {
				if (++cross < 2)
					//printf("YOU NOT MOVE, robot GO.\n");
					std::cout << "YOU NOT MOVE, robot GO.\n";
				else
					//printf("GAME OVER.");
					std::cout << "GAME OVER.";
			}
		}
	} 
	ShowBoard(board);
    printScore(board); 
	return;
}
void ShowBoard(CheckBoard board)
{
	int row, col;
	//printf("\n   ");
	std::cout << "\n   ";
	for (col = 0; col < board.size; col++){
		//printf("%c  ", col + 'a');
		char index = col+'a';
		std::cout << index <<"  ";
	}
	for (row = 0; row < board.size; row++) {
		//printf("\n ");
		std::cout << "\n ";
		for (col = 0; col < board.size; col++) {
			//printf("+--");
			std::cout << "+--";
			if (col == (board.size - 1))
				//printf("+\n");
				std::cout << "+\n";
		}
		//printf("%c", row + '1');
		char index2 = row + '1';
		std::cout << index2;
		for (col = 0; col < board.size; col++) {
			if (board.pieceBoard[row][col] == WHITE)
				//printf("| ○");
				std::cout << "| o";
			else if (board.pieceBoard[row][col] == BLACK)
				//printf("| ●");
				std::cout << "| ●";
			else
				//printf("|  ");
				std::cout << "|  ";
			if (col == (board.size - 1))
				//printf("|");
				std::cout << "|";
		}
		if (row == (board.size - 1)) {
			//printf("\n ");
			std::cout << "\n";
			for (col = 0; col < board.size; col++){
				//printf("+--");
				std::cout << "+--";
				if (col == (board.size - 1))
					//printf("+\n");
					std::cout << "+\n";
			}
		}
	}
}
int HaveSteps(CheckBoard board, char order) {
	int i, rowedge, coledge, row, col, m, n = 0, step = 0;
	char enemy, player;
	if (order == 1)
		enemy = -1;
	else
		enemy = 1;
	player = -1 * enemy;
	for (row = 0; row < board.size; row++)
	{
		for (col = 0; col < board.size; col++)
		{
			board.validHolder[row][col] = 0;
		}
	}
	for (row = 0; row < board.size; row++){
		for (col = 0; col < board.size; col++){
			if (board.pieceBoard[row][col] != 0)
				continue;
			for (rowedge = -1; rowedge <= 1; rowedge++)
				for (coledge = -1; coledge <= 1; coledge++){
					if (row + rowedge < 0 || row + rowedge >= board.size
						|| col + coledge < 0 || col + coledge >= board.size
						|| (rowedge == 0 && coledge == 0)) {
						continue;
					}
					if (board.pieceBoard[row + rowedge][col + coledge] == enemy){
						m = row + rowedge;
						n = col + coledge;
						for(;;){
							m += rowedge;
							n += coledge;
							if (m < 0 || m >= board.size || n < 0 || n >= board.size)
								break;
							if (board.pieceBoard[m][n] == 0)
								break;
							if (board.pieceBoard[m][n] == player) {
								board.validHolder[row][col] = 1;
								step++;
								break;
							}
						}
					}
				}
			}
	}
    //printf("step %d", step);
    std::cout << "step " << step;
	return step;
}
void Print(CheckBoard board, int row, int col, char order)
{
	int rowedge = 0, coledge = 0, x = 0, y = 0;
	char enemy;
	if (order == 1)
		enemy = -1;
	else
		enemy = 1;
	char player = -1 * enemy;
	board.pieceBoard[row][col] = player;
	for (rowedge = -1; rowedge <= 1; rowedge++) {
		for (coledge = -1; coledge <= 1; coledge++){
			if (row + rowedge < 0 || row + rowedge >= board.size || col + coledge < 0
				|| col + coledge >= board.size || (rowedge == 0 && coledge == 0))
				continue;
			if (board.pieceBoard[row + rowedge][col + coledge] == enemy){
				x = row + rowedge;
				y = col + coledge;
                for(;;) {
					x += rowedge;
					y += coledge;
					if (x < 0 || x >= board.size || y < 0 || y >= board.size)//assert edge
						break;
					if (board.pieceBoard[x][y] == 0)
						break;
					if (board.pieceBoard[x][y] == player){
						while (board.pieceBoard[x -= rowedge][y -= coledge] == enemy){//find out current position
							board.pieceBoard[x][y] = player;
						}
						break;
					}
				}
			}
		}
	}
}
int CalSore(CheckBoard board, char order)
{
	int score = 0, row, col;
	char enemy, player;
	if (order == 1) enemy = -1;
	else enemy = 1;
	player = -1 * enemy;
	for (row = 0; row < board.size; row++) {
		for (col = 0; col < board.size; col++){
			score = score - (board.pieceBoard[row][col] == enemy);
			score = score + (board.pieceBoard[row][col] == player);
		}
    }
	return score;
}
int FindBestScore(CheckBoard board, char order)
{
	int row, col, m, n, max = 0, score = 0;
	char enemy;
    //CheckBoard* tmpboard = (CheckBoard*)malloc(sizeof(CheckBoard));
    CheckBoard* tmpboard = new CheckBoard[1];
    tmpboard->size = board.size;
    initBoard(tmpboard);
	if (order == 1) enemy = -1;
	else enemy = 1;

	for (row = 0; row < board.size; row++) {
		for (col = 0; col < board.size; col++){
			if (!board.validHolder[row][col])
				continue;
			for (m = 0; m < board.size; m++)
				for (n = 0; n < board.size; n++){
					tmpboard->pieceBoard[m][n] = board.pieceBoard[m][n];
				}
			Print(*tmpboard, row, col, order);
			score = CalSore(*tmpboard, order);
			if (max< score)
				max= score;
		}
    }
    releaseBoard(tmpboard);
	return max;
}

int main() {

	//printf("othello games\n");
	std::cout << "othello games\n";
    CheckBoard* board = initialize();
    GameLoop(*board);
    releaseBoard(board);
}

void EnemyStep(CheckBoard board, char order)
{
	int row, col, rowtmp, coltmp, m, n, score = 0, min = 100;
	char enemy;
    //CheckBoard* tmpboard = (CheckBoard*)malloc(sizeof(CheckBoard));
    CheckBoard* tmpboard = new CheckBoard[1];
    tmpboard->size = board.size;
    initBoard(tmpboard);
	if (order == 1)  enemy = -1;
	else enemy = 1;
	for (row = 0; row < board.size; row++) {
		for (col = 0; col < board.size; col++){
			if (board.validHolder[row][col] == 0)
				continue;
			for (m = 0; m < board.size; m++){
				for (n = 0; n < board.size; n++){
					tmpboard->pieceBoard[m][n] = board.pieceBoard[m][n];
				}
			}
			Print(*tmpboard, row, col, order);
			HaveSteps(*tmpboard, enemy);
			score = FindBestScore(*tmpboard, enemy);
			if ((row == 0 && col == board.size - 1 || row == board.size - 1 && col == 0 || row == board.size - 1 && col == board.size - 1) ||(row == 0 && col == 0))  {
				min = score;
				rowtmp = row;
				coltmp = col;
			} else if (row == 0 || row == board.size - 1 || col == 0 || col == board.size - 1) {
				min = score;
				rowtmp = row;
				coltmp = col;
			} else if (score < min){
				min = score;
				rowtmp = row;
				coltmp = col;
			}
		}
	}
	Print(board, rowtmp, coltmp, order);
    releaseBoard(tmpboard);
}
