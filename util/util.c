
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadInput(char* filename, int lineLength, char** out) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    printf("could not load file\n");
    exit(-1);
  }
  
  int i = 0;
  while (fgets(out[i], lineLength, file)) {
    out[i][strcspn(out[i], "\n")] = 0;
    i++;
  }
  fclose(file);
  printf("Input loaded!\n");
}

void loadInputLines(char* filename, int lineLength, int lines, char** out) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    printf("could not load file\n");
    exit(-1);
  }
  
  int i = 0;
  while (fgets(out[i], lineLength, file) && i < lines) {
    out[i][strcspn(out[i], "\n")] = 0;
    i++;
  }
  fclose(file);
  printf("Input loaded!\n");
}

void loadInputInts(char* filename, int lines, int lineLength, int* out) {
  char** input = malloc(sizeof(char*)*lines);
  for (int i = 0; i < lines; i++) {
    input[i] = malloc(sizeof(char) * lineLength);
  }

  loadInputLines(filename, lineLength, lines, input);
  for (int i = 0; i < lines; i++) {
    int inputInt = strtol(input[i], NULL, 0);
    out[i] = inputInt;
  }

  // free
  for (int i = 0; i < lines; i++) {
    free(input[i]);
  }
  free(input);
  printf("Input ints loaded!\n");
}

char** mallocStringArray(int lines, int lineLength) {
  char** input = malloc(sizeof(char*)*lines);
  for (int i = 0; i < lines; i++) {
    input[i] = malloc(sizeof(char) * lineLength);
  }

  return input;
}

void freeStringArray(char** stringArray, int arrayLength) {
  for (int i = 0; i < arrayLength; i++) {
    free(stringArray[i]);
  }
  free(stringArray);
}

void loadInputsBase(char* filename, int lines, int lineLength, int* out, int base) {
  char** input = malloc(sizeof(char*)*lines);
  for (int i = 0; i < lines; i++) {
    input[i] = malloc(sizeof(char) * lineLength);
  }

  loadInputLines(filename, lineLength, lines, input);
  for (int i = 0; i < lines; i++) {
    int inputInt = strtol(input[i], NULL, base);
    out[i] = inputInt;
  }

  // free
  for (int i = 0; i < lines; i++) {
    free(input[i]);
  }
  free(input);
  printf("Input ints loaded!\n");
}