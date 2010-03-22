#include "viscontrol.h"

Viscontrol::Viscontrol( int x, int y, Game *g ) 
  : Window( x, y, 200, 1 )
{

  currentMode = MODE_PAUSE; 
  speed = -1; // ms
  frameNumber = 0;
  playSpeed = 40;

  maxX = g->states[0].boardX-1;
  maxY = g->states[0].boardY-1;

  moveWindow( x, maxY*2+4 ); 

  gameboard = new Gameboard( x, y, maxX*2+4, maxY*2+4 );
  score = new Scoreboard( x+maxX*2+5, y, 23, maxY*2+4 );
  plantInfo = new Plantinfo( x+maxX*2+5+23, y, 23, maxY*2+4 );
  game = g;

//  moveWindow( x, maxY*4+4); 
 
  curX = curY = 0;
  
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
  update();
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
    case KEY_LEFT:
      --curX;
      break;
    case KEY_RIGHT:
      ++curX;
      break;
    case KEY_UP:
      --curY;
      break;
    case KEY_DOWN:
      ++curY;
      break;
    }
    
    if( curX < 0 )
      curX = 0;
    if( curX > (gameboard->getWidth()-3)/2 )
      curX = (gameboard->getWidth()-3)/2;
    if( curY < 0 )
      curY = 0;
    if( curY > (gameboard->getHeight()-3)/2 )
      curY = (gameboard->getHeight()-3)/2;

    bool plant = false;

    if( currentMode == MODE_PLAY )    
      nextFrame();
    else if( currentMode == MODE_REWIND )
      prevFrame();
    
    for( std::vector<Plant>::iterator i = game->states[frameNumber].plants.begin(); i != game->states[frameNumber].plants.end(); i++ )
    {
      if( i->x == curX && i->y == curY )
      {
	
	plantInfo->givePlant( &(*i) );
	plant = true;
      }
      
    }
    
    if( !plant )
      plantInfo->givePlant( 0 );
    
    gameboard->setCursor( curX, curY );
    
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
  
  gameboard->newState( game->states[frameNumber] );
 // score->updateScore( game->states[frameNumber].turnNumber, game->states[frameNumber].player0Light, game->states[frameNumber].player0Water, game->states[frameNumber].player1Light, game->states[frameNumber].player1Water );
  score->updateScore( game->states[frameNumber].turnNumber, game->states[frameNumber].player0Score, game->states[frameNumber].player1Score );
  plantInfo->update();
  
  gameboard->update();
  score->update();
  
  const int offset = 50; 
  
  float percent = (float)(frameNumber+1)/game->states.size();
  
  int blocks = (maxX*2+offset-10)*percent;
  
  for( int i = 1; i < blocks+1; i++ )
    mvwaddch( mWindow, 0, i, ACS_HLINE );
  for( int i = blocks+1; i < maxX*2+offset-9; i++ )
    mvwaddch( mWindow, 0, i, ' ' );
  
  mvwaddch( mWindow, 0, 0, ACS_LLCORNER );
  mvwaddch( mWindow, 0, maxX*2+offset-9, ACS_LRCORNER );
  
  if( currentMode == MODE_PAUSE )
    mvwprintw( mWindow, 0, maxX*2+offset-7, "PAUSED      " );
  else if( currentMode == MODE_PLAY )
    mvwprintw( mWindow, 0, maxX*2+offset-7, "PLAYING     " );
  else if( currentMode == MODE_REWIND )
    mvwprintw( mWindow, 0, maxX*2+offset-7, "REWINDING   " );
  
  
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
