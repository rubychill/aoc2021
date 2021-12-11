#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util/util.h"

const int lines = 94;
const int lineLength = 111;
// const int lines = 10;
// const int lineLength = 26;

int main() {
  char** inputLines = mallocStringArray(lines, lineLength);
  loadInput("input.txt", lineLength, inputLines);
  //part1(inputLines);
  part2(inputLines);
  free(inputLines);
  return 0;
}

void part1(char** input) {
  Stack* brackets = createStack(lineLength);
  int points = 0;
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < strlen(input[i]); j++) {
      char bracket = input[i][j];
      if (bracket == '(' || bracket == '[' || bracket == '<' || bracket == '{') {
        push(brackets, (int)bracket);
      } else {
        char matchingBracket = (char)pop(brackets);
        if (
          (matchingBracket == '(' && bracket != ')') ||
          (matchingBracket == '[' && bracket != ']') ||
          (matchingBracket == '<' && bracket != '>') ||
          (matchingBracket == '{' && bracket != '}')
        ) {
          switch (bracket) {
            case ')':
              points += 3;
              break;
            case ']':
              points += 57;
              break;
            case '}':
              points += 1197;
              break;
            case '>':
              points += 25137;
              break;
          }
          break;
        }
      }
    }

    while (!isEmpty(brackets)) {
      pop(brackets);
    }
  }

  printf("result: %d\n", points);
}

void part2(char** input) {
  Stack* brackets = createStack(lineLength);
  long allPoints[lines];
  int autocompleted = 0;
  for (int i = 0; i < lines; i++) {
    int discard = 0;
    for (int j = 0; j < strlen(input[i]); j++) {
      char bracket = input[i][j];
      if (bracket == '(' || bracket == '[' || bracket == '<' || bracket == '{') {
        push(brackets, (int)bracket);
      } else {
        char matchingBracket = (char)pop(brackets);
        if (
          (matchingBracket == '(' && bracket != ')') ||
          (matchingBracket == '[' && bracket != ']') ||
          (matchingBracket == '<' && bracket != '>') ||
          (matchingBracket == '{' && bracket != '}')
        ) {
          discard = 1;
          break;
        }
      }
    }
    if (!discard) {
      long points = 0;
      while (!isEmpty(brackets)) {
        char toComplete = (char)pop(brackets);
        points *= 5;
        switch (toComplete) {
          case '(':
            points += 1;
            break;
          case '[':
            points += 2;
            break;
          case '{':
            points += 3;
            break;
          case '<':
            points += 4;
            break;
        }
      }
      allPoints[autocompleted] = points;
      autocompleted++;
    } else {
      while (!isEmpty(brackets)) {
        pop(brackets);
      }
    }
  }

  qsort(allPoints, autocompleted, sizeof(long), comparel);

  printf("result: %ld\n", allPoints[autocompleted / 2]);
}