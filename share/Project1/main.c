/* 
 * Project 1 main.c
 * 
 * Author: <John Zhou>
 * 
 * Date: 10/20/2019 
 * 
 * Notes: <write anything you would like us to keep in mind when grading.> 
 * Proper code documentation includes: 
 * 1. Using a readable formatting. 
 * 2. Adequate use of comments and white space.  
 * 3. Explanation attached to code blocks that do not work. 
 * 4. Keep the width of the program under 80 columns to avoid overwrap. 
 */
/*-------------------------Preprocessor Directives---------------------------*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
/*---------------------------------------------------------------------------*/
/*-----------------------------Program Main----------------------------------*/
int main(int argc, char *argv[]) {
/* Variables */	
	FILE *stream;
	FILE *file;
	setbuf(stdout, NULL);
	char *buffer;
	size_t bufsize = 30;
	const char space[2] = " ";
	const char semi[4] = ";";
	char *line;
	char *token;
	char* command[4];
	int count;
	char* laste[1];
	int stop = 1;

	buffer = (char *)malloc(bufsize*sizeof(char));
	if(strcmp(argv[1],"-command") == 0){
		while(stop){
			printf(">>>");
			getline(&buffer,&bufsize,stdin);
			// buffer = strtok(buffer, "\n");
			line = strtok(buffer, semi);
			while(line != NULL){
				count = 0;
				for(int i = 0; i<4; i++){
					command[i] = "";
				}
				while(token = strtok_r(line,space,&line)){
						command[count] = token;
						count ++;
				}

				if(strcmp(command[0], "\n") == 0){
					printf("Error! Unrecognized command: %s\n", command[0]);
					break;
				}else if(strcmp(command[0], "ls") == 0 || strcmp(command[0], "ls\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						listDir();
						
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else{
						printf("Error! Unsupported parameters for command:%s\n",command[0]);
						break;
					}
				}else if(strcmp(command[0], "pwd") == 0 || strcmp(command[0], "pwd\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						showCurrentDir();
						
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else{
						printf("Error! Unsupported parameters for command:%s\n",command[0]);
						break;
					}
				}else if(strcmp(command[0], "exit") == 0 || strcmp(command[0], "exit\n") == 0){
					stop = 0;
					break;
				}else if(strcmp(command[0], "mkdir") == 0 || strcmp(command[0], "mkdir\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else {
						if(strcmp(command[2], "") == 0 || strcmp(command[2], "\n") == 0){
							command[1] = strtok_r(command[1], "\n", &command[1]);
							makeDir(command[1]);
						}else{
							if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

								printf("Error! Incorrect syntax. No control code found.\n");
								break;
							}else{
								printf("Error! Incorrect parameters. Too many parameters\n");
								break;
							}
						}
					}
				}else if(strcmp(command[0], "cd") == 0 || strcmp(command[0], "cd\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else {
						if(strcmp(command[2], "") == 0 || strcmp(command[2], "\n") == 0){
							command[1] = strtok_r(command[1], "\n", &command[1]);
							changeDir(command[1]);
						}else{
							if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

								printf("Error! Incorrect syntax. No control code found.\n");
								break;
							}else{
								printf("Error! Incorrect parameters. Too many parameters\n");
								break;
							}
						}
					}
				}else if(strcmp(command[0], "rm") == 0 || strcmp(command[0], "rm\n") == 0){
					if(strcmp(command[1], "") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else {
						if(strcmp(command[2], "") == 0  || strcmp(command[2], "\n") == 0){
							command[1] = strtok_r(command[1],"\n",&command[1]);
							deleteFile(command[1]);
						}else{
							if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

								printf("Error! Incorrect syntax. No control code found.\n");
								break;
							}else{
								printf("Error! Incorrect parameters. Too many parameters\n");
								break;
							}
						}
					}
				}else if(strcmp(command[0], "cat") == 0 || strcmp(command[0], "cat\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else {
						if(strcmp(command[2], "") == 0 || strcmp(command[2], "\n") == 0){
							command[1] = strtok_r(command[1], "\n", &command[1]);
							displayFile(command[1]);
						}else{
							if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

								printf("Error! Incorrect syntax. No control code found.\n");
								break;
							}else{
								printf("Error! Incorrect parameters. Too many parameters\n");
								break;
							}
						}
					}	
				}else if(strcmp(command[0], "cp") == 0 || strcmp(command[0], "cp\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else{
						if(strcmp(command[2], "") == 0 || strcmp(command[2], "\n") == 0){
							printf("Error! Incorrect parameters. Missing parameters\n");
							break;
						}else if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

							printf("Error! Unsupported parameters for command:%s\n",command[0]);
							break;
						}else{
							if(strcmp(command[3], "") == 0 || strcmp(command[3], "\n") == 0){
								command[2] = strtok_r(command[2], "\n", &command[2]);
								copyFile(command[1],command[2]);
							}else{
								if(strcmp(command[3], "ls") == 0 || strcmp(command[3], "ls\n") == 0 || 
								strcmp(command[3], "pwd") == 0 || strcmp(command[3], "pwd\n") == 0 ||
								strcmp(command[3], "mkdir") == 0 || strcmp(command[3], "mkdir\n") == 0 ||
								strcmp(command[3], "cd") == 0 || strcmp(command[3], "cd\n") == 0 ||
								strcmp(command[3], "cp") == 0 || strcmp(command[3], "cp\n") == 0 ||
								strcmp(command[3], "mv") == 0 || strcmp(command[3], "mv\n") == 0 ||
								strcmp(command[3], "rm") == 0 || strcmp(command[3], "rm\n") == 0 ||
								strcmp(command[3], "cat") == 0 || strcmp(command[3], "cat\n") == 0){

									printf("Error! Incorrect syntax. No control code found.\n");
									break;
								}else{
								printf("Error! Incorrect parameters. Too many parameters\n");
									break;
							}
							}
						}
					}
				}else if(strcmp(command[0], "mv") == 0 || strcmp(command[0], "mv\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else{
						if(strcmp(command[2], "") == 0 || strcmp(command[2], "\n") == 0){
							printf("Error! Incorrect parameters. Missing parameters\n");
							break;
						}else if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

							printf("Error! Unsupported parameters for command:%s\n",command[0]);
							break;
						}else{
							if(strcmp(command[3], "") == 0 || strcmp(command[3], "\n") == 0){
								command[2] = strtok_r(command[2], "\n", &command[2]);
								moveFile(command[1],command[2]);
							}else{
								if(strcmp(command[3], "ls") == 0 || strcmp(command[3], "ls\n") == 0 || 
								strcmp(command[3], "pwd") == 0 || strcmp(command[3], "pwd\n") == 0 ||
								strcmp(command[3], "mkdir") == 0 || strcmp(command[3], "mkdir\n") == 0 ||
								strcmp(command[3], "cd") == 0 || strcmp(command[3], "cd\n") == 0 ||
								strcmp(command[3], "cp") == 0 || strcmp(command[3], "cp\n") == 0 ||
								strcmp(command[3], "mv") == 0 || strcmp(command[3], "mv\n") == 0 ||
								strcmp(command[3], "rm") == 0 || strcmp(command[3], "rm\n") == 0 ||
								strcmp(command[3], "cat") == 0 || strcmp(command[3], "cat\n") == 0){

									printf("Error! Incorrect syntax. No control code found.\n");
									break;
								}else{
									printf("Error! Incorrect parameters. Too many parameters\n");
									break;
								}
							}
						}
					}		
				}else{
					printf("Error! Unrecognized command: %s\n", command[0]);
					break;
				}

				line = strtok(NULL, semi);
			}
		}
	}
	else if(strcmp(argv[1],"-f") == 0){
		stream = fopen(argv[2],"r");
		file = freopen("output.txt","w",stdout);
		while(getline(&buffer,&bufsize,stream) != -1){
			line = strtok(buffer, semi);
			while(line != NULL){
				count = 0;
				for(int i = 0; i<4; i++){
					command[i] = "";
				}
				while(token = strtok_r(line,space,&line)){
						command[count] = token;
						count ++;
				}

				if(strcmp(command[0], "\n") == 0){
					printf("Error! Unrecognized command: %s\n", command[0]);
					break;
				}else if(strcmp(command[0], "ls") == 0 || strcmp(command[0], "ls\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						listDir();
						
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else{
						printf("Error! Unsupported parameters for command:%s\n",command[0]);
						break;
					}
				}else if(strcmp(command[0], "pwd") == 0 || strcmp(command[0], "pwd\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						showCurrentDir();
						
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else{
						printf("Error! Unsupported parameters for command:%s\n",command[0]);
						break;
					}
				}else if(strcmp(command[0], "exit") == 0 || strcmp(command[0], "exit\n") == 0){
					stop = 0;
					break;
				}else if(strcmp(command[0], "mkdir") == 0 || strcmp(command[0], "mkdir\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else {
						if(strcmp(command[2], "") == 0 || strcmp(command[2], "\n") == 0){
							command[1] = strtok_r(command[1], "\n", &command[1]);
							makeDir(command[1]);
						}else{
							if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

								printf("Error! Incorrect syntax. No control code found.\n");
								break;
							}else{
								printf("Error! Incorrect parameters. Too many parameters\n");
								break;
							}
						}
					}
				}else if(strcmp(command[0], "cd") == 0 || strcmp(command[0], "cd\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else {
						if(strcmp(command[2], "") == 0 || strcmp(command[2], "\n") == 0){
							command[1] = strtok_r(command[1], "\n", &command[1]);
							changeDir(command[1]);
						}else{
							if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

								printf("Error! Incorrect syntax. No control code found.\n");
								break;
							}else{
								printf("Error! Incorrect parameters. Too many parameters\n");
								break;
							}
						}
					}
				}else if(strcmp(command[0], "rm") == 0 || strcmp(command[0], "rm\n") == 0){
					if(strcmp(command[1], "") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else {
						if(strcmp(command[2], "") == 0  || strcmp(command[2], "\n") == 0){
							command[1] = strtok_r(command[1], "\n", &command[1]);
							deleteFile(command[1]);
						}else{
							if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

								printf("Error! Incorrect syntax. No control code found.\n");
								break;
							}else{
								printf("Error! Incorrect parameters. Too many parameters\n");
								break;
							}
						}
					}
				}else if(strcmp(command[0], "cat") == 0 || strcmp(command[0], "cat\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else {
						if(strcmp(command[2], "") == 0 || strcmp(command[2], "\n") == 0){
							command[1] = strtok_r(command[1], "\n", &command[1]);
							displayFile(command[1]);
						}else{
							if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

								printf("Error! Incorrect syntax. No control code found.\n");
								break;
							}else{
								printf("Error! Incorrect parameters. Too many parameters\n");
								break;
							}
						}
					}	
				}else if(strcmp(command[0], "cp") == 0 || strcmp(command[0], "cp\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else{
						if(strcmp(command[2], "") == 0 || strcmp(command[2], "\n") == 0){
							printf("Error! Incorrect parameters. Missing parameters\n");
							break;
						}else if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

							printf("Error! Unsupported parameters for command:%s\n",command[0]);
							break;
						}else{
							if(strcmp(command[3], "") == 0 || strcmp(command[3], "\n") == 0){
								command[2] = strtok_r(command[2], "\n", &command[2]);
								copyFile(command[1],command[2]);
							}else{
								if(strcmp(command[3], "ls") == 0 || strcmp(command[3], "ls\n") == 0 || 
								strcmp(command[3], "pwd") == 0 || strcmp(command[3], "pwd\n") == 0 ||
								strcmp(command[3], "mkdir") == 0 || strcmp(command[3], "mkdir\n") == 0 ||
								strcmp(command[3], "cd") == 0 || strcmp(command[3], "cd\n") == 0 ||
								strcmp(command[3], "cp") == 0 || strcmp(command[3], "cp\n") == 0 ||
								strcmp(command[3], "mv") == 0 || strcmp(command[3], "mv\n") == 0 ||
								strcmp(command[3], "rm") == 0 || strcmp(command[3], "rm\n") == 0 ||
								strcmp(command[3], "cat") == 0 || strcmp(command[3], "cat\n") == 0){

									printf("Error! Incorrect syntax. No control code found.\n");
									break;
								}else{
								printf("Error! Incorrect parameters. Too many parameters\n");
									break;
							}
							}
						}
					}
				}else if(strcmp(command[0], "mv") == 0 || strcmp(command[0], "mv\n") == 0){
					if(strcmp(command[1], "") == 0 || strcmp(command[1], "\n") == 0){
						printf("Error! Incorrect parameters. Missing parameters\n");
						break;
					}else if(strcmp(command[1], "ls") == 0 || strcmp(command[1], "ls\n") == 0 || 
						strcmp(command[1], "pwd") == 0 || strcmp(command[1], "pwd\n") == 0 ||
						strcmp(command[1], "mkdir") == 0 || strcmp(command[1], "mkdir\n") == 0 ||
						strcmp(command[1], "cd") == 0 || strcmp(command[1], "cd\n") == 0 ||
						strcmp(command[1], "cp") == 0 || strcmp(command[1], "cp\n") == 0 ||
						strcmp(command[1], "mv") == 0 || strcmp(command[1], "mv\n") == 0 ||
						strcmp(command[1], "rm") == 0 || strcmp(command[1], "rm\n") == 0 ||
						strcmp(command[1], "cat") == 0 || strcmp(command[1], "cat\n") == 0){

						printf("Error! Incorrect syntax. No control code found.\n");
						break;
					}else{
						if(strcmp(command[2], "") == 0 || strcmp(command[2], "\n") == 0){
							printf("Error! Incorrect parameters. Missing parameters\n");
							break;
						}else if(strcmp(command[2], "ls") == 0 || strcmp(command[2], "ls\n") == 0 || 
								strcmp(command[2], "pwd") == 0 || strcmp(command[2], "pwd\n") == 0 ||
								strcmp(command[2], "mkdir") == 0 || strcmp(command[2], "mkdir\n") == 0 ||
								strcmp(command[2], "cd") == 0 || strcmp(command[2], "cd\n") == 0 ||
								strcmp(command[2], "cp") == 0 || strcmp(command[2], "cp\n") == 0 ||
								strcmp(command[2], "mv") == 0 || strcmp(command[2], "mv\n") == 0 ||
								strcmp(command[2], "rm") == 0 || strcmp(command[2], "rm\n") == 0 ||
								strcmp(command[2], "cat") == 0 || strcmp(command[2], "cat\n") == 0){

							printf("Error! Unsupported parameters for command:%s\n",command[0]);
							break;
						}else{
							if(strcmp(command[3], "") == 0 || strcmp(command[3], "\n") == 0){
								command[2] = strtok_r(command[2], "\n", &command[2]);
								moveFile(command[1],command[2]);
							}else{
								if(strcmp(command[3], "ls") == 0 || strcmp(command[3], "ls\n") == 0 || 
								strcmp(command[3], "pwd") == 0 || strcmp(command[3], "pwd\n") == 0 ||
								strcmp(command[3], "mkdir") == 0 || strcmp(command[3], "mkdir\n") == 0 ||
								strcmp(command[3], "cd") == 0 || strcmp(command[3], "cd\n") == 0 ||
								strcmp(command[3], "cp") == 0 || strcmp(command[3], "cp\n") == 0 ||
								strcmp(command[3], "mv") == 0 || strcmp(command[3], "mv\n") == 0 ||
								strcmp(command[3], "rm") == 0 || strcmp(command[3], "rm\n") == 0 ||
								strcmp(command[3], "cat") == 0 || strcmp(command[3], "cat\n") == 0){

									printf("Error! Incorrect syntax. No control code found.\n");
									break;
								}else{
									printf("Error! Incorrect parameters. Too many parameters\n");
									break;
								}
							}
						}
					}		
				}else{
					printf("Error! Unrecognized command:%s\n", command[0]);
					break;
				}

				line = strtok(NULL, semi);
			}
		}
		fclose(stream);
	}else{
		printf("Error, unkown mode command\n");
	}

	free(buffer);
	

	return 1;
}
/*-----------------------------Program End-----------------------------------*/