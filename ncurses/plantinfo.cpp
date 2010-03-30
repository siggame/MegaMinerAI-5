#include "plantinfo.h"

Plantinfo::Plantinfo( int x, int y, int width, int height )
  : Window( x, y, width, height )
{
  plant = 0;
  
}

#define INFO_PRINT( y, z ) { mvwprintw( mWindow, i++, 2, #y": %d        ", plant->z ); }

void Plantinfo::update()
{
  
  werase(mWindow);
  box( mWindow, 0, 0 );
  
  
  if( plant )
  {
    mvwprintw( mWindow, 1, 2, "Plant Info" );
    int i = 3;
       
    INFO_PRINT( Health, health );
    INFO_PRINT( Root Level, rootLevel );
    INFO_PRINT( Leaf Level, leafLevel );
    INFO_PRINT( Flower Level, flowerLevel );
    INFO_PRINT( Root LvlUp, rootLevelUp );
    INFO_PRINT( Leaf LvlUp, leafLevelUp );
    INFO_PRINT( Flower LvlUp, flowerLevelUp );
    ++i;
    // Check if plant is talking
    
    

  } else {
    mvwprintw( mWindow, 1, 2, "Empty" );
  }
    
  box( mWindow, 0, 0 );
  wrefresh( mWindow );
  
}

void Plantinfo::givePlant( Plant *p )
{
  plant = p;
}
