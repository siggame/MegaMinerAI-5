#include "viscontrol.h"
#include "visettings.h"

Viscontrol::Viscontrol( int x, int y, Game *g ) 
  : Window( x, y, 200, 1 )
{

  currentMode = MODE_PAUSE; 
  speed = -1; // ms
  frameNumber = 0;
  playSpeed = 40;

  setAttr( maxX, g->states[0].boardX );
  setAttr( maxY, g->states[0].boardY );

  moveWindow( x, getAttr( maxY )*2+4 ); 

  gameboard = new Gameboard( x, y, getAttr(maxX)*2+4, getAttr(maxY)*2+4 );
  score = new Scoreboard( x+getAttr(maxX)*2+5, y, 31, getAttr(maxY)*2+4 );
  plantInfo = new Plantinfo( x+getAttr(maxX)*2+5+31, y, 32, getAttr(maxY)+1 );
  minimap = new Minimap( 
    x+getAttr(maxX)*2+5+31 + 30/2 - getAttr(maxX)/2,  // XPOS
    getAttr(maxY)+1, // YPOS
    getAttr(maxX)+3,  // WIDTH
    getAttr(maxY)+3 );// HEIGHT );
  game = g;
 
  setAttr( curX, 0 );
  setAttr( curY, 0 );
  
  selected = false;
  
  werase( mWindow );
  
}

Viscontrol::~Viscontrol()
{
  // Clean up, Clean up, Everybody, Everywhere
}
  
void Viscontrol::updateMode( int mode )
{

  currentMode = mode;
  if( (mode == MODE_PLAY) || (mode == MODE_REWIND) )
    speed = playSpeed;
  else if( mode == MODE_PAUSE )
    speed = -1;
  
  
}

int Viscontrol::run()
{
  static bool firstRun = true;
  if( firstRun )
  {
    update();
    firstRun = false;
  }
  
  if( selected )
  {
    timeout( speed );
    int c;
    c = getch();
    
    switch( c )
    {     
    case 'q':
      return 0;
      break;
    case ' ':
    case 'p':
      if( currentMode == MODE_PAUSE )
        updateMode( MODE_PLAY );
      else // Play/Rewind
        updateMode( MODE_PAUSE );
      break;
    case 'r':
      updateMode( MODE_REWIND );
      break;
    case '.':
      updateMode( MODE_PAUSE );
      nextFrame();
      break;
    case '=':
      playSpeed -= 5;
      if( playSpeed < 0 )
        playSpeed = 1;
      updateMode( currentMode );
      timeout(playSpeed);
      break;
    case '-':
      playSpeed += 5;
      updateMode( currentMode );
      timeout(playSpeed);
      break;
    case ',':
      updateMode( MODE_PAUSE );
      prevFrame();
      break;
    case 's':
      frameNumber = 0;
      break;
    case 'e':
      frameNumber = game->states.size()-1;
      break;
    case KEY_LEFT:
      setAttr( curX, getAttr( curX ) - 1 );
      break;
    case KEY_RIGHT:
      setAttr( curX, getAttr( curX ) + 1 );
      break;
    case KEY_UP:
      setAttr( curY, getAttr( curY ) - 1 );
      break;
    case KEY_DOWN:
      setAttr( curY, getAttr( curY ) + 1 );
      break;
    }
    
    if( currentMode == MODE_PLAY )    
      nextFrame();
    else if( currentMode == MODE_REWIND )
      prevFrame();    
    
  } else 
  {

    if( currentMode == MODE_PLAY )    
      nextFrame();
    else if( currentMode == MODE_REWIND )
      prevFrame();
  }

  update();
  
  return 1;
}

void Viscontrol::update()
{
  
  refresh();
  
  setAttr( state, &game->states[frameNumber] );
  

  setAttr( turnNumber, game->states[frameNumber].turnNumber );
  setAttr( player1Score, game->states[frameNumber].player0Score );
  setAttr( player2Score, game->states[frameNumber].player1Score );
  setAttr( player1Light, game->states[frameNumber].player0Light );
  setAttr( player2Light, game->states[frameNumber].player1Light );
  
  score->update();
  minimap->newState();
  gameboard->newState();
  plantInfo->update();  
  

  
  
  const int offset = 50; 
  
  float percent = (float)(frameNumber+1)/game->states.size();
  
  int blocks = (getAttr(maxX)*2+offset-10)*percent;
  
  for( int i = 1; i < blocks+1; i++ )
    mvwaddch( mWindow, 0, i, ACS_HLINE );
  for( int i = blocks+1; i < getAttr(maxX)*2+offset-9; i++ )
    mvwaddch( mWindow, 0, i, ' ' );
  
  mvwaddch( mWindow, 0, 0, ACS_LLCORNER );
  mvwaddch( mWindow, 0, getAttr(maxX)*2+offset-9, ACS_LRCORNER );
  
  if( currentMode == MODE_PAUSE )
    mvwprintw( mWindow, 0, getAttr(maxX)*2+offset-7, "PAUSED      " );
  else if( currentMode == MODE_PLAY )
    mvwprintw( mWindow, 0, getAttr(maxX)*2+offset-7, "PLAYING     " );
  else if( currentMode == MODE_REWIND )
    mvwprintw( mWindow, 0, getAttr(maxX)*2+offset-7, "REWINDING   " );
  
  
  wrefresh( mWindow );
  refresh();
}

void Viscontrol::nextFrame()
{
  
  ++frameNumber;
  if( frameNumber > game->states.size()-1 )
    frameNumber = game->states.size()-1;
  
}

void Viscontrol::prevFrame()
{
  --frameNumber;
  if( frameNumber < 0 )
    frameNumber = 0;
}

void Viscontrol::giveSelected()
{
  selected = true; 
}
