#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp = fopen("input.txt", "r");
  if (!fp) {
    return -1;
  }

  char *line = NULL;
  size_t size = 0;
  ssize_t nread;

  int lock = 50;
  int zero_count = 0;

  while ((nread = getline(&line, &size, fp)) != -1) {
    char rot = line[0];
    int amount = atoi(&line[1]);

    if (rot == 'L') {
      amount *= -1;
    }

    int prev = lock;
    lock += amount;
    while (lock > 100) {
      lock -= 100;
      zero_count++;
    }
    if (prev == 0) {
      lock += 100;
    }
    while (lock < 0) {
      lock += 100;
      zero_count++;
    }
    lock %= 100;
    if (lock == 0) {
      zero_count++;
    }
  }

  free(line);
  fclose(fp);
  printf("zero: %d", zero_count);
}
