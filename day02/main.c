#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util/util.h"

const int lines = 1000;
const int lineLength = 11;

int main() {
  char** inputLines = mallocStringArray(lines, lineLength);
  loadInput("input.txt", lineLength, inputLines);
  //part1(inputLines);
  part2(inputLines);
  // this is a leak lol
  free(inputLines);
  return 0;
}

void part1(char** input) {
  int depth = 0;
  int distance = 0;

  for (int i = 0; i < lines; i++) {
    char direction[10];
    int value;
    sscanf(input[i], "%s %d", direction, &value);
    if (strcmp(direction, "forward") == 0) {
      distance += value;
    } else if (strcmp(direction, "up") == 0) {
      depth -= value;
    } else if (strcmp(direction, "down") == 0) {
      depth += value;
    }
  }

  int result = depth * distance;
  printf("result: %d\n", result);
}

void part2(char** input) {
  int depth = 0;
  int distance = 0;
  int aim = 0;

  for (int i = 0; i < lines; i++) {
    char direction[10];
    int value;
    sscanf(input[i], "%s %d", direction, &value);
    if (strcmp(direction, "forward") == 0) {
      distance += value;
      depth += aim * value;
    } else if (strcmp(direction, "up") == 0) {
      aim -= value;
    } else if (strcmp(direction, "down") == 0) {
      aim += value;
    }
  }

  int result = depth * distance;
  printf("result: %d\n", result);
}