#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util/util.h"

const int height = 10;
const int width = 10;
const int totalSize = height * width;
const int lineLength = width + 2;
const int steps = 100;

int main() {
  int* inputLines = malloc(sizeof(int) * height * lineLength);
  loadInputIntArray1D("input.txt", height, lineLength, inputLines);
  //part1(inputLines);
  part2(inputLines);
  free(inputLines);
  return 0;
}

int itox(int i) { return i % width; }
int itoy(int i) { return i / width; }
int xytoi(int x, int y) { return y * width + x; }
int iN(int i) { if (itoy(i) == 0) return -1; return i - width; }
int iS(int i) { if (itoy(i) == height - 1) return -1; return i + width; }
int iW(int i) { if (itox(i) == 0) return -1; return i - 1; }
int iE(int i) { if (itox(i) == width - 1) return -1; return i + 1; }
int iNE(int i) { if (itox(i) == width -1 || itoy(i) == 0) return -1; return iN(iE(i)); }
int iNW(int i) { if (itox(i) == 0 || itoy(i) == 0) return -1; return iN(iW(i)); }
int iSE(int i) { if (itox(i) == width -1 || itoy(i) == height - 1) return -1; return iS(iE(i)); }
int iSW(int i) { if (itox(i) == 0 || itoy(i) == height - 1) return -1; return iS(iW(i)); }

void printInput(int* input) {
  for (int i = 0; i < totalSize; i++) {
    if (i % width == 0) {
      printf("\n");
    }
    printf("%d", input[i]);
  }
  printf("\n\n");
}

void part1(int* input) {
  int flashes = 0;
  //printInput(input);
  for (int step = 0; step < steps; step++) {
    // Add 1 to all octos
    for (int i = 0; i < totalSize; i++) {
      input[i]++;
    }

    // Keep iterating through input until no more flashes happen
    int iterFlashes = 0;
    
    do {
      iterFlashes = 0;
      for (int i = 0; i < totalSize; i++) {
        if (input[i] != -1) {
          int indexFlashes = input[i] / 10;
          if (indexFlashes > 0) {
            // Set to -1 when flashed to prevent additional energy
            input[i] = -1;
            iterFlashes++;
            if (iN(i) != -1 && input[iN(i)] != -1) input[iN(i)]++;
            if (iNE(i) != -1 && input[iNE(i)] != -1) input[iNE(i)]++;
            if (iE(i) != -1 && input[iE(i)] != -1) input[iE(i)]++;
            if (iSE(i) != -1 && input[iSE(i)] != -1) input[iSE(i)]++;
            if (iS(i) != -1 && input[iS(i)] != -1) input[iS(i)]++;
            if (iSW(i) != -1 && input[iSW(i)] != -1) input[iSW(i)]++;
            if (iW(i) != -1 && input[iW(i)] != -1) input[iW(i)]++;
            if (iNW(i) != -1 && input[iNW(i)] != -1) input[iNW(i)]++;
          }
        }
      }
      flashes += iterFlashes;
    } while (iterFlashes != 0);
    // Set all -1 values to 0
    for (int i = 0; i < totalSize; i++) {
      if (input[i] == -1) {
        input[i] = 0;
      }
    }
  }

  printf("result: %d\n", flashes);
}

void part2(int* input) {
  int flashes = 0;
  //printInput(input);
  for (int step = 0; 1; step++) {
    // Add 1 to all octos
    for (int i = 0; i < totalSize; i++) {
      input[i]++;
    }

    // Keep iterating through input until no more flashes happen
    int iterFlashes = 0;
    do {
      iterFlashes = 0;
      for (int i = 0; i < totalSize; i++) {
        if (input[i] != -1) {
          int indexFlashes = input[i] / 10;
          if (indexFlashes > 0) {
            // Set to -1 when flashed to prevent additional energy
            input[i] = -1;
            iterFlashes++;
            if (iN(i) != -1 && input[iN(i)] != -1) input[iN(i)]++;
            if (iNE(i) != -1 && input[iNE(i)] != -1) input[iNE(i)]++;
            if (iE(i) != -1 && input[iE(i)] != -1) input[iE(i)]++;
            if (iSE(i) != -1 && input[iSE(i)] != -1) input[iSE(i)]++;
            if (iS(i) != -1 && input[iS(i)] != -1) input[iS(i)]++;
            if (iSW(i) != -1 && input[iSW(i)] != -1) input[iSW(i)]++;
            if (iW(i) != -1 && input[iW(i)] != -1) input[iW(i)]++;
            if (iNW(i) != -1 && input[iNW(i)] != -1) input[iNW(i)]++;
          }
        }
      }
      flashes += iterFlashes;
    } while (iterFlashes != 0);
    // Set all -1 values to 0
    int stepFlashes = 0;
    for (int i = 0; i < totalSize; i++) {
      if (input[i] == -1) {
        input[i] = 0;
        stepFlashes++;
      }
    }
    if (stepFlashes == totalSize) {
      printf("part 2 result: %d\n", step + 1);
      break;
    }
  }
}