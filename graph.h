#ifndef ROBORALLY_GRAPH_H_
#define ROBORALLY_GRAPH_H_

#include "board.h"
#include <limits.h>
#include "array.h"


/* La structure de donnée utilisée pour representer tous les movements possibles du robot sur le plateau
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

typedef struct _nod{
    RRRobot* data;
    unsigned int dist;
    unsigned int goaldist;
    int end;
    unsigned int id;
    int visited;
    RRRobotMove move;
    struct _nod** neib;// nord sud est ouest
    struct _nod* prev;
    dyntab* parent;
}nod;

nod* initNod(RRRobot *);
void buildGraph(nod*, const RRBoard*, nod**);
void initGraph(nod*, const RRBoard*, nod**);
RRRobot * duplicateBot(const RRRobot *);
void newHorizon(int, nod*, RRRobotMove, nod**, const RRBoard*);
nod* inTab(RRRobot*, nod**, int);
void addTab(nod*, nod**);
nod* findNode(int, int, RRRobotStatus);
void completeGraphviz(nod*, nod*);
nod** getTab();
int getId();
void freeGraph();
void freeNode(nod * N);

#endif