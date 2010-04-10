#include "scoreboard.h"
#include "legend.h"
#include "visettings.h"

Scoreboard::Scoreboard( int x, int y, int width, int height ) : Window( x, y, width, height )
{

}

void Scoreboard::update()
{
  wattrset( mWindow, COLOR_PAIR( INSTRUCTIONS ) );

  int line = 1;

  int red = 0;
  int blue = 0;

  for( std::vector<Plant>::iterator i = getAttr( state )->plants.begin(); i != getAttr( state )->plants.end(); i++ )
  {
    // Count Red Plants
    if( i->ownerID == 0 )
      ++red;
    else
      ++blue;
  }

  setAttr( player1Plants, red );
  setAttr( player2Plants, blue );

  mvwprintw( mWindow, line++, 2, "Turn: %d      ", getAttr( turnNumber ) );

  wattrset( mWindow, COLOR_PAIR( PLAYER_1_COLOR ) );
  mvwprintw( mWindow, line++, 2, "---------------------------" );
  wattron( mWindow, A_BOLD );
  mvwprintw( mWindow, line++, 3, getAttr( player1Name ) );
  wattroff( mWindow, A_BOLD );
  mvwprintw( mWindow, line++, 2, "---------------------------" );
  mvwprintw( mWindow, line++, 3, "Score: %d       ", getAttr( player1Score ) );
  mvwprintw( mWindow, line++, 3, "Light: %d       ", getAttr( player1Light ) );
  mvwprintw( mWindow, line++, 3, "Plants: %d      ", red );


  wattrset( mWindow, COLOR_PAIR( PLAYER_2_COLOR ) );

  line = 9;

  mvwprintw( mWindow, line++, 2, "---------------------------" );
  wattron( mWindow, A_BOLD );
  mvwprintw( mWindow, line++, 3, getAttr( player2Name ) );
  wattroff( mWindow, A_BOLD );
  mvwprintw( mWindow, line++, 2, "---------------------------" );
  mvwprintw( mWindow, line++, 3, "Score: %d       ", getAttr( player2Score ) );
  mvwprintw( mWindow, line++, 3, "Light: %d       ", getAttr( player2Light ) );
  mvwprintw( mWindow, line++, 3, "Plants: %d      ", blue );


  wattrset( mWindow, COLOR_PAIR( INSTRUCTIONS ) );

  line = getAttr( maxY )*2 - 12;

  mvwprintw( mWindow, line++, 3, "Visualizer Usage:" );
  mvwprintw( mWindow, line++, 3, "Q     | Quit" );
  mvwprintw( mWindow, line++, 3, "P     | Pause/Play" );
  mvwprintw( mWindow, line++, 3, "R     | Rewind" );
  mvwprintw( mWindow, line++, 3, "+     | Increase Speed" );
  mvwprintw( mWindow, line++, 3, "-     | Decrease Speed" );
  mvwprintw( mWindow, line++, 3, ">     | Go ahead one frame" );
  mvwprintw( mWindow, line++, 3, "<     | Go back one frame" );
  mvwprintw( mWindow, line++, 3, "E     | Go to last frame" );
  mvwprintw( mWindow, line++, 3, "S     | Go to first frame" );
  mvwprintw( mWindow, line++, 3, "Left  | Move Cursor Left" );
  mvwprintw( mWindow, line++, 3, "Right | Move Cursor Right" );
  mvwprintw( mWindow, line++, 3, "Up    | Move Cursor Up" );
  mvwprintw( mWindow, line++, 3, "Down  | Move Cursor Down" );


  wattroff( mWindow, COLOR_PAIR( 8 ) );

  wrefresh( mWindow );

}
