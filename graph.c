#include "board.h"
#include <stdlib.h>
#include <unistd.h>

int id = 0;
int nb_elem_tab = 0;
int nb_elem_tab2 = 0;
int nb_elem_tab3 = 0;
nod* Tab2[1000];
nod * Tab3[1024];
FILE* fdp;
nod* mort;


nod** getTab(){
    return Tab3;
}

int getlength(){
    return nb_elem_tab3;
}

static void
    robot_print(const RRRobot* robot){
    /////////////////////////////////
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

void printTab(){
    int i;
    for(i = 0 ; i < nb_elem_tab3 ; ++ i)
        robot_print(Tab3[i]->data);
}

nod*
    arrive(){
    return Tab2[21];
}

void construitGraph2(nod* N, const RRBoard* board, nod** Tab){

    Tab3[nb_elem_tab3] = N;
    nb_elem_tab3 ++;

    unsigned int h = 0;
    h = !h;
    printf("l'entier le plus grand%d\n", h);
    RRRobot * newbot = malloc(sizeof(RRRobot));
    newbot->status = RR_ROBOT_DEAD;
    newbot->column = 1000;
    newbot->line = 1000;
    mort = initNod(newbot, RR_MOVE_FORWARD_1);

    fdp = fopen("graph.dot", "w");
    fwrite("digraph b {\n" , 1 , 12, fdp );

    N->id = id;
    construitGraph(N, board, Tab);
    printf ("il y a %d nodes dans le graph\n", id);

    fwrite("}" , 1 , 1, fdp );

}

void
    construitGraph(nod* N, const RRBoard* board, nod** Tab){
    ////////////////////////////////////////////////////////

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
        if (getStatus(N->neib[i]->data) != RR_ROBOT_DEAD && inTab(N->neib[i]->data, Tab2, nb_elem_tab2) == NULL) {
            if (N->neib[i]->data->line == 0 && N->neib[i]->data->column == 0 && N->neib[i]->data->status == RR_ROBOT_S)
                printf("DHZDHZIDHQSLKDHQSKLDHDL\n");
            construitGraph(N->neib[i], board, Tab);
        }

    }
}

void
    newHorizon(int i, nod* N, RRRobotMove move, nod** Tab, const RRBoard* board){
    ////////////////////////////////////////////
    nod * replace;
    RRRobot * temp = duplicateBot(N->data);
    rr_board_play (board, temp, move);

    if ((replace = inTab(temp, Tab, nb_elem_tab)) != NULL)
        N->neib[i] = replace;

    else {
        if(N->neib[i]->data->column < 0 && N->neib[i]->data->line < 0)
            N->neib[i] = mort;

        N->neib[i] = initNod(temp, move);
        addTab(N->neib[i], Tab);

        N->neib[i]->id = id++;
        Tab3[nb_elem_tab3] = N->neib[i];
        nb_elem_tab3 ++ ;

        completeGraphviz(N, N->neib[i]);
    }

    if(inTab(N->data, Tab2, nb_elem_tab2) == NULL) {
        Tab2[nb_elem_tab2] = N;
        nb_elem_tab2++;
    }
    if (N->data->line == 0 && N->data->column == 0 && N->data->status == RR_ROBOT_S)
        robot_print(N->neib[i]->data);
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

nod*
    inTab(RRRobot* bot, nod** T, int nb){
    ///////////////////////////////////
    int x = bot->line;
    int y = bot->column;
    RRRobotStatus status = bot->status;
    int i;
    for(i = 0 ; i < nb; ++i)
        if(T[i]->data->line == x && T[i]->data->column == y && T[i]->data->status == status)
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
    findNode(int line, int column){
    /////////////////
    int i;
    for(i = 0 ; i < nb_elem_tab3 ; ++i)
        if(Tab3[i]->data->line == line && Tab3[i]->data->column == column)
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

    //robot_print(N1->data);
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
    if (x1 < 0 || y1 < 0) {
        strcat(str, "XXX");
    }
    else {
        strcat(str, cx1);
        strcat(str, cy1);
        strcat(str, cd1);
    }
    strcat ( str, " -> " );
    if (x2 < 0 || y2 < 0) {
        strcat(str, "XXX");
    }
    else{
        strcat(str, cx2);
        strcat(str, cy2);
        strcat(str, cd2);
    }
    strcat(str, "; ");
    strcat(str, "\n");
    //puts(str);
    fwrite(str , 1 , sizeof(str) , fdp );
}





