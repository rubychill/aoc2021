#ifndef UTIL_H
#define UTIL_H

#define result(i) printf("result: %d\n", i);

void loadInput(char* filename, int lineLength, char** out);
void loadInputInts(char* filename, int lines, int lineLength, int* out);
void loadInputIntArray(char* filename, int lines, int lineLength, int** out);
void loadInputIntArray1D(char* filename, int lines, int lineLength, int* out);
void loadInputLines(char* filename, int lineLength, int lines, char** out);
void loadInputsBase(char* filename, int lines, int lineLength, int* out, int base);
char** mallocStringArray(int lines, int lineLength);
int** mallocIntArray(int lines, int lineLength);
void freeStringArray(char** stringArray, int arrayLength);
int power10(int n);

typedef struct Point {
  int x,y;
} Point;

// C program for array implementation of stack

// A structure to represent a stack
typedef struct Stack {
    int top;
    unsigned capacity;
    int* array;
} Stack;
 
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity);
 
// Stack is full when top is equal to the last index
int isFull(struct Stack* stack);
 
// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack);
 
// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item);
 
// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack);
 
// Function to return the top from stack without removing it
int peek(struct Stack* stack);

int compare( const void* a, const void* b);
int comparel( const void* a, const void* b);

#endif