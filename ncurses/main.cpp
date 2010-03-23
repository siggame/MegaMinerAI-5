#include "../visualizer/parser.h"
#include "../visualizer/structures.h"

#include <vector>
#include <iostream>
#include <limits>

#include "viscontrol.h"

#include "scoreboard.h"
#include "gameboard.h"
#include "renderer.h" 

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
  
  keypad( stdscr, TRUE );
  //refresh();
  
  // Initialize Colors Here:
  start_color();
  
  Viscontrol game1( 0, 0, &g );
  //Viscontrol game2( 0, 500, &g );
  
  game1.giveSelected();
 
  while( 1 ) 
  {
    if( !game1.run() )
      break;
    //if( !game2.run() )
//      break;
    
  }
  

 
/*
for( int i = 0; i < 64; i++ )
   for( int j = 0; j < 150; j++ )  
 mvaddch( i, j,6000+i*64+j ); 
*/

mvaddch( 1, 1, ACS_DIAMOND );
mvaddch( 2, 1, ACS_BULLET );
mvaddch( 3, 1, ACS_LANTERN );
mvaddch( 4, 1, ACS_PI );
getch();


  #if 0
  
  Renderer r;
  Gameboard gameboard( 0, 0, 23, 23 );
  Scoreboard score(24,0,23,23);
  
  r.addWindow(&gameboard);
  r.addWindow(&score);

  for(vector<GameState>::iterator i = g.states.begin(); i != g.states.end(); i++)
  {
    //cout << *i;
    //cout << "----------------------------------" << endl;
    
    score.updateScore( i->turnNumber, i->player0Light, i->player0Water, i->player1Light, i->player1Water );
    
    gameboard.newState( *i );
    refresh();
    r.updateWindows();
    getch();

    
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  
  #endif 
  return 0;
}
