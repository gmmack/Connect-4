#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printBoard( int rows, int cols, char board[ rows ][ cols ] )
{
  printf( "\n" );
  for ( int i = 0; i < rows; i++ ) {
    for ( int j = 0; j < cols; j++ )
      printf( "|%c", board[ i ][ j ] );
    printf( "|\n" );
  }
  
  for ( int j = 0; j < cols; j++ )
    printf( "+-" );
  printf( "+\n" );
  for ( int j = 0; j < cols; j++ )
    printf( " %d", ( j + 1 ) % 10 );
  printf( "\n" );
}

void clearBoard( int rows, int cols, char board[ rows ][ cols ] )
{
  for ( int i = 0; i < rows; i++ )
    for ( int j = 0; j < cols; j++ )
      board[ i ][ j ] = ' ';
}

bool winner( int rows, int cols, char board[ rows ][ cols ],
             int startRow, int startCol, int dRow, int dCol ) {
  // Number of X and O symbols in this sequence of locations
  int xcount = 0, ocount = 0;

  // Walk down the sequence of board spaces.
  for ( int k = 0; k < RUNLEN; k++ ) {

    // Figure out its row and column index and make sure it's on the board.
    int r = startRow + k * dRow;
    int c = startCol + k * dCol;
    if ( r < 0 || r >= rows || c < 0 || c >= cols )
      return false;

    // Count an X or an O if it's one of those.
    if ( board[ r ][ c ] == 'X' )
      xcount++;
    else if ( board[ r ][ c ] == 'O' )
      ocount++;
  }

  // We have a winner if it's all Xs or Os.
  return xcount == RUNLEN || ocount == RUNLEN;
}

int gameStatus( int rows, int cols, char board[ rows ][ cols ] )
{
  // Check for a winner from ever starting space.
  for ( int i = 0; i < rows; i++ )
    for ( int j = 0; j < cols; j++ )
      if ( winner( rows, cols, board, i, j, 1, 0 ) ||
           winner( rows, cols, board, i, j, 1, -1 ) ||
           winner( rows, cols, board, i, j, 1, 1 ) ||
           winner( rows, cols, board, i, j, 0, 1 ) )
        return WINNER;
  
  // See if there are stills ome empty spaces.
  for ( int i = 0; i < rows; i++ )
    for ( int j = 0; j < cols; j++ )
      if ( board[ i ][ j ] == ' ' )
        return PLAYING;

  return STALEMATE;
}

void makeMove( char player, int rows, int cols, char board[ rows ][ cols ] )
{
  // Keep prompting until we get a valid move.
  while ( true ) {
    printf( "%c move> ", player );
  
    int move = 0;
    int matches = scanf( "%d", &move );
    move -= 1;
  
    // If the move is valid, make it and return.
    if ( matches == 1 && move >= 0 && move < cols && board[ 0 ][ move ] == ' ' ) {
      int pos = 0;
      while ( pos + 1 < rows && board[ pos + 1 ][ move ] == ' ' )
        pos++;
      board[ pos ][ move ] = player;
      return;
    }

    // Just exit from here if we're done.
    if ( matches == EOF )
      exit( EXIT_SUCCESS );
  
    printf( "Invalid move\n" );

    // Eat the rest of the input line.
    int ch = getchar();
    while ( ch != EOF && ch != '\n' )
      ch = getchar();
  }
}
