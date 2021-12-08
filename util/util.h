#ifndef UTIL_H
#define UTIL_H

#define result(i) printf("result: %d\n", i);

void loadInput(char* filename, int lineLength, char** out);
void loadInputInts(char* filename, int lines, int lineLength, int* out);
void loadInputLines(char* filename, int lineLength, int lines, char** out);
void loadInputsBase(char* filename, int lines, int lineLength, int* out, int base);
char** mallocStringArray(int lines, int lineLength);
void freeStringArray(char** stringArray, int arrayLength);
int power10(int n);

#endif