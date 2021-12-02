
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void loadInput(char* filename, int lineLength, char** out) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    printf("could not load file\n");
    exit(-1);
  }
  
  int i = 0;
  while (fscanf(file, "%s", out[i])) {
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

  loadInput(filename, lineLength, input);
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