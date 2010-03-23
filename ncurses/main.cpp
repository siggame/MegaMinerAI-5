#include "../visualizer/parser.h"
#include "../visualizer/structures.h"

#include <vector>
#include <iostream>
#include <limits>

#include "viscontrol.h"

#include "scoreboard.h"
#include "gameboard.h"

using namespace std;

int main(int argc, char** argv)
{
 
  Game g;
  if( argc > 1 )
  {
    parseFile( g, argv[1] );
  }
  else
  {
    printf( "ERROR:\nINPUT GAMELOG NOT SPECIFIED. PLEASE READ README FOR MORE INFO!\n" );
    return 0;
  }
  
  initscr();  
  cbreak();
  noecho();  

  keypad(stdscr, TRUE);
  
  // Initialize Colors Here:
  start_color();
  
  Viscontrol *game1 = new Viscontrol( 0, 0, &g );
  
  game1->giveSelected();
 
  while( 1 ) 
  {
    if( !game1->run() )
      break;
  }
  
  delete game1;
  
  attrset( 0 );
  refresh();
  endwin();

  return 0;
}
