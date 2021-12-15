#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../util/util.h"

const int inputWidth = 100;
const int inputHeight = 100;
const int totalWidth = 500;
const int totalHeight = 500;
const int lines = inputHeight;
const int lineLength = inputWidth + 2;
const int startIndex = 0;
const int goal = totalWidth * totalHeight - 1;

int main() {
  int* inputLines = malloc(sizeof(int) * inputWidth * inputHeight);
  loadInputIntArray1D("input.txt", lines, lineLength, inputLines);
  //part1(inputLines, inputWidth, inputHeight);
  part2(inputLines);
  return 0;
}

int h(int i, int width) { return abs(itox(goal, width) - itox(i, width)) + abs(itoy(goal, width) - itoy(i, width)); }

int compareNode(const void* a, const void* b) {
  Node* aNode = *((Node**)a);
  Node* bNode = *((Node**)b);
  int aCost = aNode->cost + h(aNode->index, totalWidth);
  int bCost = bNode->cost + h(bNode->index, totalWidth);
  int comp = compareDecreasing(&aCost, &bCost);
  return comp;
}

Node* createNode(int index, int cost) {
  Node* node = malloc(sizeof(Node));
  node->index = index;
  node->cost = cost;
  return node;
}

void part1(int* input, int width, int height) {
  int* cameFrom = malloc(sizeof(int) * width * height);
  int* inToExplore = calloc(sizeof(int), width * height);
  int* cameFromCost = malloc(sizeof(int) * width * height);
  for (int i = 0; i < width * height; i++) {
    cameFromCost[i] = INT_MAX;
  }
  Stack* toExplore = createStack(width * height);
  Node* start = createNode(startIndex, input[startIndex]);
  push(toExplore, start);
  while(!isEmpty(toExplore)) {
    // printf("toExplore:\n");
    // for (int i = toExplore->top; i >= 0; i--) {
    //   Node* node = (Node*)toExplore->array[i];
    //   printf("%d %d\n", node->index, node->cost);
    // }
    Node* current = pop(toExplore);
    //printf("Exploring %d\n", current->index);
    if (current->index == goal) {
      break;
    }
    inToExplore[current->index] = 0;
    int neighbours[4] = {iN(current->index, width), iE(current->index, width), iS(current->index, width, height), iW(current->index, width)};
    for (int i = 0; i < 4; i++) {
      int nIndex = neighbours[i];
      if (nIndex != -1) {
        int cost = current->cost + input[nIndex];
        //printf("Cost calc %d + %d = %d\n", current->cost, input[nIndex], cost);
        if (cost < cameFromCost[nIndex]) {
          cameFromCost[nIndex] = cost;
          cameFrom[nIndex] = current->index;
          if (!inToExplore[nIndex]) {
            //printf("Added neighbour at %d with cost %d\n", nIndex, cost);
            push(toExplore, createNode(nIndex, cost));
            inToExplore[nIndex] = 1;
          }
        }
      }
    }
    qsort(toExplore->array, toExplore->top + 1, sizeof(Node*), compareNode);
  }

  int currentIndex = goal;
  int totalRisk = 0;
  do {
    totalRisk += input[currentIndex];
    currentIndex = cameFrom[currentIndex];
  } while (currentIndex != startIndex);

  printf("result: %d\n", totalRisk);
}

void part2(int* input) {
  // Generate larger map
  int* map = malloc(sizeof(int) * totalWidth * totalHeight);
  // Copy over original map
  for (int y = 0; y < inputHeight; y++) {
    for (int x = 0; x < inputWidth; x++) {
      map[xytoi(x, y, totalWidth)] = input[xytoi(x, y, inputWidth)];
      //printf("%d", input[xytoi(x, y, inputWidth)]);
    }
    //printf("\n");
  }
  //printf("\n");
  // for (int y = 0; y < inputHeight; y++) {
  //   for (int x = 0; x < inputWidth; x++) {
  //     printf("%d", map[xytoi(x, y, totalWidth)]);
  //   }
  //   printf("\n");
  // }
  // printf("\n");
  for (int tileX = 0; tileX < 5; tileX++) {
    for (int tileY = 0; tileY < 5; tileY++) {
      if (tileX || tileY) {
        for (int y = 0; y < inputHeight; y++) {
          for (int x = 0; x < inputWidth; x++) {
            int destX = tileX * inputWidth + x;
            int destY = tileY * inputHeight + y;
            int copyTileX = tileX - 1;
            int copyTileY = tileY;
            if (!tileX) {
              copyTileX = tileX;
              copyTileY = tileY - 1;
            }
            int copyX = copyTileX * inputWidth + x;
            int copyY = copyTileY * inputHeight + y;
            map[xytoi(destX, destY, totalWidth)] = map[xytoi(copyX, copyY, totalWidth)] + 1;
            if (map[xytoi(destX, destY, totalWidth)] == 10) {
              map[xytoi(destX, destY, totalWidth)] = 1;
            }
          }
        }
      }
    }
  }

  // for (int y = 0; y < totalHeight; y++) {
  //   for (int x = 0; x < totalWidth; x++) {
  //     printf("%d", map[xytoi(x, y, totalWidth)]);
  //   }
  //   printf("\n");
  // }

  part1(map, totalWidth, totalHeight);
}