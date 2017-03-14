#ifndef STRAW_UTILS_H
#define STRAW_UTILS_H

#include <stdarg.h>
#include <error.h>
#include <time.h>	  /* for clock_gettime */

void pexit(char *msg) {
  perror(msg);
  exit(1);
}

#define MILLION 1000000L
#define BILLION 1000000000L

#define rdtsc(lo, hi) __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
#define hilo2llu(lo, hi) ((unsigned long long)lo) | (((unsigned long long)hi) << 32)

// UNHOLY MACROS FOLLOW
#define get_elapsed_cycles(result, args...) \
  do { \
    unsigned start_lo, start_hi, end_lo, end_hi; \
    rdtsc(start_lo, start_hi); \
    args \
    rdtsc(end_lo, end_hi); \
    unsigned long long start = hilo2llu(start_lo, start_hi); \
    unsigned long long end = hilo2llu(end_lo, end_hi); \
    result = end - start; \
  } while (0)

#define get_elapsed_time(result, args...) \
  do { \
    struct timespec start, end;\
    clock_gettime(CLOCK_MONOTONIC, &start); \
    args \
    clock_gettime(CLOCK_MONOTONIC, &end); \
    result = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; \
  } while (0)

#endif /* STRAW_UTILS_H */
