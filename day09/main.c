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
  part1(inputLines);
  part2(inputLines);
  free(inputLines);
  return 0;
}

void part1(char** input) {
  
}

void part2(char** input) {
  
}