#include <stdint.h> /* for uint64 definition */
#include <stdlib.h> /* for exit */


#include <pthread.h>

#include "args.h"
// #include "utils.h"

#define BILLION 1000000000L

void test(void *data);

void inline test(void *data) {
  // unsigned long long a, b;
  // a = rdtsc();
  // b = rdtsc() - a;
  // printf("Hello, world! %llu\n", b);
}

int main(int argc, char **argv) {

  STRAW_ARGS *args = get_args(argc, argv);

  // uint64_t diff;
	// struct timespec start, end;
	// int i;
  //
  // /* measure monotonic time */
	// clock_gettime(CLOCK_MONOTONIC, &start);	/* mark start time */
	// // sleep(1);	/* do stuff */
	// clock_gettime(CLOCK_MONOTONIC, &end);	/* mark the end time */
  //
	// diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	// printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
  //
	// /* now re-do this and measure CPU time */
	// /* the time spent sleeping will not count (but there is a bit of overhead */
	// clock_gettime(CLOCK_REALTIME, &start);	/* mark start time */
	// // sleep(1);	/* do stuff */
	// clock_gettime(CLOCK_REALTIME, &end);		/* mark the end time */
  //
	// diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	// printf("elapsed process CPU time = %llu nanoseconds\n", (long long unsigned int) diff);

  // unsigned long long a;
  // a = get_clock_cycles(test, NULL);

  uint64_t a;
  get_elapsed_cycles(a,
    int x = 4;
    int y = 4 + x;
    printf("x, y: %d, %d\n", x, y);
  );
  printf("cycles: %llu\n", a);

  get_elapsed_time(a);
  printf("time: %llu\n", a);

  destroy_args(args);
	exit(0);
}
