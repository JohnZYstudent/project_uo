#ifndef CLOCK_H_
#define CLOCK_H_

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

#endif /* CLOCK_H_ */
