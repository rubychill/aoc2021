#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../util/util.h"
#include "../util/cute_coroutine.h"

const int lines = 2000;
const int lineLength = 6;
// const int lines = 10;
// const int lineLength = 5;

int main() {
  int* depths = malloc(sizeof(int)*lines);
  loadInputInts("input.txt", lines, lineLength, depths);
  //part1(depths);
  //part2(depths);
  part1co(depths);
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

void part1co(int* depths) {
  coroutine_t co;
  coroutine_init(&co);

  int* result = calloc(sizeof(int), 1);
  int donePercent = 0;
  while(donePercent < 100) {
    donePercent = doPart1(&co, depths, result);
    printf("done: %d\n", donePercent);
  }
  printf("result: %d\n", *result);
}

int doPart1(coroutine_t* co, int* depths, int* result) {
  int* previousPtr = (int*)coroutine_local_var(co, sizeof(int));
  int* increasesPtr = (int*)coroutine_local_var(co, sizeof(int));
  int* donePercentPtr = (int*)coroutine_local_var(co, sizeof(int));
  int previous = *previousPtr;
  int increases = *increasesPtr;
  int donePercent = *donePercentPtr;
  COROUTINE_START(co);
  previous = -1;
  increases = 0;

  for (int i = 0; i < lines; i++) {
    int depth = depths[i];
    if (previous != -1 && depth > previous) {
      increases++;
    }
    previous = depth;
    donePercent = ((i + 1) * 100) / lines;
    if (donePercent < 100) {
      COROUTINE_YIELD(co);
    }
  }

  *result = increases;

  COROUTINE_END(co);
  *previousPtr = previous;
  *increasesPtr = increases;
  *donePercentPtr = donePercent;
  return donePercent;
}