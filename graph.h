#include "board.h"

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

typedef enum {
		NORTH, 
		SOUTH, 
		EAST, 
		WEST
		}direction ;

typedef struct _nod{	
	RRRobot* data;
	int dist;
	struct _nod** neib;// nord sud est ouest
	struct _nod* prev;
}nod;

nod* initNod(RRRobot *);


#define TAILLE_BASE 15

typedef struct _graph{
	nod* depart;
	int nb_nods;
	int kappa;
}graph;

typedef struct _Cell{
	direction dir;
	nod* data;
	struct _Cell* next;
}cell;

typedef struct _path{
	int size;
	cell* bestValue;
	cell* first;
	cell* last;
}path;

void construitGraph(nod* N, const RRBoard* board, nod** Tab);
RRRobot * duplicateBot(RRRobot *);
RRRobot * createNode(RRRobot *);
void newHorizon(int i, nod* N, RRRobotMove move, nod**);
