//
// Created by enzo on 09/03/16.
    //

#include "dijkstra.h"

nod* Path[1024];
int nb_neib = 0;

RRRobotMove* dijkstra(nod* D, nod * A){
    nod * T = D;
    while(T != A){
        addNeib(T);
        T = closestOnPath();
    }
    nod* tmp = A;
    int i = 0;
    while(tmp != D){
        tmp = tmp->prev;
        ++i;
    }
    i ++ ;
    RRRobotStatus * moves = malloc(sizeof(moves)*i);
    tmp = A;
    moves[0] = i;
    while(tmp != D){
        moves[i] = tmp->data->status;
        tmp = tmp->prev;
        i --;
    }
    return moves;
}

void
    addNeib(nod* N){
    int i ;
    for(i = 0 ; i < 7 ; ++i){ // pb
        if(N->neib[i] != NULL &&N->neib[i]->data->status != RR_ROBOT_DEAD){
            N->neib[i]->prev = N;
            addToPath(N->neib[i]);
            if(N->neib[i]->dist > N->dist + 1)
                N->neib[i]->dist = N->dist + 1;
        }
    }
    removeFromPath(N);
}

void printPath(){
    int i;
    printf("[ ");
   for(i = 0 ; i < nb_neib ; ++ i)
        printf("(%d, %d) ",Path[i]->data->line, Path[i]->data->column);
    printf(" ]\n");
}

nod* closestOnPath(){
    int i;
    nod * min  = Path[0];
    for(i = 0 ; i < nb_neib ; ++i)
        if(Path[i]->dist < min->dist)
            min = Path[i];
    return min;
}

void addToPath(nod* N){
    Path[nb_neib] = N;
    nb_neib ++ ;
}

void removeFromPath(nod * N){
    nod * swap = Path[nb_neib-1] ;
    int i = 0 ;
    while (Path[i] != N && i < nb_neib)
        i++;
    Path[i] = swap ;
    nb_neib -- ;
}




