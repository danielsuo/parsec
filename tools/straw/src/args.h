#ifndef STRAW_ARGS_H
#define STRAW_ARGS_H

#include <stdio.h>  /* for printf */
#include <unistd.h> /* for getopt */

#include "utils.h"

#define set_int_opt(opt, arg) if ((opt = atoi(arg)) < 1) usage();

struct straw_args {
  unsigned short numThreads;
  unsigned int workingSetSize;
  unsigned short objectSize;
};

typedef struct straw_args STRAW_ARGS;

void usage() {
  printf("Usage: ./straw [options...]\n");
  printf("Options:\n");
  printf(" -n\tNumber of threads to use\n");
  printf(" -w\tWorking set size in bytes\n");
  printf(" -o\tOjbect size in bytes\n");
  exit(1);
}

STRAW_ARGS *init_args() {
  STRAW_ARGS *args;
  if ((args = (STRAW_ARGS *)malloc(sizeof(STRAW_ARGS))) == NULL) {
    pexit("ERROR: failed to malloc STRAW_ARGS");
  }

  args->numThreads = 1;
  args->workingSetSize = 1024;
  args->objectSize = 64;

  return args;
}

void print_args(STRAW_ARGS *args) {
  printf("Arguments:\n");
  printf(" numThreads      %d\n", args->numThreads);
  printf(" workingSetSize  %d\n", args->workingSetSize);
  printf(" objectSize      %d\n", args->objectSize);
}

void destroy_args(STRAW_ARGS *args) {
  free(args);
}

STRAW_ARGS *get_args(int argc, char **argv) {
  STRAW_ARGS *args = init_args();
  char opt;

  while ((opt = getopt(argc, argv, "n:")) != -1) {
    switch (opt) {
    case 'n':
      set_int_opt(args->numThreads, optarg);
      break;
    default:
      printf("Unrecognized option!\n");
      usage();
      break;
    }
  }

  return args;
}

#endif /* STRAW_ARGS_H */
