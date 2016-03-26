//
// Created by enzo on 09/03/16.
    //
 //
#include <unistd.h>                                 //
#include "dijkstra.h"                               //
                                                    //
int nb_nodes;                                       //
nod** dijkstra;                                     //	this array will contain every nodes of the graph
nod * goal;                                         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void robot_print(const RRRobot* robot)       //
{                                                   //
    static const char* translations[5] =            //
            {                                       //
                    "east",                         //
                    "north",                        //
                    "west",                         //
                    "south",                        //
                    "dead"                          //
            } ;                                     //
    printf(                                         //
            "robot is at (%d, %d) looking %s\n",    //
            robot->line,                            //
            robot->column,                          //
            translations[robot->status]             //
    ) ;                                             //
}                                                   //

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RRRobotMove*										//
byDijkstra(nod* N, nod* D, nod ** Tab, int nb){     //	this function will calculate the shortest path in a graph
    nb_nodes = nb;                                  //	N is the start point of the graph and D is the goal     //
    dijkstra = Tab;                                 //
    goal = D;                                       //
    initHeap(nb);
    for(int i = 0 ;  i < nb_nodes ; ++i){	        //
        dijkstra[i]->dist = INT_MAX;		        //	unreachable distance, so every path will be shorter than this one
        dijkstra[i]->end = 0;				        //	I set every nodes to 0, when every neighbours she got will be
        dijkstra[i]->visited = 0;                   //
    }										        //	examine I'll set it to 1
    push(N);                                        //  I add the starting point in the reachable array
    N->dist = 0;                                    //	the starting node is at 0 distance from itself
    while(nb_nodes != 0)                               //	i'll run the program till every nodes will be visitedr
        updateNeibs(pop());                         //	updateNeibs update the distance from a node to an other + the distance
    RRRobotMove* Path                               //	i'll return an array which contain the shortest path of the graph nodes by nodes + 1 an end nodes
            = malloc(sizeof(RRRobotMove )* (D->dist + 2));
    nod * flag = D;							        //	this array will be as long as the distance between the beginning and the goal
    int j = D->dist + 1;                            //
    while(flag != NULL){                                             //	in this loop I add every move I have made from the begining till the end
        Path[j] = flag->move;                       //
        robot_print(flag->data);
        flag = flag->prev;				        	//
        printf("%d \n", j);
        -- j;                                       //
    }			//
    Path[0] = D->dist + 2;				            //  little trick : in the first case I indicate the array's size
    freeHeap();
    return Path;							        //	and then we return the array
}											        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void reverseDijkstra(nod* goal, nod ** Tab, int nb){
    nb_nodes = nb;
    dijkstra = Tab;
    puts("ok");
    for(int i = 0 ;  i < nb_nodes ; ++i){
        dijkstra[i]->goaldist = INT_MAX;
        dijkstra[i]->end = 0;
        dijkstra[i]->visited = 0;
    }
    puts("ok");
    initHeap(nb);
    push(goal);
    goal->goaldist = 0;
    while(nb_nodes != 0)
        updateParents(pop());
    /*for(int i = 0; i < nb ; ++ i)
//        printf("%d \n",Tab[i]->goaldist);*/
    freeHeap();
}
void 								        		//
updateGoalDist(nod* N1, nod* N2){		        	    //
    N2->goaldist = N1->goaldist + 1;		        		///
}
void
updateParents(nod * N){
    -- nb_nodes;
    nod * P;
    P = malloc(sizeof(nod));
    for(int i = 0 ; i < N->parent->size ; ++i) {                  //
        dyntab_get(N->parent, i, P);
        if (P != NULL                      //
            && N->data->status != RR_ROBOT_DEAD) {

            if (P->goaldist > N->goaldist + 1) {    //	if the new path is shorter than the previous one
                updateGoalDist(N, P);
                puts("caca");
            }//
        if (P->visited == 0) {         //
            push(P);                   //
        }                                       //
        }                                           //
    }                                               //	I'll set the distance of his neighbour to his distance +1
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void 										        //
updateNeibs(nod* N){                                //
    -- nb_nodes;
    for(int i = 0 ; i < 7 ; ++i) {                  //
        if (N->neib[i] != NULL                      //
            && N->data->status != RR_ROBOT_DEAD) {  //	for every neighbour's node ...
            if (N->neib[i]->dist > N->dist + 1)     //	if the new path is shorter than the previous one
                updateDist(N, N->neib[i]);          //
            if (N->neib[i]->visited == 0) {         //
                push(N->neib[i]);                   //
                N->neib[i]->move = i;               //  i will give the RRRobotMove
            }                                       //
        }                                           //
    }                                               //	I'll set the distance of his neighbour to his distance +1
}								        			//
//
void 								        		//
updateDist(nod* N1, nod* N2){		        	    //
    N2->dist = N1->dist + 1;		        		//
    N2->prev = N1;					        		//
}									        		//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////



