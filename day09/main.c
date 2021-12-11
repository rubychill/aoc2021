#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util/util.h"

const int height = 100;
const int width = 100;
const int lineLength = width + 2;

int main() {
  int** inputLines = mallocIntArray(height, lineLength);
  loadInputIntArray("input.txt", height, lineLength, inputLines);
  //part1(inputLines);
  part2(inputLines);
  return 0;
}

void part1(int** input) {
  int risk = 0;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int pointHeight = input[y][x];
      int leftCheck = x == 0 || pointHeight < input[y][x-1];
      int rightCheck = x == width - 1 || pointHeight < input[y][x+1];
      int upCheck = y == 0 || pointHeight < input[y-1][x];
      int downCheck = y == height - 1 || pointHeight < input[y+1][x];
      if (leftCheck && rightCheck && upCheck && downCheck) {
        risk += pointHeight + 1;
      }
    }
  }

  printf("result: %d\n", risk);
}

int itox(int i) { return i % width; }
int itoy(int i) { return i / width; }
int xytoi(int x, int y) { return y * width + x; }
int iup(int i) { if (itoy(i) == 0) return -1; return i - width; }
int idown(int i) { if (itoy(i) == height - 1) return -1; return i + width; }
int ileft(int i) { if (itox(i) == 0) return -1; return i - 1; }
int iright(int i) { if (itox(i) == width - 1) return -1; return i + 1; }

void checkAddBasin(int** input, int i, Stack* explore, int* pointUsed) {
  if (i != -1 && pointUsed[i] == 0 && input[itoy(i)][itox(i)] != 9) {
    push(explore, i);
    pointUsed[i] = 1;
  }
}

void part2(int** input) {
  int* lowPoints = calloc(sizeof(int), 0);
  int lowPointsCount = 0;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int pointHeight = input[y][x];
      int leftCheck = x == 0 || pointHeight < input[y][x-1];
      int rightCheck = x == width - 1 || pointHeight < input[y][x+1];
      int upCheck = y == 0 || pointHeight < input[y-1][x];
      int downCheck = y == height - 1 || pointHeight < input[y+1][x];
      if (leftCheck && rightCheck && upCheck && downCheck) {
        lowPointsCount++;
        lowPoints = realloc(lowPoints, sizeof(int) * lowPointsCount);
        lowPoints[lowPointsCount - 1] = xytoi(x, y);
      }
    }
  }

  int basinSizes[lowPointsCount];
  struct Stack* explore = createStack(height * width);
  int* pointUsed = calloc(sizeof(int), height * width);
  for (int i = 0; i < lowPointsCount; i++) {
    basinSizes[i] = 0;
    //printf("starting basin %d\n", lowPoints[i]);
    push(explore, lowPoints[i]);
    pointUsed[lowPoints[i]] = 1;
    //printf("---\n");
    while (!isEmpty(explore)) {
      int point = pop(explore);
      basinSizes[i]++;
      checkAddBasin(input, iup(point), explore, pointUsed);
      checkAddBasin(input, idown(point), explore, pointUsed);
      checkAddBasin(input, ileft(point), explore, pointUsed);
      checkAddBasin(input, iright(point), explore, pointUsed);
    }
    //printf("--- final size: %d\n", basinSizes[i]);
  }

  qsort(basinSizes, lowPointsCount, sizeof(int), compare);
  //printf("%d %d %d\n", basinSizes[lowPointsCount - 1], basinSizes[lowPointsCount - 2], basinSizes[lowPointsCount - 3]);

  long result = (long)basinSizes[lowPointsCount - 1] * (long)basinSizes[lowPointsCount - 2] * (long)basinSizes[lowPointsCount - 3];
  printf("result: %ld\n", result);
}