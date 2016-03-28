#ifndef ROBORALLY_HEAP_H_
#define ROBORALLY_HEAP_H_

#include<stdio.h>
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"graph.h"

dyntab* initHeap(int, size_t);
void push(void*, dyntab*);
void * pop(dyntab*);
void freeHeap(dyntab*);

#endif

