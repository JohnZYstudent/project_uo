
/*
* Description: <write a brief description of your lab>
*
* Author: John(Ziyuan) Zhou
*
* Date: 10/08/2019
*
* Notes: 
* 1. <add notes we should consider when grading>
*/

/*-------------------------Preprocessor Directives---------------------------*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*---------------------------------------------------------------------------*/

/*-----------------------------Program Main----------------------------------*/
int main(int argc, char *argv[]) {
	FILE *stream;
	setbuf(stdout, NULL);
	char *buffer;
	size_t bufsize = 30;
	const char s[2] = " ";
	char *token;
	int count = 0;
	/* Main Function Variables */
	buffer = (char *)malloc(bufsize*sizeof(char));
	stream = fopen(argv[1],"r");
	/* Allocate memory for the input buffer. */
	while(getline(&buffer,&bufsize,stream) != -1){
		buffer = strtok(buffer, "\n");
		token = strtok(buffer, s);
		while(token != NULL){
			printf("T%d: %s\n",count,token);
			count ++;
			token = strtok(NULL, s);
		}
		count = 0;
	}
	/*main run loop*/
		/* Print >>> then get the input string */

		/* Tokenize the input string */

		/* Display each token */
		
		/* If the user entered <exit> then exit the loop */
	free(token);
	free(buffer);
	fclose(stream);
	/*Free the allocated memory*/

	return 1;
}
/*-----------------------------Program End-----------------------------------*/