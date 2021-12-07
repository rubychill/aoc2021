#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "../util/util.h"

const int lines = 1000;
const int lineLength = 6;

int main() {
  int* inputLines =malloc(sizeof(int) * lines);
  loadInputInts("input.txt", lines, lineLength, inputLines);
  part1(inputLines);
  //part2(inputLines); // toggle comment in line 43/44 for part 2
  free(inputLines);
  return 0;
}

void part1(int* input) {
  int min = input[0];
  int max = input[0];
  for (int i = 0; i < lines; i++) {
    int value = input[i];
    if (value < min) {
      min = value;
    }
    if (value > max) {
      max = value;
    }
  }

  int minPosition = min;
  int minFuel = INT_MAX;
  for (int position = min; position < max + 1; position++) {
    int fuel = 0;
    for (int i = 0; i < lines; i++) {
      int n = abs(input[i] - position);
      // toggle the below line comment for part 2
      // fuel += n; // part 1
      fuel += n * (n + 1)/2; // part 2
    }
    if (fuel < minFuel) {
      minPosition = position;
      minFuel = fuel;
    }
  }

  printf("result: %d\n", minFuel);
}

void part2(int* input) {
  
}