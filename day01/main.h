#ifndef DAY1_H
#define DAY1_H

#include "../util/cute_coroutine.h"

void day1();
void part1(int* depths);
void part2(int* depths);
void part1co(int* depths);
int doPart1(coroutine_t* co, int* depths, int* result);

#endif