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
int boardStateIndex(int i) { return i / boardWidth; }
int boardStateOffset(int i) { return i % boardWidth; }
int boardFlippedStateIndex(int i) { return (i % boardWidth) + (boardNumber(i) * boardWidth); }
int boardFlippedStateOffset(int i) {return (i % boardSize) / boardWidth; }

/**
 * State is stored twice so that completed lines can be read as 0x1F integers both horizontally and vertically
 * Horizontal state (regular state) is intuitive, if boards are lined up vertically each int will represent the following state
 * 
 * (board 0)
 *  0  0  0  0  0
 *  1  1  1  1  1
 *  2  2  2  2  2
 *  3  3  3  3  3
 *  4  4  4  4  4
 *  5  5  5  5  5
 * 
 * (board 1)
 *  6  6  6  6  6
 *  7  7  7  7  7
 *  8  8  8  8  8
 *  9  9  9  9  9
 * 10 10 10 10 10
 * 
 * (etc...)
 * 
 * Vertical state (flipped state) is funky but makes sense if you imagine the boards lined up horizontally
 * (board 0)         (board 1)             (etc...)
 *  0  1  2  3  4     5  6  7  8  9  10
 *  0  1  2  3  4     5  6  7  8  9  10
 *  0  1  2  3  4     5  6  7  8  9  10
 *  0  1  2  3  4     5  6  7  8  9  10
 *  0  1  2  3  4     5  6  7  8  9  10
 * 
 * For each horizontal or vertical line, the state is store as a int representing the binary state of that line
 * eg: a row:
 *  - X - X X
 * will have the binary representation 0b01011 (11)
 * We know a row is full when it has the value 0b11111 (31)
 */

void part1(int* numbers, int* boards) {
  int* boardStates = calloc(sizeof(int), boardCount * 5);
  int* boardStatesFlipped = calloc(sizeof(int), boardCount * 5);
  int* boardSolved = calloc(sizeof(int), boardCount);

  // draw numbers
  for (int draw = 0; draw < numbersDrawn; draw++) {
    int drawnNumber = numbers[draw];
    // iterate through all board numbers
    for (int i = 0; i < boardLines; i++) {
      int boardValue = boards[i];
      if (boardValue == drawnNumber) {
        // grab all the needed state indexes
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
          // make a bit mask to check whether a space was marked
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