//
// Created by enzo on 09/03/16.
//

#ifndef ROBORALLY_DIJKSTRA_H
#define ROBORALLY_DIJKSTRA_H

#include "board.h"

RRRobotMove* dijkstra(nod* D, nod * A);
nod* closestOnPath();
void addToPath(nod* N);
void removeFromPath(nod * N);
void printPath();
void addNeib(nod*);

nod* bestValue(path*, nod*, int);
path* initPath();
cell* addCell(path* P, nod * data);
void removeCell(path* , nod*);
int isOnPathDir(path * P, nod * N, direction dir);
int isOnPath(path * P, nod * N);

#endif //ROBORALLY_DIJKSTRA_H
