#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../util/util.h"

const int lines = 1000;
const int lineLength = 14;
const int places = 12;

int main() {
  int* input = malloc(sizeof(int) * lines);
  loadInputsBase("input.txt", lines, lineLength, input, 2);
  //part1(input);
  part2(input);
  free(input);
  return 0;
}

int getBits(int* input, int inputSize, bool getMost) {
  int bits = 0;

  for (int pow = 0; pow < places; pow++) {
    int comp = 1 << pow;
    int oneCount = 0;
    for (int i = 0; i < inputSize; i++) {
      oneCount += (input[i] & comp) >> pow;
    }
    int halfInputSize = (inputSize + 2 - 1) / 2;
    if ((oneCount >= halfInputSize && getMost) || (oneCount < halfInputSize && !getMost)) {
      bits += 1 << pow;
    }
  }

  return bits;
}

void part1(int* input) {
  int gamma = getBits(input, lines, true);
  int epsilon = ~gamma & 0xFFF;

  printf("result: %d\n", gamma * epsilon);
}


int findMatch(int* input, int inputSize, int pow, bool getMost) {
  int bits = getBits(input, inputSize, getMost);
  int* remainder = malloc(sizeof(int) * inputSize);
  int remainderSize = 0;
  int comp = 1 << pow;
  int bit = bits & comp;
  for (int i = 0; i < inputSize; i++) {
    if ((input[i] & comp) == bit) {
      remainder[remainderSize] = input[i];
      remainderSize++;
    }
  }
  if (remainderSize == 1 || pow == 0) {
    int result = remainder[0];
    free(remainder);
    return result;
  } else {
    free(input);
    return findMatch(remainder, remainderSize, pow - 1, getMost);
  }
}

void part2(int* input) {
  int* oxygenInput = malloc(sizeof(int) * lines);
  int* co2Input = malloc(sizeof(int) * lines);
  memcpy(oxygenInput, input, sizeof(int) * lines);
  memcpy(co2Input, input, sizeof(int) * lines);
  int oxygen = findMatch(oxygenInput, lines, places - 1, true);
  int co2 = findMatch(co2Input, lines, places - 1, false);

  // int result = findMatch(input, oxygen) * findMatch(input, co2);
  int result = oxygen * co2;
  printf("result: %d\n", result);
}