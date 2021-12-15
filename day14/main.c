#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util/util.h"

const int lines = 100;
const int lineLength = 9;
const char* start = "KFFNFNNBCNOBCNPFVKCP";
const int steps = 40;

int main() {
  char** inputLines = mallocStringArray(lines, lineLength);
  loadInput("pairs.txt", lineLength, inputLines);
  //part1(inputLines);
  part2(inputLines);
  free(inputLines);
  return 0;
}

int pairToIndex(char* s) { return (s[0] - 'A') * 100 + (s[1] - 'A'); }
char* indexToPair(int index) { return (char[]){index / 100 + 'A', index % 100 + 'A'}; }

void part1(char** input) {
  int chainSize = 20;
  char* pairMap = calloc(sizeof(char), pairToIndex("ZZ") + 1);
  for (int i = 0; i < lines; i++) {
    char pair[3];
    char mappedChar;
    sscanf(input[i], "%s -> %c", pair, &mappedChar);
    pairMap[pairToIndex(pair)] = mappedChar;
  }
  // printf("Generated pair map\n");

  List* chain = createList(chainSize);
  for (int i = 0; i < chainSize; i++) {
    lsAddTail(chain, &start[i]);
  }
  // printf("Generated initial chain\n");
  // printf("%p %c\n", ((char*)chain->array[0]), *((char*)chain->array[0]));

  for (int step = 0; step < steps; step++) {
    // printf("Step %d\n", step);
    List* newChain = lsCloneList(chain);
    // printf("Cloned chain\n");
    // printf("pointers %p %p\n", ((char*)chain->array[0]), ((char*)newChain->array[0]));
    // printf("char %c\n", *((char*)newChain->array[0]));
    chainSize = lsSize(chain) * 2;
    newChain = lsResizeList(newChain, chainSize);
    // for (int j = 0; j < lsSize(newChain); j++) {
    //   printf("%c", *((char*)lsGet(newChain, j)));
    // }
    // printf("\n");
    // printf("Created new chain\n");
    for (int i = 0; i < lsSize(chain) - 1; i++) {
      // printf("%c %c\n", *((char*)lsGet(chain, i)), *((char*)lsGet(chain, i + 1)));
      char pair[2] = {*((char*)lsGet(chain, i)), *((char*)lsGet(chain, i + 1))};
      int mappedIndex = pairToIndex(pair);
      // printf("mappedIndex: %d char: %c %p\n", mappedIndex, pairMap[mappedIndex], &pairMap[mappedIndex]);
      lsInsert(newChain, &pairMap[mappedIndex], (i * 2) + 1);
      // printf("pointers %p %p\n", &pairMap[mappedIndex], ((char*)newChain->array[0]));
      // printf("char %c %c\n", pairMap[mappedIndex], *((char*)newChain->array[0]));
      // for (int j = 0; j < lsSize(newChain); j++) {
      //   printf("%c", *((char*)lsGet(newChain, j)));
      // }
      // printf("\n");
    }
    // printf("char %c\n", *((char*)newChain->array[0]));
    // printf("Free old chain\n");
    lsFree(chain);
    chain = newChain;
  }

  printf("chain length: %d\n", lsSize(chain));

  int* count = calloc(sizeof(int), 26);
  int max = 0;
  int min = chainSize;
  for (int i = 0; i < lsSize(chain); i++) {
    printf("%c", *((char*)lsGet(chain, i)));
    count[*((char*)lsGet(chain, i)) - 'A']++;
  }
  printf("\n");
  for (int i = 0; i < 26; i++) {
    int c = count[i];
    printf("%c: %d\n", i + 'A', c);
    if (c > 0 && c < min) {
      printf("new min\n");
      min = c;
    }
    if (c > max) {
      printf("new max\n");
      max = c;
    }
  }

  printf("result: %d - %d = %d\n", max, min, max - min);
}

void part2(char** input) {
  long chainSize = 20;
  int numPairs = pairToIndex("ZZ") + 1;
  char* pairMap = calloc(sizeof(char), numPairs);
  for (int i = 0; i < lines; i++) {
    char pair[3];
    char mappedChar;
    sscanf(input[i], "%s -> %c", pair, &mappedChar);
    pairMap[pairToIndex(pair)] = mappedChar;
  }

  long* pairCount = calloc(sizeof(long), numPairs);
  for (int i = 0; i < chainSize - 1; i++) {
    char pair[2] = {start[i], start[i+1]};
    int mappedIndex = pairToIndex(pair);
    pairCount[mappedIndex]++;
  }

  for (int step = 0; step < steps; step++) {
    printf("Step %d\n", step);
    long* newPairCount = calloc(sizeof(long), numPairs);
    for (int i = 0; i < numPairs; i++) {
      long count = pairCount[i];
      if (count > 0) {
        char* pair = indexToPair(i);
        char newChar = pairMap[i];
        char leftPair[2] = {pair[0], newChar};
        char rightPair[2] = {newChar, pair[1]};
        newPairCount[pairToIndex(leftPair)] += count;
        newPairCount[pairToIndex(rightPair)] += count;
      }
    }
    free(pairCount);
    pairCount = newPairCount;
  }

  long* count = calloc(sizeof(int), 26);
  long max = 0;
  long min = LONG_MAX;
  for (int i = 0; i < numPairs; i++) {
    char* pair = indexToPair(i);
    count[pair[0] - 'A'] += pairCount[i];
    count[pair[1] - 'A'] += pairCount[i];
    if (pairCount[i] > 0) {
      printf("%c%c: %ld\n", pair[0], pair[1], pairCount[i]);
    }
  }
  count[start[0] - 'A']++;
  count[start[chainSize - 1] - 'A']++;
  // printf("\n");
  for (int i = 0; i < 26; i++) {
    long c = count[i];
    printf("%c: %ld\n", i + 'A', c);
    if (c > 0 && c < min) {
      printf("new min\n");
      min = c;
    }
    if (c > max) {
      printf("new max\n");
      max = c;
    }
  }

  printf("result: (%ld - %ld) / 2 = %ld\n", max, min, (max - min) / 2);
}