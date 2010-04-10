#include "plantinfo.h"

#include "visettings.h"
#include "legend.h"
#include <stdio.h>
#include <string.h>

Plantinfo::Plantinfo( int x, int y, int width, int height )
  : Window( x, y, width, height )
{


}

#define INFO_PRINT( y, z ) { mvwprintw( mWindow, i++, 2, #y": %d        ", getAttr(plant)->z ); }

void Plantinfo::update()
{

  werase(mWindow);
  box( mWindow, 0, 0 );
  wattron( mWindow, COLOR_PAIR( DEFAULT_COLOR ) );

  if( getAttr(plant) )
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
    // Check if plant is talking
    GameState state = *getAttr( state );
    ++i;
    for( std::vector<Animation *>::iterator j = state.animations.begin(); j != state.animations.end(); j++ )
    {
      if( (*j)->type == TALK )
      {
        if( getAttr( plant )->objectID == ((Talk *)(*j))->plantID )
        {

          char *msg = ((Talk *)(*j))->message;
          bool nLine = false;


          for( int l = 0; l < 28; l++ )
          {
            if( msg[l] == '\n' )
            {
              nLine = true;
            }
          }

          while( strlen( msg ) > 28 || nLine )
          {
            nLine = false;
            char str[29];
            strncpy( str, msg, 28 );
            int n = 28;

            for( int l = 0; l < 28 && l < strlen(msg); l++ )
            {
              if( str[l] == '\n' )
              {

                str[l] = '\0';
                n = l;
                break;
              }

            }
            str[28] = '\0';
            mvwprintw( mWindow, i++, 2, "%s", str );
            msg += n+1;

            for( int l = 0; l < 28; l++ )
            {
              if( msg[l] == '\n' )
              {
                nLine = true;
                break;
              }
            }

          }
          mvwprintw( mWindow, i++, 2, "%s", msg );
        }
      }
    }


  } else {
    mvwprintw( mWindow, 1, 2, "Empty" );
  }

  box( mWindow, 0, 0 );
  wrefresh( mWindow );

}

