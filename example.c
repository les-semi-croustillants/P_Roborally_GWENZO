//#include "board.h"
#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void robot_cpy(const RRRobot* from, RRRobot* to)
{
  memcpy(to, from, sizeof(RRRobot)) ;
}

void move_print(
    RRRobotMove move
    )
{
  static const char* translations[7] =
  {
    "moving forward 1 tile",
    "moving forward 2 tiles",
    "moving forward 3 tiles",
    "moving backward 1 tile",
    "rotating left",
    "rotating right",
    "u turning"
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
  robot.status = RR_ROBOT_N ;

  RRRobot prev_robot ;
  robot_cpy(&robot, &prev_robot) ;
    nod** Tab = malloc(sizeof(nod*)*1000);
  nod * D = initNod(&robot, RR_MOVE_FORWARD_1);

  construitGraph2(D, &board, Tab);
    //printTab();
    //sleep(5);
    robot_print(D->data);
    robot_print(findNode(2, 2)->data);
    RRRobotMove* moves = bydijkstra(D, findNode(2, 2), getTab(), getlength());

  for(unsigned int i = 1; i < moves[0]; ++i)
  {
    move_print(moves[i]) ;
    robot_cpy(&robot, &prev_robot) ;
    rr_board_play(&board, &robot, moves[i]) ;
    //robot_print(&robot) ;

  }

  rr_board_destroy(&board) ;

  return 0 ;
}
