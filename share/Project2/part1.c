#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc,char *argv[]){
	size_t bufsize = 30;
	char *token;
	char *command;
	char *command1;
	int numprograms = 0;
	int count = 0;
	FILE *stream,*stream2;
	char *buffer = (char*)malloc(bufsize*sizeof(char));
	char *cbuffer = (char*)malloc(bufsize*sizeof(char));
	char *c1buffer = (char*)malloc(bufsize*sizeof(char));
	stream = fopen(argv[1],"r");
	while(getline(&buffer,&bufsize,stream) != -1){
		numprograms++;
	}
	free(buffer);
	fclose(stream);
	pid_t pid[numprograms];
	int wstatus;
	stream = fopen(argv[1],"r");
	stream2 = fopen(argv[1],"r");
	for(int i = 0; i < numprograms; i++){
		getline(&cbuffer,&bufsize,stream);
		getline(&c1buffer,&bufsize,stream2);
		command = strtok(cbuffer,"\n");
		command1 = strtok(c1buffer,"\n");
		while(token = strtok_r(command," ",&command)){
			count++;
		}
		count++;
		char *programs[count];
		for(int i =0;i<count;i++){
			programs[i]=NULL;
		}
		
		count = 0;
		while(token = strtok_r(command1," ",&command1)){
			programs[count] = token;
			count++;
		}

		count = 0;
		pid[i] = fork();
		if(pid[i] < 0){
			perror("fork");
			exit(1);
		}
		if(pid[i] == 0){
			printf("%d\n", getpid());
			execvp(programs[0],programs);
			free(cbuffer);
			free(c1buffer);
			fclose(stream);
			fclose(stream2);
			exit(-1);
		}	
	}
	for(int i = 0; i < numprograms; i++){
		waitpid(pid[i], &wstatus, WUNTRACED | WCONTINUED);
	}
	free(cbuffer);
	free(c1buffer);
	return 1;
}