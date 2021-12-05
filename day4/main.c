#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../util/util.h"

const int numbersDrawn = 100;
const int boardCount = 100;

const int boardLineLength = 4;
const int boardWidth = 5;
const int boardSize = boardWidth * boardWidth;
const int boardLines = boardCount * boardSize;
const int boardStateMask = 0x1F;

int main() {
  int* drawNumbers = malloc(sizeof(int) * numbersDrawn);
  int* boards = malloc(sizeof(int) * boardLines);
  loadInputInts("draw.txt", numbersDrawn, 4, drawNumbers);
  loadInputInts("boards.txt", boardLines, boardLineLength, boards);

  part1(drawNumbers, boards); // comment out the return on line 76 for part 2 (yes, really)
  free(drawNumbers);
  free(boards);
  return 0;
}

int boardStart(int i) { return i * boardSize; }
int boardNumber(int i) {return i / boardSize; }
int boardStateStart(int i) { return i * boardWidth; }
int boardStateIndex(int i) { return i / boardWidth; }
int boardStateOffset(int i) { return i % boardWidth; }
int boardFlippedStateIndex(int i) { return (i % boardWidth) + (boardNumber(i) * boardWidth); }
int boardFlippedStateOffset(int i) {return (i % boardSize) / boardWidth; }



void part1(int* numbers, int* boards) {
  int* boardStates = calloc(sizeof(int), boardCount * 5);
  int* boardStatesFlipped = calloc(sizeof(int), boardCount * 5);
  int* boardSolved = calloc(sizeof(int), boardCount);

  for (int draw = 0; draw < numbersDrawn; draw++) {
    int drawnNumber = numbers[draw];
    for (int i = 0; i < boardLines; i++) {
      int boardValue = boards[i];
      if (boardValue == drawnNumber) {
        int board = boardNumber(i);
        int stateIndex = boardStateIndex(i);
        int stateOffset = boardStateOffset(i);
        int flippedIndex = boardFlippedStateIndex(i);
        int flippedOffset = boardFlippedStateOffset(i);

        boardStates[stateIndex] += 1 << stateOffset;
        boardStatesFlipped[flippedIndex] += 1 << flippedOffset;
      }
    }

    // check boards
    for (int i = 0; i < boardCount * 5; i++) {
      int boardIndex =  i / 5;
      int solved = boardSolved[boardIndex];
      if (!solved && (boardStates[i] == boardStateMask || boardStatesFlipped[i] == boardStateMask)) {
        boardSolved[boardIndex] = 1;
        int score = 0;
        for (int i = boardStart(boardIndex); i < boardStart(boardIndex + 1); i++) {
          int comp = 1 << boardStateOffset(i);
          if ((boardStates[boardStateIndex(i)] & comp) == 0) {
            score += boards[i];
          }
        }
        score *= drawnNumber;
        printf("board %d solved with score %d\n", boardIndex, score);
        //return; // comment this line out for part 2 lmao
      }
    }
  }
}