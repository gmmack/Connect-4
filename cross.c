#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WORD_LEN 20
#define WORD_LIMIT 100000

int wordCount = 0;
char words[ WORD_LIMIT ][ WORD_LEN + 1 ];

void readWords( char const *filename )
{
  FILE *fp = fopen( filename, "r" );
  if ( !fp ) {
    fprintf( stderr, "Can't open word file\n" );
    exit( EXIT_FAILURE );
  }

  // Read words with room for one extra character, so
  // we can tell if they're too long.
  char buffer[ WORD_LEN + 2 ];
  while ( fscanf( fp, "%21s", buffer ) == 1 ) {
    if ( strlen( buffer ) > WORD_LEN ) {
      fprintf( stderr, "Invalid word file\n" );
      exit( EXIT_FAILURE );
    }

    if ( wordCount >= WORD_LIMIT ) {
      fprintf( stderr, "Invalid word file\n" );
      exit( EXIT_FAILURE );
    }

    for ( int i = 0; buffer[ i ]; i++ )
      if ( buffer[ i ] < 'a' || buffer[ i ] > 'z' ) {
        fprintf( stderr, "Invalid word file\n" );
        exit( EXIT_FAILURE );
      }
        
    
    strcpy( words[ wordCount++ ], buffer );
  }

  fclose( fp );
}

bool getPattern( char *pat )
{
  char buffer[ WORD_LEN + 2 ];

  bool valid = false;
  while ( ! valid ) {
    printf( "pattern> " );
    int match = scanf( "%21s", buffer );
    if ( match == EOF )
      return false;
    if ( match == 1 && strlen( buffer ) <= WORD_LEN ) {
      // Assume pattern is valid unless we find a bad character.
      valid = true;
      for ( int i = 0; valid && buffer[ i ]; i++ )
        if ( buffer[ i ] != '?' &&
             ( buffer[ i ] < 'a' || buffer[ i ] > 'z' ) )
          valid = false;
    }

    if ( ! valid ) {
      printf( "Invalid pattern\n" );
      // Skip the rest of the line.
      int ch = getchar();
      while ( ch != EOF && ch != '\n' )
        ch = getchar();
    }
  }

  strcpy( pat, buffer );
  return true;
}

bool matches( char const *word, char const *pat ) {
  int pos = 0;
  while ( word[ pos ] && pat[ pos ] ) {
    if ( pat[ pos ] != '?' )
      if ( word[ pos ] != pat[ pos ] )
        return false;
    pos++;
  }

  // Return true if they both end at the same time.
  return word[ pos ] == pat[ pos ];
}

int main( int argc, char *argv[] )
{
  if ( argc != 2 ) {
    fprintf( stderr, "usage: cross <word-file>\n" );
    exit( EXIT_FAILURE );
  }

  readWords( argv[ 1 ] );

  char pat[ WORD_LEN + 1 ];
  while ( getPattern( pat ) ) {
    for ( int i = 0; i < wordCount; i++ )
      if ( matches( words[ i ], pat ) )
        printf( "%s\n", words[ i ] );
  }

  return EXIT_SUCCESS;
}
