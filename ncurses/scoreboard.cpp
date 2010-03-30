#include "scoreboard.h"
#include "legend.h"

Scoreboard::Scoreboard( int x, int y, int width, int height ) : Window( x, y, width, height )
{
  turn = 0;
  p1score = p2score = 0;
//  p1light = p2light = 0;
//  p1water = p2water = 0;
}

void Scoreboard::update()
{
  wattrset( mWindow, COLOR_PAIR( 9 ) );
  
  int line = 1;
  
  mvwprintw( mWindow, line++, 2, "Turn: %d      ", turn );
  
  wattrset( mWindow, COLOR_PAIR( PLAYER_1_COLOR ) );
  mvwprintw( mWindow, line++, 2, "---------------------------" );
  wattron( mWindow, A_BOLD );
  mvwprintw( mWindow, line++, 3, "Player 1" );
  wattroff( mWindow, A_BOLD );
  mvwprintw( mWindow, line++, 2, "---------------------------" );
  mvwprintw( mWindow, line++, 3, "Score: %d       ", p1score );
//  mvwprintw( mWindow, 5, 3, "Light: %d      ", p1light );
//  mvwprintw( mWindow, 6, 3, "Water: %d      ", p1water );
  
  wattrset( mWindow, COLOR_PAIR( PLAYER_2_COLOR ) );
  
  line = 8;
  
  mvwprintw( mWindow, line++, 2, "---------------------------" );
  wattron( mWindow, A_BOLD );
  mvwprintw( mWindow, line++, 3, "Player 2" );
  wattroff( mWindow, A_BOLD );
  mvwprintw( mWindow, line++, 2, "---------------------------" );
  mvwprintw( mWindow, line++, 3, "Score: %d       ", p2score );
  
  wattrset( mWindow, COLOR_PAIR( INSTRUCTIONS ) );
  
  line = 24;
  
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

void Scoreboard::updateScore( int rTurn, int p1Score, int p2Score )
{
 turn = rTurn;
 p1score = p1Score;
 p2score = p2Score;
// p1light = rP1light;
// p1water = rP1water;
// p2light = rP2light;
// p2water = rP2water;
 
}
