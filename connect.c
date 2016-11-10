#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "board.h"

int main()
{
  int rows, cols;
  printf( "Rows and cols> " );

  if ( scanf( "%d%d", &rows, &cols ) != 2 || rows < RUNLEN || cols < RUNLEN ||
       rows > RUNLEN + 16 || cols > RUNLEN + 16 ) {
    fprintf( stderr, "Invalid board size\n" );
    exit( EXIT_FAILURE );
  }

  char board[ rows ][ cols ];
  clearBoard( rows, cols, board );

  int status;
  char player = 'O';
  do {
    // Switch players.
    player = ( player == 'X' ) ? 'O' : 'X';

    printBoard( rows, cols, board );
    makeMove( player, rows, cols, board );
  } while ( ( status = gameStatus( rows, cols, board ) ) == PLAYING );

  printBoard( rows, cols, board );
  
  if ( status == WINNER )
    printf( "Player %c wins\n", player );
  else
    printf( "Stalemate\n" );

  return EXIT_SUCCESS;
}
