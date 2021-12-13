
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

void loadInputIntArray(char* filename, int lines, int lineLength, int** out) {
  char** input = malloc(sizeof(char*)*lines);
  for (int i = 0; i < lines; i++) {
    input[i] = malloc(sizeof(char) * lineLength);
  }

  loadInputLines(filename, lineLength, lines, input);
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < lineLength - 1; j++) {
      out[i][j] = (int)(input[i][j] - '0');
    }
  }

  // free
  for (int i = 0; i < lines; i++) {
    free(input[i]);
  }
  free(input);
  printf("Input int array loaded!\n");
}

void loadInputIntArray1D(char* filename, int lines, int lineLength, int* out) {
  char** input = malloc(sizeof(char*)*lines);
  for (int i = 0; i < lines; i++) {
    input[i] = malloc(sizeof(char) * lineLength);
  }

  loadInputLines(filename, lineLength, lines, input);
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < lineLength - 2; j++) {
      out[i * (lineLength - 2) + j] = (int)(input[i][j] - '0');
    }
  }

  // free
  for (int i = 0; i < lines; i++) {
    free(input[i]);
  }
  free(input);
  printf("Input int array loaded!\n");
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

int** mallocIntArray(int lines, int lineLength) {
  int** input = malloc(sizeof(int*) * lines);
  for (int i = 0; i < lines; i++) {
    input[i] = malloc(sizeof(int) * lineLength);
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

int power10(int n) {
    static int pow[10] = {
        1, 10, 100, 1000, 10000, 
        100000, 1000000, 10000000, 100000000, 1000000000
    };

    return pow[n]; 
}

// C program for array implementation of stack

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
 
// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}
 
// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}
 
// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    //printf("%d pushed to stack\n", item);
}
 
// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}
 
// Function to return the top from stack without removing it
int peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}

int compare( const void* a, const void* b) {
  int int_a = * ( (int*) a );
  int int_b = * ( (int*) b );

  if ( int_a == int_b ) return 0;
  else if ( int_a < int_b ) return -1;
  else return 1;
}

int comparel( const void* a, const void* b) {
  long int_a = * ( (long*) a );
  long int_b = * ( (long*) b );

  if ( int_a == int_b ) return 0;
  else if ( int_a < int_b ) return -1;
  else return 1;
}

/**
 * List implementation
 */
List* createList(int capacity) {
  List* list = malloc(sizeof(List));
  void** array = calloc(sizeof(void*), capacity);
  list->array = array;
  list->size = 0;
  list->capacity = capacity;
  return list;
}

int lsSize(List* ls) { return ls->size; }

int lsIsEmpty(List* ls) { return ls->size == 0; }

void* lsGet(List* ls, int index) {
  return ls->array[index];
}

void lsInsert(List* ls, void* item, int index) {
  if (index < 0 || index > ls->size) {
    printf("can't insert outside of current list size ya big dingus\n");
    return;
  }
  if (ls->size == ls->capacity) {
    printf("list is already at capacity ya big dingus\n");
    return;
  }

  void* temp;
  for (int i = index; i < ls->size + 1; i++) {
    temp = ls->array[i + 1];
    ls->array[i + 1] = ls->array[i];
  }

  ls->array[index] = item;
  ls->size++;
}

void* lsRemove(List* ls, int index) {
  if (index < 0 || index > ls->size - 1) {
    printf("index is outside valid ranges ya big dingus\n");
  }
  void* removed = ls->array[index];
  for (int i = index; i < ls->size + 1; i++) {
    ls->array[i] = ls->array[i + 1];
  }

  ls->size--;
  return removed;
}

int lsIndexOf(List* ls, void* item, int (*comp)(const void*, const void*)) {
  for (int i = 0; i < ls->size; i++) {
    if (!comp(ls->array[i], item)) {
      return i;
    }
  }
  return -1;
}

void lsAddHead(List* ls, void* item) {
  lsInsert(ls, item, 0);
}

void lsAddTail(List* ls, void* item) {
  lsInsert(ls, item, ls->size);
}

void* lsRemoveHead(List* ls) {
  return lsRemove(ls, 0);
}

void* lsRemoveTail(List* ls) {
  return lsRemove(ls, ls->size - 1);
}

List* lsCloneList(List* ls) {
  List* newList = createList(ls->capacity);
  memcpy(newList->array, ls->array, ls->capacity);
  newList->size = ls->size;
  return newList;
}