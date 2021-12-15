#ifndef MAIN_H
#define MAIN_H

typedef struct Node {
    int index;
    int cost;
} Node;

int compareNode(const void* a, const void* b);

int main();
void part1(int* input, int width, int height);
void part2(int* input);

#endif