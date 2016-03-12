//
// Created by enzo on 09/03/16.
//

#ifndef ROBORALLY_DIJKSTRA_H
#define ROBORALLY_DIJKSTRA_H

#include "board.h"
/*
RRRobotMove* dijkstra(nod* D, nod * A);
nod* closestOnPath();
void addToPath(nod* N);
void removeFromPath(nod * N);
void printPath();
void addNeib(nod*);
int isOnPath(nod *);

nod* bestValue(path*, nod*, int);
path* initPath();
cell* addCell(path* P, nod * data);
void removeCell(path* , nod*);
int isOnPathDir(path * P, nod * N, direction dir);
 */

RRRobotMove* bydijkstra(nod*, nod*, nod**, int);
nod* find(nod*);
void updateNeibs(nod*);
void updateDist(nod*, nod*);
int end();
nod* bestNode();
void visited(nod*);
nod* notvisited();
void addNeib(nod*);
void printPath();
nod* findBestValue();
#endif //ROBORALLY_DIJKSTRA_H
