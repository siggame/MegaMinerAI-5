#include "minimap.h"
#include "legend.h"

Minimap::Minimap( int x, int y, int width, int height )
: Window( x, y, width, height )
{

}

void Minimap::newState()
{
  GameState state = *getAttr( state );
  for( int i = 0; i < getAttr(boardX); i++ )
    for( int j = 0; j < getAttr(boardY); j++ )
    {
      wattron( mWindow, COLOR_PAIR( BACKGROUND_COLOR ) );

      mvwaddch( mWindow, 1+j, 1+i, ACS_CKBOARD );

      wattroff( mWindow, COLOR_PAIR( BACKGROUND_COLOR ) );
    }

  bool plant = false;

  // Draw them plants.
  for( std::vector<Plant>::iterator i = state.plants.begin(); i != state.plants.end(); i++ )
  {


      wattron( mWindow, COLOR_PAIR( PLAYER_1_PIECE_COLOR+i->ownerID ) );

      int ch = ' ';

      mvwaddch( mWindow, i->y+1, i->x+1, ch );

      wattroff( mWindow, COLOR_PAIR( 10 ) );

  }

  if( !plant )
    setAttr( plant, 0 );

  update();
}
