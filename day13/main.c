#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util/util.h"

const int lines = 916;
const int lineLength = 11;
const int numFolds = 12;
const int foldLineLength = 7;

int itox(int i, int width) { return i % width; }
int itoy(int i, int width) { return i / width; }
int xytoi(int x, int y, int width) { return y * width + x; }

int main() {
  char** inputLines = mallocStringArray(lines, lineLength);
  char** foldsLines = mallocStringArray(numFolds, foldLineLength);
  loadInput("input.txt", lineLength, inputLines);
  loadInput("folds.txt", foldLineLength, foldsLines);
  //part1(inputLines, foldsLines);
  part2(inputLines, foldsLines);
  return 0;
}

void part1(char** input, char** folds) {
  int paperWidth = 2000;
  int paperHeight = 2000;
  int* paper = calloc(sizeof(int), paperWidth * paperHeight);
  char foldDir;
  int foldAmount;
  sscanf(folds[0], "%c=%d", &foldDir, &foldAmount);
  if (foldDir == 'x') {
    paperWidth = foldAmount;
  }
  for (int i = 0; i < lines; i++) {
    int x;
    int y;
    sscanf(input[i], "%d,%d", &x, &y);
    if (foldDir == 'x' && x > foldAmount) {
      x = 2 * foldAmount - x;
    } else if (foldDir == 'y' && y > foldAmount) {
      y = 2 * foldAmount - y;
    }
    paper[xytoi(x, y, paperWidth)]++;
  }

  int count = 0;
  for (int i = 0; i < paperWidth * paperHeight; i++) {
    if (paper[i] > 0) {
      count++;
    }
  }

  printf("\nresult: %d\n", count);
}

void part2(char** input, char** folds) {
  int paperWidth = 2000;
  int paperHeight = 2000;
  for (int fold = 0; fold < numFolds; fold++) {
    char foldDir;
    int foldAmount;
    sscanf(folds[fold], "%c=%d", &foldDir, &foldAmount);
    if (foldDir == 'x' && foldAmount < paperWidth) {
      paperWidth = foldAmount;
    }
    if (foldDir == 'y' && foldAmount < paperHeight) {
      paperHeight = foldAmount;
    }
  }
  int* paper = calloc(sizeof(int), paperWidth * paperHeight);

  for (int i = 0; i < lines; i++) {
    int x;
    int y;
    sscanf(input[i], "%d,%d", &x, &y);
    for (int fold = 0; fold < numFolds; fold++) {
      char foldDir;
      int foldAmount;
      sscanf(folds[fold], "%c=%d", &foldDir, &foldAmount);
      if (foldDir == 'x' && x > foldAmount) {
        x = 2 * foldAmount - x;
      } else if (foldDir == 'y' && y > foldAmount) {
        y = 2 * foldAmount - y;
      }
    }
    paper[xytoi(x, y, paperWidth)]++;
  }

  int count = 0;
  for (int i = 0; i < paperWidth * paperHeight; i++) {
    if (i % paperWidth == 0) {
      printf("\n");
    }
    if (paper[i] > 0) {
      printf("#");
    } else {
      printf(" ");
    }
    if (paper[i] > 0) {
      count++;
    }
  }

  printf("\nresult: %d\n", count);
}