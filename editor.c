#include "board_display.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) 
{
  if(argc < 2)
  {
    printf("usage : %s <board filename>\n", argv[0]) ;
    return 1 ;
  }

  RRBoard board ;

  /*check whether file exists*/
  if(access(argv[1], F_OK) != -1)
  {
    /* load the file as a board */
    rr_board_init(&board, argv[1]) ;

    /* backup the input board */
    int f_size = strlen(argv[1]) ;
    char* backup_filename = malloc((f_size+8) * sizeof(char)) ;
    snprintf(backup_filename, f_size + 8, "%s.backup", argv[1]) ;
    printf("saving initial board to %s\n", backup_filename) ;
    rr_board_save(&board, backup_filename) ;
    free(backup_filename) ;
  }
  else
  {
    /* initialize an empty board */
    board.tile_size = 0 ;
    board.tiles = NULL ;
    board.width = 0 ;
    board.height = 0 ;
  }

  /* edit the board */
  rr_board_edit(&board, "roborally.svg") ;

  /* save the board */
  rr_board_save(&board, argv[1]) ;

  /* save the board */
  rr_board_destroy(&board) ;

  return 0 ;
}
