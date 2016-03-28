#include "wobowall_e.h"

#define C_95 126;

static void move_print(
        RRRobotMove move
)
{
    static const char* translations[8] =
            {
                    "moving forward 1 tile",
                    "moving forward 2 tiles",
                    "moving forward 3 tiles",
                    "moving backward 1 tile",
                    "rotating left",
                    "rotating right",
                    "u turning",
                    "not moving"
            } ;
    printf("%s\n", translations[move]) ;
}

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

int fact(int a){
    int res = 1;
    for(int i = 1 ; i <= a ; ++i)
        res = res*i;
    return res;
}

int comb(int n, int p){
    return (fact(n)/(fact(p)*fact(n-p)));
}

int nbin(RRRobotMove* deck, RRRobotMove move){
    int nb =0;
    for(int i = 0 ; i < 9 ; ++i){
        if(deck[i] == move)
            ++nb;
    }
    return nb;
}
/*
RRRobotMove** permutations(RRRobotMove* deck, int n, int p){
    RRRobotMove** permute = malloc(sizeof(RRRobotMove)* 5 * 126);
    int l = 0;
    int k = 0;

    for(int i = 0 ; i < 5 ; ++i)
        for(int j = 0 ; j < 126 ; ++j){
            if(l == i+1) {
                k = (k + 1) % 9;
                l = 0;
            }
                permute[j][i] = deck[k];
            l++;
        }
    for(int i = 0 ; i < 126 ; ++i){
        for(int j = 0 ; j < 5 ; ++j)
            move_print(permute[i][j]);
        puts("");
    }

    return permute;
}
 */

static void swap(RRRobotMove* deck, int i, int j)
{
    RRRobotMove temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
}

RRRobotMove* duplicate(RRRobotMove* deck){
    RRRobotMove * newdeck = malloc(sizeof(RRRobotMove)*5);
    for(int i = 0 ; i < 5 ; ++i)
        newdeck[i]= deck[i];
    return newdeck;
}

void permute(RRRobotMove * deck, int start, int end, dyntab* P)
{
    RRRobotMove * newdeck = duplicate(deck);
    dyntab_push(P, &newdeck);
    /*for(int k = 0 ; k < 5 ; ++k)
        printf("%d -", newdeck[k]);
    puts("");
    sleep(1);*/
    if(start == end)
    {
        return;
    }

    permute(newdeck, start + 1, end, P);
    int i;
    for(i = start + 1; i < end; i++)
    {
        if(newdeck[start] == newdeck[i])
            continue;
        swap(newdeck, start, i);
        permute(newdeck, start + 1, end, P);
        swap(newdeck, start, i);
    }
    for(int k = 0 ; k < 5 ; ++k)
        printf("%d -", newdeck[k]);
    puts("");
}

dyntab* mainsPossibles(int size, int sizeM){
    dyntab* P = malloc(sizeof(dyntab));
    dyntab_init(P, sizeof(RRRobotMove*));
    RRRobotMove *T = malloc(sizeof(RRRobotMove)*5);
    for(int i = 0 ; i < 5 ; ++i)
        T[i]= i ;
    dyntab_push(P, &T);
    RRRobotMove* L;
    dyntab_get(P, 0, &L);
    //printf("valeur de Ppop,%p T %p\n", L = dyntab_return(P, T, sizeof(RRRobotMove*)), T);
    /*for(int k = 0 ; k < 5 ; ++k)
        printf("%d -", L[k]);
    puts("");
    sleep(5);*/
    int i = 0;
    while(1){
        if(i == size-1){
            if(T[i]+1 < sizeM){
                T[i] =T[i]+1;
                T = duplicate(T);
                dyntab_push(P, &T);;
                i = 0;
            }
            else break;
        }
        else{
            if(T[i] < T[i + 1] - 1){
                T[i] =T[i]+1;
                T = duplicate(T);
                dyntab_push(P, &T);
                i = 0;
            }
            else
                ++i;
        }
    }

    /*puts("");
    printf("%p\n",dyntab_return(P, 3, sizeof(RRRobotMove *)));

    sleep(10);*/
    return P;
}

RRRobotMove* drawCards(){
    RRRobotMove *deck = malloc(sizeof(RRRobotMove)*9);
    for(int i = 0 ; i < 9 ; ++i)
        deck[i] = rand()%7;
    return deck;
}

int manhattanDistance(RRRobot* A, RRRobot* B){
    return (abs(A->column - B->column) + abs(A->line - B->line));
}

void copySequence(RRRobotMove* Sdest, RRRobotMove*Ssrc){
    for(int i = 0 ; i < 5 ; ++i)
        Sdest[i] = Ssrc[i];
}

nod* whosNext(nod* N, nod* goal, RRRobotMove** permutations, RRRobotMove* sequence, RRBoard* board){
    int dist = INT_MAX;
    int newdist;
    RRRobot * bestRobot;
    RRRobot * temp;
    for(int i = 0; i < 126 ; ++i) {
        puts("i");
        for(int k = 0 ; k < 5 ; ++k)
            printf("%d -", permutations[i][k]);
        puts("");
        robot_print(N->data);
        temp = duplicateBot(N->data);
        for (int j = 0; j < 5; ++j) {
            printf("%d, %d\n", i, j);
            move_print(permutations[i][j]);
            puts("j");
            if(temp->status == RR_ROBOT_DEAD) break;
            if(temp->line == goal->data->line
               && temp->column == goal->data->column
               && temp->status == goal->data->status){
                copySequence(sequence, permutations[i]);
                nod* best = inTab(bestRobot->line, bestRobot->column, bestRobot->status);
                free(temp);
                return best;
            }
            puts("caca");
            rr_board_play(board, temp, permutations[i][j]);
            puts("caca");
        }
        if(dist > (newdist = inTab(temp->line, temp->column, temp->status)->goaldist) && temp->status != RR_ROBOT_DEAD){
            dist = newdist;
            free(bestRobot);
            bestRobot = temp;
            copySequence(sequence, permutations[i]);
        }
        else
            free(temp);
    }
    nod* best = inTab(bestRobot->line, bestRobot->column, bestRobot->status);
    free(temp);
    return best;
}

void dontStopTillGetEnough(nod* N, nod* goal, RRBoard* board){
    RRRobotMove* deck = drawCards();
    RRRobotMove* sequence = calloc(5, sizeof(RRRobotMove));
    puts("test");
    robot_print(N->data);
    puts("voici votre main :");
    for (int i = 0 ; i < 9 ; ++i)
        move_print(deck[i]);
    puts("");
    dyntab t;
    dyntab_init(&t, sizeof(RRRobotMove*));
    dyntab * P = mainsPossibles(5, 9);
    int size = P->size;
    puts("cacaaaaaaaaaaa");
    /*RRRobotMove* newdeck = (RRRobotMove*)dyntab_return(P, 4, sizeof(RRRobotMove *));
    for(int k = 0 ; k < 5 ; ++k)
        printf("%d -", newdeck[k]);
    puts("");
    sleep(10);*/
    for(int i = 0 ; i < size ; ++i) {
        RRRobotMove* dest;
        dyntab_get(P, i, &dest);
        permute(dest, 0, 5, P);
        puts("#######");
    }
    printf("nb_permutations %d \n", P->size);

    //RRRobotMove** moves = permutations(deck, 9, 5);
    puts("test");
    robot_print(N->data);

    nod * nextstep = N;

    puts("voici votre main :");
    for (int i = 0 ; i < 9 ; ++i)
        move_print(deck[i]);
    puts("");

    RRRobotMove** moves = malloc(sizeof(RRRobotMove*)*P->size);
    for(int i = 0 ; i < P->size ; ++i){
       dyntab_get(P, i, &moves[i]);
       for(int k = 0 ; k < 5 ; ++k)
            moves[i][k] = deck[(int)moves[i][k]];
    }

    while(nextstep != goal)
        nextstep = whosNext(nextstep, goal, moves, sequence, board);

}

