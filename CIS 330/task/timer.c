#include "timer.h"

#include <stdio.h>
#include <stdlib.h>

int hour = 0;
int min = 0;
int sec = 0;
ClockType *cl = NULL;


// Initialize the timer with the user-provided input
void initTimer(ClockType *clock, int minutes, int seconds) {
	initClock(clock);
	cl = clock;

	clock->showHour = 0;
	min = minutes;
	sec = seconds;
}

//create a time_t with given hour, min and sec
time_t makeTime(int hour, int min, int sec) {
	time_t cur_time = time(NULL);
	struct tm* t = localtime(&cur_time);

	t->tm_hour = hour;
	t->tm_min = min;
	t->tm_sec = sec;

	return mktime(t);
}

// Run the timer -- print out the time each second
void runTimer() {
	time_t cur_time = 0l;
	clock_t start = 0, finish = 0;
	double diff = 0;

	while (min > 0 || sec > 0) {
		//create time
		cur_time = makeTime(hour, min, sec);

		//clear screen
		system("cls");

		//print time
		printClock(cur_time, cl);

		//sleep for 1 second
		start = clock();
		finish = clock();
		diff = (double) (finish - start) / CLOCKS_PER_SEC;
		while (diff < 1) {
			finish = clock();
			diff = (double) (finish - start) / CLOCKS_PER_SEC;
		}

		//decrease counter by 1 second
		sec--;
		if (sec < 0) {
			sec = 59;
			min--;
			if (min < 0) {
				min = 0;
				sec = 0;
			}
		}
	}

	//show 00:00
	cur_time = makeTime(hour, min, sec);
	system("cls");
	printClock(cur_time, cl);
}

// Clean up memory (as needed)
void cleanTimer(ClockType *clock) {
	cleanClock(clock);
}



// Initialize the clock data structure
void initClock(ClockType *clock) {
	int i = 0, j = 0, k = 0;
	int p = 0, q = 0;
	int n = 0;

	//set width and height of number matrix
	clock->showHour = 1;
	clock->width = 5;
	clock->height = 8;

	//allocate memory space for table(a 3-dimension array)
	clock->table = (char***) malloc(sizeof(char**) * 11);
	for (i = 0; i < 11; i++) {
		clock->table[i] = (char**) malloc(sizeof(char*) * clock->height);
		for (j = 0; j < clock->height; j++) {
			clock->table[i][j] = (char*) malloc(sizeof(char) * clock->width);
			for (k = 0; k < clock->width; k++) {
				clock->table[i][j][k] = ' ';
			}
		}
	}

	//0
	n = 0;
	for (i = 0; i < clock->height; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height - 1 || j == 0
					|| j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}

	//1
	n = 1;
	j = (clock->width - 1) / 2 - 1;
	for (i = 0; i < clock->height; i++) {
		clock->table[n][i][j] = '@';
	}

	//2
	n = 2;
	for (i = 0; i < clock->height / 2; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height / 2 - 1 || j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}
	for (i--; i < clock->height; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height - 1 || j == 0) {
				clock->table[n][i][j] = '@';
			}
		}
	}

	//3
	n = 3;
	for (i = 0; i < clock->height / 2; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height / 2 - 1 || j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}
	for (i--; i < clock->height; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height - 1 || j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}

	//4
	n = 4;
	for (i = 0; i < clock->height / 2; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == clock->height / 2 - 1 || j == 0 || j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}
	for (i--; i < clock->height; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}

	//5
	n = 5;
	for (i = 0; i < clock->height / 2; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height / 2 - 1 || j == 0) {
				clock->table[n][i][j] = '@';
			}
		}
	}
	for (i--; i < clock->height; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height - 1 || j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}

	//6
	n = 6;
	for (i = 0; i < clock->height / 2; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height / 2 - 1 || j == 0) {
				clock->table[n][i][j] = '@';
			}
		}
	}
	for (i--; i < clock->height; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height - 1 || j == 0
					|| j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}

	//7
	n = 7;
	j = (clock->width - 1);
	for (i = 0; i < clock->height; i++) {
		clock->table[n][i][j] = '@';

		if (i == 0) {
			for (k = 0; k < clock->width; k++) {
				clock->table[n][i][k] = '@';
			}
		}
	}

	//8
	n = 8;
	for (i = 0; i < clock->height / 2; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height / 2 - 1 || j == 0
					|| j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}
	for (i--; i < clock->height; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height - 1 || j == 0
					|| j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}

	//9
	n = 9;
	for (i = 0; i < clock->height / 2; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height / 2 - 1 || j == 0
					|| j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}
	for (i--; i < clock->height; i++) {
		for (j = 0; j < clock->width; j++) {
			if (i == 0 || i == clock->height - 1 || j == clock->width - 1) {
				clock->table[n][i][j] = '@';
			}
		}
	}

	//:
	n = 10;
	j = (clock->width - 1) / 2;
	k = (clock->height - 1) / 2;
	p = k / 2;
	q = (k + clock->height - 1) / 2;

	clock->table[n][p][j] = '@';
	clock->table[n][p + 1][j] = '@';
	clock->table[n][q][j] = '@';
	clock->table[n][q + 1][j] = '@';
}

//print the number row of the matrix for number n
void printNum(int n, const ClockType *clock, int row) {
	int i = 0;
	for (i = 0; i < clock->width; i++) {
		printf("%c", clock->table[n][row][i]);
	}
	printf(" ");
}

//print the number row of the matrix for colon
void printColon(const ClockType *clock, int row) {
	int i = 0;
	for (i = 0; i < clock->width; i++) {
		printf("%c", clock->table[10][row][i]);
	}
	printf(" ");
}

// Print an ASCII clock showing cur_time as the time
void printClock(const time_t cur_time, const ClockType *clock) {

	//get the hour, min and second of current time
	struct tm* t = localtime(&cur_time);
	int hour = t->tm_hour;
	int min = t->tm_min;
	int second = t->tm_sec;

	//hour = 67;
	//min = 89;
	//second = 12;

	int i = 0;

	//print all numbers line by line
	for (i = 0; i < clock->height; i++) {
		if(clock->showHour){
			printNum(hour / 10, clock, i);
			printNum(hour % 10, clock, i);
			printColon(clock, i);
		}
		printNum(min / 10, clock, i);
		printNum(min % 10, clock, i);
		printColon(clock, i);
		printNum(second / 10, clock, i);
		printNum(second % 10, clock, i);
		printf("\n");
	}
}

// Free up any dynamically allocated memory in the clock
void cleanClock(ClockType *clock) {
	int i = 0, j = 0;

	//free memory space
	for (i = 0; i < 11; i++) {
		for (j = 0; j < clock->height; j++) {
			free(clock->table[i][j]);
		}
		free(clock->table[i]);
	}
	free(clock->table);
}

