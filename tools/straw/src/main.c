#include <pthread.h>

#include "args.h"

void *test(void *data) {
  spin(BILLION * 10);
}

int main(int argc, char **argv) {

  STRAW_ARGS *args = get_args(argc, argv);
  print_args(args);

  // uint64_t a;
  // get_elapsed_cycles(a,
  //   int x = 4;
  //   int y = 4 + x;
  //   printf("x, y: %d, %d\n", x, y);
  // );
  // printf("cycles: %lu\n", a);
  //
  // get_elapsed_time(a);
  // printf("time: %lu\n", a);

  for (int i = 0; i < args->numThreads; i++) {
    pthread_t thread;
    if (pthread_create(&thread, NULL, test, NULL) != 0) {
      pexit("ERROR: failed to create thread");
    }
  }


  destroy_args(args);
  pthread_exit(0);
	// exit(0);
}
