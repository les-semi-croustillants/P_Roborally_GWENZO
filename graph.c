#include "graph.h"
#include "board.h"

int id = 0;
int nb_elem_tab = 0;
int nb_elem_tab2 = 0;
int nb_elem_tab3 = 0;
nod* Tab2[50000];
nod * Tab3[50000];
FILE* fdp;
nod* mort;

nod** getTab(){ return Tab3; }
int getId(){ return id; }

void initGraph(nod* N, const RRBoard* board, nod** Tab){
    Tab3[nb_elem_tab3] = N;
    nb_elem_tab3 ++;

    RRRobot * newbot = malloc(sizeof(RRRobot));
    newbot->status = RR_ROBOT_DEAD;
    newbot->column = 1000;
    newbot->line = 1000;
    mort = initNod(newbot);

    Tab3[nb_elem_tab3] = mort;
    nb_elem_tab3 ++;

    fdp = fopen("graph.dot", "w");
    fwrite("digraph b {\n" , 1 , 12, fdp );

    buildGraph(N, board, Tab);

    fwrite("}" , 1 , 1, fdp );
    fclose(fdp);
}

void
buildGraph(nod* N, const RRBoard* board, nod** Tab){
    ////////////////////////////////////////////////////////

    //RRRobot * bot = N->data;
    newHorizon(0, N, RR_MOVE_FORWARD_1,  Tab, board);
    newHorizon(1, N, RR_MOVE_FORWARD_2,  Tab, board);
    newHorizon(2, N, RR_MOVE_FORWARD_3,  Tab, board);
    newHorizon(3, N, RR_MOVE_BACKWARD_1, Tab, board);
    newHorizon(4, N, RR_TURN_LEFT,       Tab, board);
    newHorizon(5, N, RR_TURN_RIGHT,      Tab, board);
    newHorizon(6, N, RR_U_TURN,          Tab, board);

    for(int i = 0 ; i < 7 ; ++i) {
        if (getStatus(N->neib[i]->data) != RR_ROBOT_DEAD
            && inTab(N->neib[i]->data, Tab2, nb_elem_tab2) == NULL)
            buildGraph(N->neib[i], board, Tab);
    }
}

void
newHorizon(int i, nod* N, RRRobotMove move, nod** Tab, const RRBoard* board){
    ////////////////////////////////////////////
    nod * replace;
    RRRobot * temp = duplicateBot(N->data);
    rr_board_play (board, temp, move);
    if(temp->status == RR_ROBOT_DEAD) {
        N->neib[i] = mort;
        free(temp);
    }
    else {
        if ((replace = inTab(temp, Tab3, nb_elem_tab)) != NULL) {
            N->neib[i] = replace;
            free(temp);
        }
        else {
            N->neib[i] = initNod(temp);
            addTab(N->neib[i], Tab);
            Tab3[nb_elem_tab3] = N->neib[i];
            nb_elem_tab3 ++ ;
        }
    }
    if(inTab(N->data, Tab2, nb_elem_tab2) == NULL) {
        Tab2[nb_elem_tab2] = N;
        nb_elem_tab2++;
    }
    completeGraphviz(N, N->neib[i]);
    dyntab_push(N->neib[i]->parent, N);
}

RRRobot *
duplicateBot(const RRRobot * bot){
    //////////////////////////////////
    RRRobot * newbot = malloc(sizeof(RRRobot));
    memcpy(newbot, bot, sizeof(RRRobot));
    return newbot;
}

nod*
initNod(RRRobot * bot){
    ///////////////////////
    nod * N = malloc(sizeof(nod));
    N->data = bot;
    nod** tab = malloc(sizeof(nod*)*7);
    N->neib = tab;
    N->parent = malloc(sizeof(dyntab));
    dyntab_init(N->parent, sizeof(nod*));
    N->id = id;
    ++ id;
    int i;
    for(i = 0 ; i < 7 ; i++)
        N->neib[i] = NULL;
    N->dist = INT_MAX;
    return N;
}

void
freeNode(nod * N){

    free(N->neib);
    free(N);
}

nod*
inTab(RRRobot* bot, nod** T, int nb){
    ///////////////////////////////////
    int x = bot->line;
    int y = bot->column;
    RRRobotStatus Status = bot->status;
    for(int i = 0 ; i < nb; ++i)
        if(T[i]->data->line == x
           && T[i]->data->column == y
           && T[i]->data->status == Status)
            return T[i];
    return NULL;
}

void
addTab(nod* N, nod** T){
    ////////////////////////
    T[nb_elem_tab] = N;
    nb_elem_tab ++ ;
}

nod*
findNode(int line, int column, RRRobotStatus status){
    /////////////////
    int i;
    for(i = 0 ; i < nb_elem_tab3 ; ++i)
        if(Tab3[i]->data->line == line
           && Tab3[i]->data->column == column
           && Tab3[i]->data->status == status)
            return Tab3[i];
    return NULL;
}

int sizeInt(int n){
    int i = 0;
    while(n != 0) {
        n = n / 10;
        ++i;
    }
    return i;
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void completeGraphviz(nod* N1, nod* N2) {
    int x1 = N1->data->line;
    int y1 = N1->data->column;
    int x2 = N2->data->line;
    int y2 = N2->data->column;
    int d1 = N1->data->status;
    int d2 = N2->data->status;

    char cx1[5];
    char cy1[5];
    char cx2[5];
    char cy2[5];
    char cd1[1];
    char cd2[1];
    char str[80] = "";

    itoa(x1, cx1);
    itoa(y1, cy1);
    itoa(x2, cx2);
    itoa(y2, cy2);
    itoa(d1, cd1);
    itoa(d2, cd2);
    if (x1 == 1000 || y1 == 1000) {
        strcat(str, "XXX");
    }
    else {
        strcat(str, cx1);
        strcat(str, cy1);
        strcat(str, cd1);
    }
    strcat ( str, " -> " );
    if (x2 == 1000 || y2 == 1000) {
        strcat(str, "XXX");
    }
    else{
        strcat(str, cx2);
        strcat(str, cy2);
        strcat(str, cd2);
    }
    strcat(str, "; ");
    strcat(str, "\n\0");
    fwrite(str , 1 , strlen(str) , fdp );
}

void freeGraph(){
    for(int i = nb_elem_tab3 - 1  ; i > 0 ; --i){
        free(Tab3[i]->data);
        freeNode(Tab3[i]);
    }
    nb_elem_tab3 = 0;
}


