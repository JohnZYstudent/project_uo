#define _POSIX_C_SOURCE 199309L
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
/*---------------------------------------------------------------------------*/

/*-----------------------------Program Main----------------------------------*/
static void signaler(pid_t pid[],int num){
	for(int i = 0 ; i < num; i++){
    	kill(pid[i], SIGUSR1);
    	sleep(1);
    }

}

static void handler(int sig){
	printf(" Child process %d Received signal %d \n", getpid(), sig);
	sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_SETMASK,&set,NULL);
   	int sign;
   	sigwait(&set, &sign);
}

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
	pid_t pid[numprograms],w;
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
			struct sigaction act;
			/*
			*struct sigaction {
            *	void (*sa_handler)(int);   signal num as only argument
            *   void (*sa_sigaction)(int, siginfo_t *, void *);
            *	sigset_t sa_mask;	a mask of signals which should be blocked during execution of the signal handler
            *	int sa_flags;	a set of flags which modify the behavior of the signal
            *	void (*sa_restorer)(void);
           	*};
            */
			act.sa_handler = &handler;
			sigemptyset(&act.sa_mask);
			act.sa_flags = 0;
			sigaction(SIGUSR1,&act,NULL);
			sleep(10);
			printf("child process:%d\n", getpid());
			execvp(programs[0],programs);
			free(cbuffer);
			free(c1buffer);
			fclose(stream);
			fclose(stream2);
			exit(-1);
		}	
	}
	printf("signal1\n");
	signaler(pid,numprograms);
	sleep(5);
	printf("finish1\n");
	printf("signal2\n");
	signaler(pid,numprograms);
	printf("finish2\n");
	for(int i = 0; i < numprograms; i++){
		if((w = waitpid(pid[i], &wstatus, WNOHANG)) == 0) {
        	kill(pid[i],SIGSTOP);
        	printf("stop!\n");
    	}	
	}
	for(int i = 0; i < numprograms; i++){
		if((w = waitpid(pid[i], &wstatus, WNOHANG)) == 0) {
        	kill(pid[i],SIGCONT);
        	printf("cont!\n");
    	}	 
	}
	
	return 1;
}