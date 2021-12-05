#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../util/util.h"

const int lines = 500;
const int lineLength = 20;
const int areaWidth = 1000;
const int areaSize = areaWidth * areaWidth;

typedef struct {
  int x,y;
} Point;

typedef struct {
  Point start;
  Point end;
} Line;

int main() {
  char** inputLines = mallocStringArray(lines, lineLength);
  loadInput("input.txt", lineLength, inputLines);
  part1(inputLines); // commend out lines 57 and 59 for part 2
  free(inputLines);
  return 0;
}

int xytoi(int x, int y) { return y * areaWidth + x; }

void drawLine(Line line, int* area) {
  Point delta = {line.end.x - line.start.x, line.end.y - line.start.y};
  delta.x = (delta.x > 0) - (delta.x < 0);
  delta.y = (delta.y > 0) - (delta.y < 0);
  //printf("Drawing line %d,%d -> %d,%d with delta %d,%d\n", line.start.x, line.start.y, line.end.x, line.end.y, delta.x, delta.y);
  Point draw = {line.start.x, line.start.y};
  while (1) {
    //printf("Draw point: %d, %d\n", draw.x, draw.y);
    area[xytoi(draw.x, draw.y)]++;

    if (draw.x == line.end.x && draw.y == line.end.y) {
      break;
    }

    draw.x += delta.x;
    draw.y += delta.y;
  }
}

void part1(char** input) {
  int* area = calloc(sizeof(int), areaSize);
  for (int i = 0; i < lines; i++) {
    Line line;
    sscanf(input[i], "%d,%d -> %d,%d", &line.start.x, &line.start.y, &line.end.x, &line.end.y);
    //if (line.start.x == line.end.x || line.start.y == line.end.y) {
      drawLine(line, area);
    //}
  }
  int linesCount = 0;
  for (int i = 0; i < areaSize; i++) {
    if (area[i] > 1) {
      linesCount++;
    }
  }

  printf("result: %d\n", linesCount);
}

void part2(char** input) {
  
}