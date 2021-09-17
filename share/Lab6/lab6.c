/*-----------------------------------------------------------------------------
File name: Lab5.c
Description: A simple lab showing the use of signals.
Author: Jared Hall
-----------------------------------------------------------------------------*/

/*---------------------------Preprocessor Directives-------------------------*/
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
/*---------------------------------------------------------------------------*/

/*---------------------------------Functions---------------------------------*/
/*---------------------------------------------------------------------------*/

/*--------------------------------Program Main-------------------------------*/
int main(void) 
{
    //variable declarations
    pid_t pid, w;
    int wstatus, eStatus;
    //create a child process
    pid = fork();
    if(pid < 0) {
        perror("Error! could not create a new process.\n");
        exit(EXIT_FAILURE);
    }else if(pid == 0) {
        //This code runs in the child process only
        printf("    Child process: %d - Starting...\n", getpid());
        //Add your while loop here
        int count = 0;        
        while (count < 10) {
            count++;
            printf("Child process <%d> - Still alive after for <%d> seconds\n",getpid(),(10-count));
            sleep(1);           
            
        }
	   exit(EXIT_SUCCESS);

    } else if(pid > 0) {
        //This code runs in the parent process only
	printf("Parent process: %d - Sending signals to child...\n", getpid());
	//Add code to send your signals in a loop here
    
	printf("Parent process: %d - Waiting for child to complete...\n", getpid());
    while ((w = waitpid(pid, &wstatus, WNOHANG)) == 0) {
        kill(pid,SIGSTOP);
        printf("stop!\n");
        sleep(3);
        kill(pid,SIGCONT);
        printf("cont!\n");
        sleep(1);
    }
	printf("Parent process: %d - Finished\n", getpid());
    }
    
    //exit out of program
    return EXIT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
