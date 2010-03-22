#include "scoreboard.h"

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
  mvwprintw( mWindow, 1, 2, "Turn: %d      ", turn );
  
  wattrset( mWindow, COLOR_PAIR( 8 ) );
  mvwprintw( mWindow, 2, 2, "----------------" );
  wattron( mWindow, A_BOLD );
  mvwprintw( mWindow, 3, 3, "Player 1" );
  wattroff( mWindow, A_BOLD );
  mvwprintw( mWindow, 4, 2, "----------------" );
  mvwprintw( mWindow, 5, 3, "Score: %d       ", p1score );
//  mvwprintw( mWindow, 5, 3, "Light: %d      ", p1light );
//  mvwprintw( mWindow, 6, 3, "Water: %d      ", p1water );
  
  mvwprintw( mWindow, 8, 2, "----------------" );
  wattron( mWindow, A_BOLD );
  mvwprintw( mWindow, 9, 3, "Player 2" );
  wattroff( mWindow, A_BOLD );
  mvwprintw( mWindow, 10, 2, "----------------" );
  mvwprintw( mWindow, 11, 3, "Score: %d       ", p2score );
//  mvwprintw( mWindow, 11, 3, "Light: %d     ", p2light );
//  mvwprintw( mWindow, 12, 3, "Water: %d     ", p2water );
  
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
