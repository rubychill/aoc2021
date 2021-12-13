#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util/util.h"

const int lines = 23;
const int lineLength = 10;

int main() {
  char** inputLines = mallocStringArray(lines, lineLength);
  loadInput("input.txt", lineLength, inputLines);
  part1(inputLines);
  part2(inputLines);
  free(inputLines);
  return 0;
}

int nodecmp(Node* a, Node* b) {
  return strcmp(a->name, b->name);
}

int nodestrcmp(Node* a, char* bStr) {
  return strcmp(a->name, bStr);
}

void part1(char** input) {
  List* nodes = createList(lines * lines);
  // generate nodes
  Node* start;
  Node* end;
  for (int i = 0; i < lines; i++) {
    // This is probably a memory management nightmare but it's AoC so idc
    char* startStr = malloc(sizeof(char) * 5);
    char* endStr = malloc(sizeof(char) * 5);
    sscanf(input[i], "%[A-Za-z]-%[A-Za-z]", startStr, endStr);
    Node* startNode;
    Node* endNode;
    int startIndex = lsIndexOf(nodes, startStr, nodestrcmp);
    if (startIndex == -1) {
      startNode = malloc(sizeof(Node));
      startNode->name = startStr;
      startNode->bigRoom = startStr[0] < 'a';
      startNode->connections = createList(lines * lines);
      lsAddTail(nodes, startNode);
    } else {
      startNode = lsGet(nodes, startIndex);
    }

    int endIndex = lsIndexOf(nodes, endStr, nodestrcmp);
    if (endIndex == -1) {
      endNode = malloc(sizeof(Node));
      endNode->name = endStr;
      endNode->bigRoom = endStr[0] < 'a';
      endNode->connections = createList(lines * lines);
      lsAddTail(nodes, endNode);
    } else {
      endNode = lsGet(nodes, endIndex);
    }

    if (strcmp(endStr, "start") != 0) {
      lsAddTail(startNode->connections, endNode);
    }

    if (strcmp(startStr, "start") != 0) {
      lsAddTail(endNode->connections, startNode);
    }

    if (strcmp(startNode->name, "start") == 0) {
      start = startNode;
    }
    if (strcmp(endNode->name, "end") == 0) {
      end == endNode;
    }
  }
  printf("Generating paths\n");
  List* paths = createList(lines * lines * lines * lines);
  List* currentPath = createList(lines * lines);
  generatePath(paths, currentPath, start, 0);
  // printf("Paths:\n");
  // for (int i = 0; i < lsSize(paths); i++) {
  //   printf("%d: ", i);
  //   List* path = (List*)lsGet(paths, i);
  //   for (int j = 0; j < lsSize(path); j++) {
  //     Node* node = lsGet(path, j);
  //     printf("%s ", node->name);
  //   }
  //   printf("\n");
  // }
  printf("result: %d\n", lsSize(paths));
}

void generatePath(List* paths, List* currentPath, Node* currentNode, int consumedSecondSmall) {
  // printf("Add node to path\n");
  lsAddTail(currentPath, currentNode);
  // printf("Current path (length %d):\n", lsSize(currentPath));
  // for (int i = 0; i < lsSize(currentPath); i++) {
  //   printf("%d: %s\n", i, ((Node*)lsGet(currentPath, i))->name);
  // }
  // printf("exploring %s\n", currentNode->name);
  if (strcmp(currentNode->name, "end") == 0) {
    // printf("Found path\n");
    lsAddTail(paths, currentPath);
    return;
  }
  int connectionsCount = lsSize(currentNode->connections);
  for (int i = 0; i < connectionsCount; i++) {
    int iterConsumedSmall = consumedSecondSmall;
    Node* nextNode = lsGet(currentNode->connections, i);
    // printf("next node %s: big:%d indexOf:%d\n", nextNode->name, nextNode->bigRoom, lsIndexOf(currentPath, nextNode, nodecmp));
    // printf("before %d\n", iterConsumedSmall);
    if (nextNode->bigRoom || lsIndexOf(currentPath, nextNode, nodecmp) == -1 || (!iterConsumedSmall && ++iterConsumedSmall)) {
      // printf("after %d\n", iterConsumedSmall);
      List* pathCopy;
      if (connectionsCount > 1) {
        pathCopy = lsCloneList(currentPath);
      } else {
        pathCopy = currentPath;
      }
      generatePath(paths, pathCopy, nextNode, iterConsumedSmall);
    }
  }
}

void part2(char** input) {
  
}