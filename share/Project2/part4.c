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
int check = 0;
static void handler(int sig){
	printf(" Child process %d Received signal %d \n", getpid(), sig);
	sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_SETMASK,&set,NULL);
   	int sign;
   	sigwait(&set, &sign);
}

static void handler1(int sig) {
	check = 1;
}

static void print(pid_t pid){
	char mask[1250];
	int pid_num;
	char comm[1250],state;
	long vsize;
	int stime, utime;
	sprintf(mask,"/proc/%u/stat",pid);
	FILE *file = fopen(mask,"r");
	if (file == NULL) {
		return;
	}
	fscanf(file, "%d %s %c %lu %lu %lu ", &pid_num,comm,&state,&utime,&stime,&vsize);
	printf("pid:%d name:%s state:%c stime:%lu utime:%lu exec_time:%lu mem_size:%lu\n", pid_num,comm,state,stime,utime,stime+utime,vsize);
	fclose(file);
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
            act.sa_handler = &handler;
			sigemptyset(&act.sa_mask);
			act.sa_flags = 0;
			sigaction(SIGUSR1,&act,NULL);
			sleep(10);
			// printf("child process:%d\n", getpid());
			execvp(programs[0],programs);
			free(cbuffer);
			free(c1buffer);
			fclose(stream);
			fclose(stream2);
			exit(-1);
		}	
	}


	printf("signal1\n");
	for(int i = 0 ; i < numprograms; i++){
    	kill(pid[i], SIGUSR1);
    	sleep(2);
    }
	printf("finish1\n");
	printf("signal2\n");
	for(int i = 0 ; i < numprograms; i++){
    	kill(pid[i], SIGUSR1);
    	if(i != numprograms-1){
    		kill(pid[i],SIGSTOP);
    		printf("stop:%d\n",pid[i]);
    	}
    	sleep(2);
    }
	printf("finish2\n");
	int index = numprograms-1;
	int flag = 1;
	while(flag){
    	signal(SIGALRM,handler1);
    	alarm(5);
    	sleep(5);
    	if(check == 1){
    		while(1){
				if((w = waitpid(pid[index%numprograms], &wstatus, WNOHANG)) == 0){
    				kill(pid[index%numprograms],SIGSTOP);
    				index++;
    				break;
				}else{
					break;
				}	   			
			}

			while(1){
   				if((w = waitpid(pid[index%numprograms], &wstatus, WNOHANG)) == 0){
					kill(pid[index%numprograms],SIGCONT);
					sleep(4);
					for(int i = 0; i < numprograms; i++){
                        if(waitpid(pid[i], &wstatus, WNOHANG) == 0){
                            print(pid[i]);
                        }
                    }
					break;
    			}
    			index++;
			}
			check = 0;
    	}
    	printf("\n");
    	for(int i = 0 ; i < numprograms; i++){
			if((w = waitpid(pid[i], &wstatus, WNOHANG)) == 0){
    			flag = 1;
    		}else{
    			flag = 0;
    		}	
		} 

	}
	return 1;
}