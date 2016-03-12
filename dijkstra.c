//
// Created by enzo on 09/03/16.
    //

#include <unistd.h>
#include "dijkstra.h"
#include "board.h"

int nb_nodes;
nod** dijkstra;                                     //	this array will contain every nodes of the graph
nod** neighbours;
int nb_neibs = 0;
int nb_visited = 0;
int bestdist = 2000000000;
nod * goal;
int finish = 0;
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RRRobotMove*										//
bydijkstra(nod* N, nod* D, nod ** Tab, int nb){     //	this function will calculate the shortest path in a graph
    nb_nodes = nb;                                  //	N is the start point of the graph and D is the goal
    dijkstra = Tab;                                 //
    goal = D;
    neighbours = malloc(sizeof(nod*)*nb);
    for(int i = 0 ;  i < nb_nodes ; ++i){	        //
        dijkstra[i]->dist = 2000000000;		        //	unreachable distance, so every path will be shorter than this one
        dijkstra[i]->end = 0;				        //	I set every nodes to 0, when every neighbours she got will be
        dijkstra[i]->visited = 0;
    }										        //	examine I'll set it to 1
    addNeib(N);
    find(N)->dist = 0;                              //	the starting node is at 0 distance from itself
    while(!end())                        //	i'll run the program till every nodes will be examine
        //	for every nodes of the graph i'll see if the distance from a
        // 	path will be shorter than an other
        updateNeibs(bestNode());            //	updateNeibs update the distance from a node to an other + the distance
                                                    // 	of the total path if this distance is shorter than a previous path
    RRRobotMove* Path                               //	i'll return an array which contain the shortest path of the graph nodes by nodes + 1 an end nodes
            = malloc(sizeof(RRRobotMove )* (D->dist + 1));
    nod * flag = D;							        //	this array will be as long as the distance between the beginning and the goal
    int j = 0;
    while(flag != N){        //	in this loop I add every nodes of the path in the array
        Path[j] = flag->move;						//
        flag = flag->prev;				        	//
        ++ j;
    }										   	    //	this node will indicate the end of the array
    Path[0] = D->dist + 1;				            //
    return Path;							        //	and then we return the array
}											        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
nod* 									        	//
find(nod* N) {//	this foncftion is used to find a certain node in the array
    for (int i = 0; i < nb_nodes; ++i) {            //
        if (dijkstra[i] == N)                       //
    return dijkstra[i];                             //
}                                                   //
    return NULL;							        //	if I don't find it i'll return NULL
}											        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void 										        //
updateNeibs(nod* N){                                //
    int i;
    for(i = 0 ; i < 7 ; ++i) {
        if (N->neib[i] != NULL
            && N->data->status != RR_ROBOT_DEAD) {     //	for every neighbour's node ...
            if (N->neib[i]->dist > N->dist + 1)     //	if the new path is shorter than the previous one
                updateDist(N, N->neib[i]);
            if (N->neib[i]->visited == 0)
                addNeib(N->neib[i]);

        }
    }
                                                    //	I'll set the distance of his neighbour to his distance +1
    visited(N);                                      //	this node will not be use again
    puts("update Neib Pass");
}								        			//
                                                    //
void 								        		//
updateDist(nod* N1, nod* N2){		        	    //
    N2->dist = N1->dist + 1;		        		//
    N2->prev = N1;					        		//
}									        		//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int 								        		//
end(){                                              //
                                                    //	this function is use to end the loop
    for(int i = 0 ; i < nb_nodes ; ++i)		        //	i check every nodes of the array
    if(!dijkstra[i]->end) {                         //	if their will be more updates
        puts("end Pass");
            return 0;
        }//	I stop the loop
    puts("finish");
    return 1;								        //	elsewhere i'll indicate to stop the program
}											        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    //
nod*                                                //
    bestNode(){                                     //
    printPath();
    nod * min = neighbours[0];                       //
    for(int i = 0 ; i < nb_neibs ; ++i)             //
        if(min->dist > neighbours[i]->dist)                    //
            min = neighbours[i];                      //
    min->end = 1;
    /*for(int i = 0 ; i < 7 ; ++i)
        robot_print(min->neib[i]->data);*/
    //sleep(3);
   // printf("(%d, %d) %d\n",min->data->line, min->data->column, min->dist);
    puts("best node Pass");
    return min ;//findBestValue();                                     //
}                                                   //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    //
void
    visited(nod* N){
    int i = 0;
    while(N != neighbours[i])
        ++i;
    N->end = 1;
    neighbours[i] = neighbours[nb_neibs - 1];
    nb_neibs--;
    nb_visited ++;
    puts("visited Pass");
}

nod*
    notvisited(){
    for(int i = 0 ; i < nb_nodes ; ++i)
        if(dijkstra[i]->dist == 2000000000)
            return dijkstra[i];
    return NULL;
}

void
    addNeib(nod* N){
    if(!N->end) {
        neighbours[nb_neibs] = N;
        nb_neibs++;
        N->visited = 1;
    }
    puts("addNeib Pass");
}
void
printPath(){
    ////////////
    printf("[ ");
    for(int i = 0 ; i < nb_neibs ; ++ i)
        printf("(%d, %d) %d",neighbours[i]->data->line, neighbours[i]->data->column, neighbours[i]->data->status);
    printf(" ]\n");
}
int distance(nod * N){
    return (goal->data->line-N->data->line)*(goal->data->line-N->data->line) + (goal->data->column-N->data->column)*(goal->data->column-N->data->column);
}
nod*
    findBestValue(){
    nod * minN = neighbours[0];
    int minD = neighbours[0]->dist + distance(neighbours[0]);
    int temp;
    for(int i = 1 ; i < nb_neibs ; ++ i)
        if((temp = neighbours[i]->dist + distance(neighbours[i]))< minD) {
            minD = temp;
            minN = neighbours[i];
        }
    return minN;
}


/*
#include "dijkstra.h"

nod* Path[1024];
int nb_neib = 0;

RRRobotMove*
    dijkstra(nod* D, nod * A){
    //////////////////////////
    D->dist = 0;
    nod * T = D;
    while(T != A){
        addNeib(T);
        T = closestOnPath();
        //printPath();
    }
    nod* tmp = A;
    int i = 0;
    while(tmp != D){
        tmp = tmp->prev;
        ++i;
    }
    i ++ ;
    RRRobotMove * moves = malloc(sizeof(moves)*i);
    tmp = A;
    moves[0] = i;
    while(tmp != D){
        moves[i] = tmp->move;
        tmp = tmp->prev;
        i --;
    }
    return moves;
}

void
    addNeib(nod* N){
    ////////////////
    int i ;
    for(i = 0 ; i < 7 ; ++i) // pb
        if(N->neib[i] != NULL && N->neib[i]->data->status != RR_ROBOT_DEAD){
            addToPath(N->neib[i]);
            if(N->neib[i]->dist > N->dist + 1){
                N->neib[i]->dist = N->dist + 1;
                N->neib[i]->prev = N;
            }
        }
    removeFromPath(N);
}

void
    printPath(){
    ////////////
    int i;
    printf("[ ");
   for(i = 0 ; i < nb_neib ; ++ i)
        printf("(%d, %d) %d",Path[i]->data->line, Path[i]->data->column, Path[i]->dist);
    printf(" ]\n");
}

nod*
    closestOnPath(){
    ////////////////
    int i;
    nod * min  = Path[0];
    for(i = 0 ; i < nb_neib ; ++i)
        if(Path[i]->dist < min->dist)
            min = Path[i];
    return min;
}

int isOnPath(nod* N){
    int i;
    for(i = 0 ; i < nb_neib ; ++i)
        if(Path[i] == N)
            return 1;
    return 0;
}

void
    addToPath(nod* N) {
    //////////////////
    if (!isOnPath(N)) {
        Path[nb_neib] = N;
        nb_neib++;
    }
}

void
    removeFromPath(nod * N){
    ////////////////////////
    nod * swap = Path[nb_neib-1] ;
    int i = 0 ;
    while (Path[i] != N && i < nb_neib)
        i++;
    Path[i] = swap ;
    nb_neib -- ;
}
*/



