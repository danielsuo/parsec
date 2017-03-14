#ifndef STRAW_ARGS_H
#define STRAW_ARGS_H

#include <stdio.h>  /* for printf */
#include <unistd.h> /* for getopt */

#include "utils.h"

struct straw_args {
  unsigned short numThreads;
  unsigned int workingSetSize;
};

typedef struct straw_args STRAW_ARGS;

void usage() {
  printf("Usage: ./straw [options...]\n");
  printf("Options:\n");
  printf(" -n\tNumber of threads to use\n");
  printf(" -w\tWorking set size in bytes\n");
  exit(1);
}

STRAW_ARGS *init_args() {
  STRAW_ARGS *args;
  if ((args = (STRAW_ARGS *)malloc(sizeof(STRAW_ARGS))) == NULL) {
    pexit("ERROR: failed to malloc STRAW_ARGS");
  }

  return args;
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
      if ((args->numThreads = atoi(optarg)) < 1) {
        usage();
      }
      printf("Num threads: %d\n", args->numThreads);
      break;
    default:
      printf("Unrecognized option!\n");
      usage();
      break;
    }
  }

  // TODO: required parameters
  // if (numThreads == 0) {
  //   usage();
  // }

  return args;
}

#endif /* STRAW_ARGS_H */
