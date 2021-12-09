#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util/util.h"

const int lines = 200;
const int lineLength = 129;
const int signalLength = 9;
const int signalCount = 10;
const int digitsCount = 4;

int main() {
  char** inputLines = mallocStringArray(lines, lineLength);
  loadInput("input.txt", lineLength, inputLines);
  char** signals = mallocStringArray(signalCount * lines, signalLength);
  char** digits = mallocStringArray(digitsCount * lines, signalLength);
  for (int i = 0; i < lines; i++) {
    sscanf(inputLines[i], "%s %s %s %s %s %s %s %s %s %s | %s %s %s %s",
      signals[(i * signalCount) + 0],
      signals[(i * signalCount) + 1],
      signals[(i * signalCount) + 2],
      signals[(i * signalCount) + 3],
      signals[(i * signalCount) + 4],
      signals[(i * signalCount) + 5],
      signals[(i * signalCount) + 6],
      signals[(i * signalCount) + 7],
      signals[(i * signalCount) + 8],
      signals[(i * signalCount) + 9],
      digits[(i * digitsCount) + 0],
      digits[(i * digitsCount) + 1],
      digits[(i * digitsCount) + 2],
      digits[(i * digitsCount) + 3]
    );
  }
  //part1(signals, digits);
  part2(signals, digits);
  return 0;
}

void part1(char** signals, char** digits) {
  int count = 0;
  for (int i = 0; i < digitsCount * lines; i++) {
    int digitLen = strlen(digits[i]);
    printf("%s %d\n", digits[i], digitLen);
    if (digitLen == 2 || digitLen == 3 || digitLen == 4 || digitLen == 7) {
      count++;
    }
  }

  printf("result: %d\n", count);
}

//   0:      1:      2:      3:      4:
//  aaaa    ....    aaaa    aaaa    ....
// b    c  .    c  .    c  .    c  b    c
// b    c  .    c  .    c  .    c  b    c
//  ....    ....    dddd    dddd    dddd
// e    f  .    f  e    .  .    f  .    f
// e    f  .    f  e    .  .    f  .    f
//  gggg    ....    gggg    gggg    ....

//   5:      6:      7:      8:      9:
//  aaaa    aaaa    aaaa    aaaa    aaaa
// b    .  b    .  .    c  b    c  b    c
// b    .  b    .  .    c  b    c  b    c
//  dddd    dddd    ....    dddd    dddd
// .    f  e    f  .    f  e    f  .    f
// .    f  e    f  .    f  e    f  .    f
//  gggg    gggg    ....    gggg    gggg

const int segments[10] = {
//gfedcba
0b1110111, // 0
0b0100100, // 1
0b1011101, // 2
0b1101101, // 3
0b0101110, // 4
0b1101011, // 5
0b1111011, // 6
0b0100101, // 7
0b1111111, // 8
0b1101111, // 9
};

int charToInt(char c) {
  return (int)(c - 'a');
}

char intToChar(int i) {
  return (char)(i + 'a');
}

void swap(char *a, char *b) { char t = *a; *a = *b; *b = t; }

void permute(char *a, int i, int n, char** out, int* outSize) {
  // If we are at the last letter, print it
  if (i == (n-1)) {
    out[*outSize] = malloc(sizeof(char) * 8);
    strcpy(out[*outSize], a);
    *outSize = *outSize + 1;
  } else {
    // Show all the permutations with the first i-1 letters fixed and 
    // swapping the i'th letter for each of the remaining ones.
    for (int j = i; j < n; j++) {
      swap((a+i), (a+j));
      permute(a, i+1, n, out, outSize);
      swap((a+i), (a+j));
    }
  }
}

const int numTranslations = 5040;

void generateTranslations(int** out) {
  for (int i = 0; i < numTranslations; i++) {
    out[i] = malloc(sizeof(int) * 10);
  }
}

int translateSignal(char* signal, int* translation) {
  int translatedInt = 0;
  //printf("len %d\n", strlen(signal));
  for (int c = 0; c < strlen(signal); c++) {
    int sInt = charToInt(signal[c]);
    int tInt = translation[sInt];
    //printf("%d\n", tInt);
    translatedInt += 1 << tInt;
  }
  //printf("translated %d\n", translatedInt);
  return translatedInt;
}

int signalIntToDisplay(int translatedInt) {
  //printf("signal to display %d\n", translatedInt);
  switch(translatedInt) {
    case 0b1110111: return 0;
    case 0b0100100: return 1;
    case 0b1011101: return 2;
    case 0b1101101: return 3;
    case 0b0101110: return 4;
    case 0b1101011: return 5;
    case 0b1111011: return 6;
    case 0b0100101: return 7;
    case 0b1111111: return 8;
    case 0b1101111: return 9;
  }
  return -1;
}

void part2(char** signals, char** digits) {
  int** translations = malloc(sizeof(int*) * numTranslations);
  char** permutations = malloc(sizeof(char*) * numTranslations);
  int* permutationsSize = calloc(sizeof(int), 1);
  char* input = malloc(sizeof(char) * 8);
  strcpy(input, "abcdefg");
  permute(input, 0, strlen(input), permutations, permutationsSize);

  for (int i = 0; i < numTranslations; i++) {
    //printf("translation %d\npermutation: %s\n", i, permutations[i]);
    translations[i] = malloc(sizeof(int) * 10);
    for (int j = 0; j < 10; j++) {
      translations[i][charToInt(permutations[i][j])] = j;
    }
  }

  int allDigitsTotal = 0;
  for (int i = 0; i < lines; i++) {
    //printf("line %d\n", i);
    int signalStart = i * signalCount;
    int* matchedTranslation;
    for (int transIndex = 0; transIndex < numTranslations; transIndex++) {
      int* translation = translations[transIndex];
      int matches = 0;
      for (int j = 0; j < signalCount; j++) {
        char* signal = signals[signalStart + j];
        int translatedInt = translateSignal(signal, translation);
        //printf("translatedInt %d\n", translatedInt);
        if (signalIntToDisplay(translatedInt) != -1) {
          matches++;
        }
      }
      if (matches == 10) {
        //printf("found match\n");
        matchedTranslation = translation;
        break;
      }
    }
    // calculate digits
    int digitsStart = i * digitsCount;
    int digitsTotal = 0;
    for (int j = 0; j < digitsCount; j++) {
      int digit = signalIntToDisplay(translateSignal(digits[digitsStart + j], matchedTranslation));
      //printf("digit %d is %d\n", j, digit);
      digitsTotal += digit * power10(digitsCount - j - 1);
    }
    //printf("digits %d\n", digitsTotal);
    allDigitsTotal += digitsTotal;
  }

  printf("result: %d\n", allDigitsTotal);
}