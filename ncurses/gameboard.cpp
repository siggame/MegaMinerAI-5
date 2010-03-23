#include "gameboard.h"
#include <string.h>

Gameboard::Gameboard( int x, int y, int width, int height )
: Window( x, y, width, height )
{

  board = new char *[width-2];
  for( int i = 0; i < width-2; i++ )
  {
    board[i] = new char[height-2];
    // Initialize board to zeros
    memset( board[i], 0, sizeof(char)*(height-2) );
  }

  boardX = (width-2)/2;
  boardY = (height-2)/2;
  curX = curY = 0;

  setupPieces();
  
}

void Gameboard::setupPieces()
{
  init_color( COLOR_RED, 0x5C, 0x40, 0x33 );
  
  init_pair(18, COLOR_BLACK, COLOR_CYAN );
    
  // Roots
  init_pair(10, COLOR_RED, COLOR_BLACK );
  init_pair(14, COLOR_RED, COLOR_BLACK );
  // Leaf
  init_pair(11, COLOR_GREEN, COLOR_BLACK );
  init_pair(15, COLOR_GREEN, COLOR_BLACK );
  // Flower
  init_pair(12, COLOR_YELLOW, COLOR_BLACK );
  init_pair(16, COLOR_YELLOW, COLOR_BLACK );
  // Bark
  init_pair(13, COLOR_RED, COLOR_BLACK );
  init_pair(17, COLOR_RED, COLOR_BLACK );
  
  // Background
  init_pair( 9, COLOR_WHITE, COLOR_BLACK );
  
  // Header

  // Player 1
  init_pair( 8, COLOR_CYAN, COLOR_BLACK );
  
  pieces[0][P_ROOT].keyCode0 = 'r';
  pieces[0][P_ROOT].color = 10;
  pieces[0][P_LEAF].keyCode0 = 'l';
  pieces[0][P_LEAF].color = 11;
  pieces[0][P_FLOWER].keyCode0 = 'f';
  pieces[0][P_FLOWER].color = 12;
  pieces[0][P_BARK].keyCode0 = 'b';
  pieces[0][P_BARK].color = 13;
  
  pieces[1][P_ROOT].keyCode0 = 'R';
  pieces[1][P_ROOT].color = 14;
  pieces[1][P_LEAF].keyCode0 = 'L';
  pieces[1][P_LEAF].color = 15;
  pieces[1][P_FLOWER].keyCode0 = 'F';
  pieces[1][P_FLOWER].color = 16;
  pieces[1][P_BARK].keyCode0 = 'B';
  pieces[1][P_BARK].color = 17;
  
  background.keyCode0 = ACS_CKBOARD;//ACS_LANTERN;
  background.color = 9;
}

void Gameboard::newState( GameState state )
{
  
    // Clear the board

  for( int i = 0; i < boardX; i++ )
    for( int j = 0; j < boardY; j++ )
    {
      if( curX == i && curY == j )
        wattron( mWindow, COLOR_PAIR( 18 ) );

      mvwaddch( mWindow, 1+j*2, 1+i*2, background.keyCode0 );
      mvwaddch( mWindow, 1+j*2, 2+i*2, background.keyCode0 );
      mvwaddch( mWindow, 2+j*2, 1+i*2, background.keyCode0 );
      mvwaddch( mWindow, 2+j*2, 2+i*2, background.keyCode0 );

      if( curX == i && curY == j )
        wattroff( mWindow, COLOR_PAIR( 18 ) );
    }

  // Draw them plants.
  for( std::vector<Plant>::iterator i = state.plants.begin(); i != state.plants.end(); i++ )
  {
      //char *piece = &board[i->x][i->y];
	    
      Piece *currentPiece = &pieces[i->ownerID][i->objectID];
      if( i->x == curX && i->y == curY )
        wattron( mWindow, COLOR_PAIR( 18 ) );
      else
        wattron( mWindow, COLOR_PAIR( currentPiece->color ) );

      int ch = 0;      

      // Health Progression:
      // We can modify these numbers:
      if( i->health >= 100 )
        ch = ACS_GEQUAL;
      else if( i->health >= 75 )
        ch = '>';
      else if( i->health >= 50 )
        ch = '=';
      else if( i->health >= 25 )
        ch = '<';
      else
        ch = ACS_LEQUAL;
      mvwaddch( mWindow, i->y*2+2, i->x*2+2, ch );
      
      // Flower
      if( i->flower )
        ch = 'F';
      else
        ch = ' ';
      mvwaddch( mWindow, i->y*2+1, i->x*2+1, ch );

      // Root 
      if( i->root )
        ch = 'R';
      else
        ch = ' ';
      mvwaddch( mWindow, i->y*2+2, i->x*2+1, ch );
      // Leaves
      if( i->leaf )
        ch = 'L';
      else
        ch = ' ';
      mvwaddch( mWindow, i->y*2+1, i->x*2+2, ch );

      
      if( i->x == curX && i->y == curY )
        wattroff( mWindow, COLOR_PAIR( 18 ) );
      else
        wattroff( mWindow, COLOR_PAIR( currentPiece->color ) );
      
  }
  
}

void Gameboard::setCursor( int x, int y )
{
  curX = x;
  curY = y;
}
