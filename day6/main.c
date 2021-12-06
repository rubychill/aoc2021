#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util/util.h"

const int lines = 300;
const int lineLength = 3;
const int solutionDays = 256;
const int firstDays = 8;
const int resetDays = 6;
const int totalDays = solutionDays + firstDays - 3;

typedef struct tNode {
  int value;
  struct tNode* next;
} Node;

int main() {
  int* inputLines = malloc(sizeof(int) * lines);
  loadInputInts("input.txt", lines, lineLength, inputLines);
  //part1(inputLines);
  part2(inputLines);
  free(inputLines);
  return 0;
}

long solution(int* input, int solutionDays) {
  long* buckets = calloc(sizeof(long), firstDays + 1);
  for (int i = 0; i < lines; i++) {
    int value = input[i];
    buckets[value]++;
  }
  for (int day = 0; day < solutionDays; day++) {
    long temp = 0;
    for (int i = firstDays; i >= 0; i--) {
      long value = buckets[i];
      buckets[i] = temp;
      temp = value;
      if (i == 0) {
        buckets[resetDays] += value;
        buckets[firstDays] += value;
      }
    }
  }

  long result = 0;
  for (int i = 0; i < firstDays + 1; i++) {
    result += buckets[i];
  }
  return result;
}

void part1(int* input) {
  int finalFishCount[resetDays];
  Node firstFish = {resetDays, NULL};
  Node* lastFish = &firstFish;
  int fishCount = 1;

  for (int day = 0; day < totalDays; day++) {
    Node* fish  = &firstFish;
    while (fish != NULL) {
      if (fish->value == 0) {
        fish->value = resetDays;
        // add new fish
        Node* newFish = malloc(sizeof(Node));
        newFish->value = firstDays;
        newFish->next = NULL;
        lastFish->next = newFish;
        lastFish = newFish;
        fishCount++;
      } else {
        fish->value -= 1;
      }
      fish = fish->next;
    }
    if (day - solutionDays + 1 >= 0) {
      //printf("final fish count day %d index %d value %d\n", day, resetDays - (day - solutionDays + 1), fishCount);
      finalFishCount[resetDays - (day - solutionDays + 1)] = fishCount;
    }
  }
  
  int totalFish = 0;
  for (int i = 0; i < lines; i++) {
    totalFish += finalFishCount[input[i]];
  }
  printf("result: %d\n", totalFish);
}

void part2(int* input) {
  printf("result: %ld\n", solution(input, 256));
}