#include "board_display.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) 
{
  if(argc < 2)
  {
    printf("usage : %s <board filename>\n", argv[0]) ;
    return 1 ;
  }

  RRBoard board ;

  rr_board_init(&board, argv[1]) ;

  if(!board.tile_size)
  {
    printf("the board has no tiles\n") ;
    rr_board_destroy(&board) ;
    return 0 ;
  }

  RRRobot robot ;
  robot.line = -1 ;
  robot.column = -1 ;
  robot.status = RR_ROBOT_DEAD ;

  RRRobot prev_robot ;
  prev_robot.line = -1 ;
  prev_robot.column = -1 ;
  prev_robot.status = RR_ROBOT_DEAD ;

  rr_board_show(&board, "roborally.svg", &robot, &prev_robot) ;

  rr_board_destroy(&board) ;

  return 0 ;
}
