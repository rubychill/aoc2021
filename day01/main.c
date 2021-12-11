#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util/util.h"

const int lines = 2000;
const int lineLength = 6;

int main() {
  int* depths = malloc(sizeof(int)*lines);
  loadInputInts("input.txt", lines, lineLength, depths);
  //part1(depths);
  part2(depths);
  free(depths);
  return 0;
}

void part1(int* depths) {
  int previous = -1;
  int increases = 0;
  for (int i = 0; i < lines; i++) {
    int depth = depths[i];
    if (previous != -1 && depth > previous) {
      increases++;
    }
    previous = depth;
  }

  printf("result: %d\n", increases);
}

void part2(int* depths) {
  int groupSize = 3;
  int groupLines = lines - (groupSize - 1);

  int* groupDepths = malloc(sizeof(int) * groupLines);
  for (int i = 0; i < groupLines; i++) {
    int sum = 0;
    for (int j = 0; j < groupSize; j++) {
      sum += depths[i+j];
    }
    groupDepths[i] = sum;
  }

  part1(groupDepths);

  free(groupDepths);
}