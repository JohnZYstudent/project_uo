/*
* Description: <write a brief description of your lab>
*
* Author: <your name>
*
* Date: <today's date>
*
* Notes: 
* 1. <add notes we should consider when grading>
*/

/*-------------------------Preprocessor Directives---------------------------*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "command.h"
/*---------------------------------------------------------------------------*/

/*----------------------------Function Definitions---------------------------*/
void lfcat()
{
	printf("<<In lfcat(): function called>>\n");
	/* Define your variables here */
	char path[100];
	struct dirent *entry;
	FILE *file;
	FILE *stream;
	size_t nread;
	char *buffer;
	size_t bufsize = 30;
	DIR *dir;
	char str[82] = "\n--------------------------------------------------------------------------------\n";
	char title[6] = "File: ";
	char enter[1] = "\n";
	/* Open the file output.txt for writing */
	file = fopen("output.txt", "w");
	/* Get the current directory*/
	getcwd(path,sizeof(path));
	/* Open the dir using opendir() */
	dir = opendir(path);
	/* use a while loop to read the dir */
	while((entry = readdir(dir)) != NULL){
		/* Hint: use an if statement to skip any names that are not readable files (e.g. ".", "..", "lab-3.c", "lab3", "output.txt" */
		if(strcmp(entry->d_name,"command.h")!=0 && strcmp(entry->d_name,".")!=0 && 
				strcmp(entry->d_name,"..")!=0 && strcmp(entry->d_name,"lab-3.c")!=0 && 
				strcmp(entry->d_name,"lab3.exe")!=0 && strcmp(entry->d_name,"output.txt")!=0){
			buffer = (char *)malloc(bufsize*sizeof(char));

			fwrite(title,sizeof(title),1,file);
			fwrite(entry->d_name,strlen(entry->d_name),1,file);
			fwrite(enter,sizeof(enter),1,file);

			/* Open the file */
			stream = fopen(entry->d_name,"r");
			/* Read in each line using getline() */
			while((nread = getline(&buffer,&bufsize,stream)) != -1){
				/* Write each line to output.txt */
				fwrite(buffer,nread,1,file);
			}
			/* print 80 "-" characters to output.txt */
			fwrite(str,sizeof(str),1,file);
			/* close the read file and frre/null assign your line buffer */
			fclose(stream);
			free(buffer);
			}
	}
	/*close both the output file and the directory you were reading from using closedir() and fclose() */
	closedir(dir);
	fclose(file);
}

/*---------------------------------------------------------------------------*/
/*-----------------------------Program Main----------------------------------*/
int main() {
	setbuf(stdout, NULL);
	
	/*function vars */
	char *cBuffer;
	size_t bufferSize = 50;
	size_t inputSize;
	char *token;
	
	/* Allocate memory to the input buffer. */
	cBuffer = (char *)malloc(bufferSize * sizeof(char));
	if( cBuffer == NULL)
	{
		printf("Error! Unable to allocate input buffer. \n");
		exit(1);
	}
	
	/*main run cycle*/
	do {
	
	printf( ">>> ");
	inputSize = getline(&cBuffer, &bufferSize, stdin);
	
	/* tokenize the input string */
	token = strtok(cBuffer, " ");
	while(token != NULL && strcmp(token, "\n")) {
		
		/*if the command is 'exit then close the program*/
		if(strcmp(token, "exit\n") == 0 || strcmp(token, "exit") == 0) { break; }
		
		/*Display any commands */
		if(strcmp(token, "lfcat\n") == 0) {lfcat();}
		else {printf("Error: Unrecognized command! \n"); break;}
		token = strtok(NULL, " ");
	}
	if(token != NULL) {if(strcmp(token, "exit\n") == 0 || strcmp(token, "exit") == 0) { break; }}
	} while (1);
	/*Free the allocated memory*/
	free(cBuffer);
	return 0;
}
/*-----------------------------Program End-----------------------------------*/
