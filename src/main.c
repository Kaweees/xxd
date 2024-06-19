#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// #include "xxd.h"

#define USAGE_STRING  "Usage: %s [ infile ]\n" /* Program usage string */
#define MIN_ARGS      1
#define MAX_ARGS      2
#define SYSCALL_ERROR -1

/**
 * Prints the proper usage of the program and exits unsuccessfully.
 */
void usage(char* prog_name) {
  fprintf(stderr, USAGE_STRING, prog_name);
  exit(EXIT_FAILURE);
}

/**
 * @brief Program entry point
 *
 * @param argc - the number of command line arguments
 * @param argv - an array of command line arguments
 * @return int - the exit status
 */

int main(int argc, char* argv[]) {
  FILE* file = fopen("Makefile", "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  printf("yass");
  char line_buffer[16];
  uint64_t total_read = 0;
  uint64_t bytes_read = 0;
  while ((bytes_read = fread(
              line_buffer, sizeof(char), sizeof(line_buffer), file)) != 0) {
    printf("%08lx: ", total_read);
    for (int i = 0; i < sizeof(line_buffer); i++) {
      if (bytes_read > i) {
        printf("%02x", line_buffer[i]);

      } else {
        printf("  ");
      }
      if (!(i % 2 == 0)) {
        printf(" ");
      }
    }
    printf(" ");
    for (int i = 0; i < bytes_read; i++) {
      if (line_buffer[i] == '\n' || line_buffer[i] == ' ' ||
          line_buffer[i] == '\t') {
        printf(".");
      } else {
        printf("%c", line_buffer[i]);
      }
    }
    printf("\n");
    total_read += sizeof(line_buffer);
  }
}

/*
        if (argc == MIN_ARGS) {
    kiwish(STDIN_FILENO, STDOUT_FILENO);
  } else if (argc == MAX_ARGS) {
    int infile = open(*(argv + 1), O_RDONLY, S_IRWXU);
    if (infile == SYSCALL_ERROR) {
      perror("Error opening file");
      exit(EXIT_FAILURE);
    }
    kiwish(infile, STDOUT_FILENO);
    close(infile);
  } else {
    usage(*argv);
  }
  return EXIT_SUCCESS;
}
*/
