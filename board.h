#ifndef ROBORALLY_BOARD_H_
#define ROBORALLY_BOARD_H_


#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
/** Types **/

/* Board tiles */

typedef enum {
/*  0 */  RR_TILE_BELT_E,
/*  1 */  RR_TILE_BELT_N,
/*  2 */  RR_TILE_BELT_W,
/*  3 */  RR_TILE_BELT_S,
/*  4 */  RR_TILE_TURN_SE,
/*  5 */  RR_TILE_TURN_SW,
/*  6 */  RR_TILE_TURN_EN,
/*  7 */  RR_TILE_TURN_WN,
/*  8 */  RR_TILE_TURN_NW,
/*  9 */  RR_TILE_TURN_NE,
/* 10 */  RR_TILE_TURN_WS,
/* 11 */  RR_TILE_TURN_ES,
/* 12 */  RR_TILE_JOIN_S_TO_E, 
/* 13 */  RR_TILE_JOIN_S_TO_W, 
/* 14 */  RR_TILE_JOIN_E_TO_N, 
/* 15 */  RR_TILE_JOIN_W_TO_N, 
/* 16 */  RR_TILE_JOIN_N_TO_E, 
/* 17 */  RR_TILE_JOIN_N_TO_W, 
/* 18 */  RR_TILE_JOIN_W_TO_S, 
/* 19 */  RR_TILE_JOIN_E_TO_S, 
/* 20 */  RR_TILE_JOIN_NS_TO_E, 
/* 21 */  RR_TILE_JOIN_EW_TO_N, 
/* 22 */  RR_TILE_JOIN_NS_TO_W, 
/* 23 */  RR_TILE_JOIN_EW_TO_S, 
/* 24 */  RR_TILE_FAST_BELT_E,
/* 25 */  RR_TILE_FAST_BELT_N,
/* 26 */  RR_TILE_FAST_BELT_W,
/* 27 */  RR_TILE_FAST_BELT_S,
/* 28 */  RR_TILE_FAST_TURN_SE,
/* 29 */  RR_TILE_FAST_TURN_SW,
/* 30 */  RR_TILE_FAST_TURN_EN,
/* 31 */  RR_TILE_FAST_TURN_WN,
/* 32 */  RR_TILE_FAST_TURN_NW,
/* 33 */  RR_TILE_FAST_TURN_NE,
/* 34 */  RR_TILE_FAST_TURN_WS,
/* 35 */  RR_TILE_FAST_TURN_ES,
/* 36 */  RR_TILE_FAST_JOIN_S_TO_E, 
/* 37 */  RR_TILE_FAST_JOIN_S_TO_W, 
/* 38 */  RR_TILE_FAST_JOIN_E_TO_N, 
/* 39 */  RR_TILE_FAST_JOIN_W_TO_N, 
/* 40 */  RR_TILE_FAST_JOIN_N_TO_E, 
/* 41 */  RR_TILE_FAST_JOIN_N_TO_W, 
/* 42 */  RR_TILE_FAST_JOIN_W_TO_S, 
/* 43 */  RR_TILE_FAST_JOIN_E_TO_S, 
/* 44 */  RR_TILE_FAST_JOIN_NS_TO_E, 
/* 45 */  RR_TILE_FAST_JOIN_EW_TO_N, 
/* 46 */  RR_TILE_FAST_JOIN_NS_TO_W, 
/* 47 */  RR_TILE_FAST_JOIN_EW_TO_S, 
/* 48 */  RR_TILE_ROTATE_RIGHT, 
/* 49 */  RR_TILE_ROTATE_LEFT, 
/* 50 */  RR_TILE_NOTHING,
/* 51 */  RR_TILE_NONE 
} RRTileType ;

typedef struct {
  int line ;
  int column ;
  RRTileType type ;
} RRTile ;

/* Board */

typedef struct {
  RRTile* tiles ;
  unsigned int tile_size ;
  unsigned int width ;
  unsigned int height ;
} RRBoard ;

/* Robot movements */

typedef enum {
  RR_MOVE_FORWARD_1,
  RR_MOVE_FORWARD_2,
  RR_MOVE_FORWARD_3,
  RR_MOVE_BACKWARD_1,
  RR_TURN_LEFT,
  RR_TURN_RIGHT,
  RR_U_TURN
} RRRobotMove ;

/* Robot status (mostly orientation) */

typedef enum {
  RR_ROBOT_E,
  RR_ROBOT_N,
  RR_ROBOT_W,
  RR_ROBOT_S,
  RR_ROBOT_DEAD,
} RRRobotStatus ;


/* Robot */

typedef struct {
  unsigned int line ;
  unsigned int column ;
  RRRobotStatus status ;
} RRRobot ;
RRRobotStatus getStatus(RRRobot*);
/** Board construction and destruction **/

void rr_board_init (
    RRBoard* board,
    const char* filename
    ) ;

void rr_board_destroy (
    RRBoard* board
    ) ;

void rr_board_save(
    RRBoard* board,
    const char* filename
    ) ;

/** Moves **/

/* play a move from a given robot position */

void rr_board_play (
    const RRBoard* board,
    RRRobot* robot, /* updated */
    RRRobotMove move
    ) ;


//////////////////////////////////////////////////////////////////////////////

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
}direction ;

typedef struct _nod{
    RRRobot* data;
    int dist;
    int end;
    int id;
    RRRobotMove move;
    struct _nod** neib;// nord sud est ouest
    struct _nod* prev;
}nod;

nod* initNod(RRRobot *, RRRobotMove);


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
void construitGraph2(nod* N, const RRBoard* board, nod** Tab);
RRRobot * duplicateBot(const RRRobot *);
void newHorizon(int i, nod* N, RRRobotMove move, nod**, const RRBoard*);
RRRobot* inTab(RRRobot* bot, nod** T, int);
void addTab(nod* N, nod** T);
nod * arrive();
void printTab();
nod* findNode(int line, int column);
void completeGraphviz(nod* N1, nod* N2);
nod** getTab();
int getlength();
#endif
