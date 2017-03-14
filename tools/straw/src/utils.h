#ifndef STRAW_UTILS_H
#define STRAW_UTILS_H

#include <time.h>	  /* for clock_gettime */
#include <error.h>
#include <stdlib.h> /* for exit */
#include <stdarg.h>
#include <inttypes.h>

#define MILLION 1000000L
#define BILLION 1000000000L

#define rdtsc(lo, hi) __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
#define hilo2llu(lo, hi) ((unsigned long long)lo) | (((unsigned long long)hi) << 32)
#define timediff(a, b) BILLION * (b.tv_sec - a.tv_sec) + b.tv_nsec - a.tv_nsec

// UNHOLY MACROS FOLLOW
#define get_elapsed_cycles(result, args...) \
  do { \
    uint32_t start_lo, start_hi, end_lo, end_hi; \
    rdtsc(start_lo, start_hi); \
    args \
    rdtsc(end_lo, end_hi); \
    uint64_t start = hilo2llu(start_lo, start_hi); \
    uint64_t end = hilo2llu(end_lo, end_hi); \
    result = end - start; \
  } while (0)

#define get_elapsed_time(result, args...) \
  do { \
    struct timespec start, end;\
    clock_gettime(CLOCK_MONOTONIC, &start); \
    args \
    clock_gettime(CLOCK_MONOTONIC, &end); \
    result = timediff(start, end); \
  } while (0)

void pexit(char *msg) {
  perror(msg);
  exit(1);
}

void spin(uint64_t ns) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  end = start;

  while (timediff(start, end) < ns) {
    clock_gettime(CLOCK_MONOTONIC, &end);
  }
}

#endif /* STRAW_UTILS_H */
