
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clock.h"

int main(int argc, char *argv[]) {
	setbuf(stdout,0);

	time_t cur_time = time(NULL);


	ClockType cl;
	initClock(&cl);
	printClock(cur_time, &cl);
	cleanClock(&cl);

	return 0;
}
