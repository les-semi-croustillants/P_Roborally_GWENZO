#include "wobowall_e.h"

void robot_cpy(const RRRobot* from, RRRobot* to)
{
  memcpy(to, from, sizeof(RRRobot)) ;
}

void move_print(
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

void robot_print(const RRRobot* robot)
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

int main (int argc, char **argv)
{
  RRBoard board ;

  rr_board_init(&board, "board.txt") ;

  if(!board.tile_size) {
    printf("the board has no tile\n") ;
    return 0 ;
  }

  RRRobot robot ;
  robot.line = board.tiles[0].line ;
  robot.column = board.tiles[0].column ;
  robot.status = RR_ROBOT_S ;

  RRRobot prev_robot ;
  robot_cpy(&robot, &prev_robot) ;
  nod** Tab = malloc(sizeof(nod*)*50000);
  nod * D = initNod(&robot);
  initGraph(D, &board, Tab);
  robot_print(D->data);
  nod * goal = findNode(4, 4, RR_ROBOT_S);
 /* RRRobotMove* moves = byDijkstra(D, goal, getTab(), getId());

  for(unsigned int i = 2; i < moves[0]; ++i) {
    printf("%d \n", i);
    move_print(moves[i]) ;
    robot_cpy(&robot, &prev_robot) ;
    rr_board_play(&board, &robot, moves[i]) ;
  }
*/
  reverseDijkstra(goal, getTab(), getId());
    puts("bonjour");
    robot_print(D->data);
  dontStopTillGetEnough(D, goal, &board);
  freeGraph();
  free(Tab);
  //free(moves);
  freeNode(D);
  rr_board_destroy(&board) ;

  return 0 ;
}