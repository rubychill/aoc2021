#ifndef MAIN_H
#define MAIN_H

#include "../util/util.h"

typedef struct Edge {
    int start;
    int end;
} Edge;

typedef struct Node {
    char* name;
    int bigRoom;
    List* connections;
} Node;

int main();
void part1(char** input);
void part2(char** input);

int nodecmp(Node* a, Node* b);
int nodestrcmp(Node* a, char* bStr);

void generatePath(List* paths, List* currentPath, Node* currentNode, int consumedSecondSmall);

#endif