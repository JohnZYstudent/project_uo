#ifndef OTHELLO_H
#define OTHELLO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 8

enum DISKCOLOR{
    BLACK = -1,
    WHITE = 1,
};

typedef struct _CheckBoard{
	char** pieceBoard;
	int** validHolder;
    int size;
}CheckBoard;

//calc if player have change to step
int HaveSteps(CheckBoard, char );
void Print(CheckBoard, int , int , char );
//calculate score
int CalSore(CheckBoard, char );
//find the best step
int FindBestScore(CheckBoard, char );
//enemy player opetator 
void EnemyStep(CheckBoard, char );
//show status of checkboard
void ShowBoard(CheckBoard);
void GameLoop(CheckBoard); 

#endif // #ifndef OTHELLO_H
