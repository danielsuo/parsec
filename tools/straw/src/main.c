#include <stdio.h>  /* for printf */
#include <stdlib.h> /* for exit */
#include <unistd.h> /* for getopt */

int main(int argc, char **argv) {

  int opt;
  int a;

  while ((opt = getopt(argc, argv, "a:b")) != -1) {
    switch (opt) {
    case 'a':
      a = atoi(optarg);
      printf("option a %d\n", a);
      break;
    case 'b':
      printf("option b\n");
      break;
    }
  }
}
