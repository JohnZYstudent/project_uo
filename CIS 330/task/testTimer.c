
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "timer.h"

int main(int argc, char *argv[]) {
	setbuf(stdout,0);

	int minutes = 0;
	int seconds = 0;
	ClockType cl;

	printf("How long should the timer run (MM:SS)? ");
	scanf("%d:%d",&minutes,&seconds);
	//printf("%02d:%02d\n",minutes,seconds);

	initTimer(&cl,minutes,seconds);
	runTimer();
	cleanTimer(&cl);

	return 0;
}
