#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>

typedef struct {
	char ***table;//table contains 11 matrix, 0-9 for numbers and 10 for colon
	int width;//width of number matrix
	int height;//height of number matrix
	int showHour;//show hour or not
} ClockType;

// Initialize the clock data structure
void initClock( ClockType *clock );

// Print an ASCII clock showing cur_time as the time
void printClock( const time_t cur_time, const ClockType *clock );

// Free up any dynamically allocated memory in the clock
void cleanClock( ClockType *clock);


// Initialize the timer with the user-provided input
void initTimer(ClockType *clock, int minutes, int seconds);

// Run the timer -- print out the time each second
void runTimer();

// Clean up memory (as needed)
void cleanTimer(ClockType  *clock);

#endif /* TIMER_H_ */
