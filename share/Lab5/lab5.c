/*
* Description: A simple lab showing signal processing
*
* Author: Jared Hall
*
* Date: 10/21/2019
*
* Notes:
* 1. to be done in lab
*/

/*-------------------------Preprocessor Directives---------------------------*/
#define _POSIX_C_SOURCE 199309L
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
    	sleep(2);
    }

}

static void handler(int sig){
	printf(" Child process %d Received signal %d \n", getpid(), sig);
	sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

   	int sign;
   	sigwait(&set, &sign);
}

int	main(){
	//variable definitions
	
	pid_t  pid[5], w;
	int wstatus, i;
	i=0;
	for(int j=0; j < 5; j++){
		pid[j] = fork();
		if(pid[j] == 0){
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
			act.sa_handler = &handler;;
			act.sa_flags = 0;
			sigaction(SIGUSR1,&act,NULL);
			printf("	Child Process: %i - Starting infinite loop...\n", pid[j]);
			while(1){
				i++;
				if(i%10000) {
					printf("	Child Process: %i - Running infinite loop...\n", getpid());
					i=0;
				}
			}
		}else{
			printf("Parent Process: %i, Waiting for child to finish...\n", getpid());
		} 
	}
	signaler(pid,5);

	signaler(pid,5);

    for(int i = 0 ; i < 5; i++){
    	kill(pid[i], SIGINT);
    	w = waitpid(pid[i], &wstatus, WUNTRACED | WCONTINUED);
    }
	printf("All child processes joined. Exiting\n");
}
/*-----------------------------Program End-----------------------------------*/
