#ifndef UTIL_H
#define UTIL_H

#define result(i) printf("result: %d\n", i);

#include <limits.h>

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
    void** array;
} Stack;
 
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity);
 
// Stack is full when top is equal to the last index
int isFull(struct Stack* stack);
 
// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack);
 
// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, void* item);
 
// Function to remove an item from stack.  It decreases top by 1
void* pop(struct Stack* stack);
 
// Function to return the top from stack without removing it
void* peek(struct Stack* stack);

int compare( const void* a, const void* b);
int compareDecreasing( const void* a, const void* b);
int comparel( const void* a, const void* b);

typedef struct List {
  unsigned capacity;
  unsigned size;
  void** array;
} List;

List* createList(int capacity);
int lsSize(List* ls);
int lsIsEmpty(List* ls);
void* lsGet(List* ls, int index);
void lsInsert(List* ls, void* item, int index);
void* lsremove(List* ls, int index);
int lsIndexOf(List* ls, void* item, int (*comp)(const void*, const void*));
void lsAddHead(List* ls, void* item);
void lsAddTail(List* ls, void* item);
void* lsRemoveHead(List* ls);
void* lsRemoveTail(List* ls);
List* lsCloneList(List* ls);
List* lsResizeList(List* ls, int newSize);
void lsFree(List* ls);


typedef struct ListNode {
  void* value;
  struct ListNode* next;
} ListNode;

ListNode* createListNode(void* value);
ListNode* llsGet(ListNode* ls, long index);
void llsAddTail(ListNode* ls, void* item);
void llsInsertNode(ListNode* before, ListNode* insert);
void llsInsertValue(ListNode* before, void* insert);

/**
 * Index to xy funcs
 */
int itox(int i, int width);
int itoy(int i, int width);
int xytoi(int x, int y, int width);
int iN(int i, int width);
int iS(int i, int width, int height);
int iW(int i, int width);
int iE(int i, int width);

#endif