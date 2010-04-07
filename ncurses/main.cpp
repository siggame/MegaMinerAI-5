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
    if( !parseFile( g, argv[1] ) )
    {
      printf( "ERROR: Invalid Gamelog or Gamelog NOT FOUND!\nIf you need assistant please read README\n" );
      return 0;
    }
  }
  else
  {
    printf( "ERROR:\nINPUT GAMELOG NOT SPECIFIED. PLEASE READ README FOR MORE INFO!\n" );
    return 0;
  }
  
  visettings::instance()->loadFromFile();
  
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
