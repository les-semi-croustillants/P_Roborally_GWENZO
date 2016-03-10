#include "board.h"
#include <unistd.h>

int nb_elem_tab = 0;
int nb_elem_tab2 = 0;
nod* Tab2[1000];

static void robot_print(const RRRobot* robot)
{
    static const char* translations[5] =
            {
                    "east",
                    "north",
                    "west",
                    "south",
                    "dead"
            } ;

    printf(
            "robot is at (%d, %d) looking %s\n",
            robot->line,
            robot->column,
            translations[robot->status]
    ) ;
}

nod*
    arrive(){
    return Tab2[21];
}

void
    construitGraph(nod* N, const RRBoard* board, nod** Tab){
    ///////////////////////////////////////////////
	//RRRobot * bot = N->data;
    int i;
    newHorizon(0, N, RR_MOVE_FORWARD_1, Tab, board);
    newHorizon(1, N, RR_MOVE_FORWARD_2, Tab, board);
    newHorizon(2, N, RR_MOVE_FORWARD_3, Tab, board);
    newHorizon(3, N, RR_MOVE_BACKWARD_1, Tab, board);
    newHorizon(4, N, RR_TURN_LEFT, Tab, board);
    newHorizon(5, N, RR_TURN_RIGHT, Tab, board);
    newHorizon(6, N, RR_U_TURN, Tab, board);

    for(i = 0 ; i < 7 ; ++i) {
        if (getStatus(N->neib[i]->data) != RR_ROBOT_DEAD && inTab(N->neib[i]->data, Tab2, nb_elem_tab2) == NULL)
            construitGraph(N->neib[i], board, Tab);
    }
}

void
    newHorizon(int i, nod* N, RRRobotMove move, nod** Tab, const RRBoard* board){
    ////////////////////////////////////////////
    RRRobot * replace;
    RRRobot * temp = duplicateBot(N->data);
    rr_board_play (board, temp, move);

    if((replace = inTab(temp, Tab, nb_elem_tab)) != NULL)
        N->neib[i] = initNod(replace, move);
    else {
        N->neib[i] = initNod(temp, move);
        addTab(N->neib[i], Tab);
    }
    if(inTab(N->data, Tab2, nb_elem_tab2) == NULL){
        Tab2[nb_elem_tab2] = N;
        nb_elem_tab2++;
    }
}

RRRobot *
    duplicateBot(const RRRobot * bot){
    //////////////////////////////////
    RRRobot * newbot = malloc(sizeof(RRRobot));
    memcpy(newbot, bot, sizeof(RRRobot));
    return newbot;
}

nod*
    initNod(RRRobot * bot, RRRobotMove move){
    ///////////////////////
    nod * N = malloc(sizeof(nod));
    N->data = bot;
    nod** tab = malloc(sizeof(nod*)*7);
    N->neib = tab;
    int i;
    for(i = 0 ; i < 7 ; i++)
        N->neib[i] = NULL;
    N->dist = 2000000000;
    N->move = move;
    return N;
}

RRRobot*
    inTab(RRRobot* bot, nod** T, int nb){
    ///////////////////////////////////
    int x = bot->line;
    int y = bot->column;
    RRRobotStatus Status = bot->status;
    int i;
    for(i = 0 ; i < nb; ++i)
        if(T[i]->data->line == x && T[i]->data->column == y && T[i]->data->status == Status)
            return T[i]->data;

    return NULL;
}

void
    addTab(nod* N, nod** T){
    T[nb_elem_tab] = N;
    nb_elem_tab ++ ;
}







