#include "renderer.h"

Renderer::Renderer()
{
  initscr();  
  cbreak();
  noecho();
  //refresh();
  
  // Initialize Colors Here:
  start_color();
  
}

Renderer::~Renderer()
{
  endwin();
}

void Renderer::addWindow( Window *window )
{
  mWindows.push_back( window );
}

void Renderer::updateWindows()
{
   refresh();
 
  for( std::list<Window *>::iterator i = mWindows.begin(); i != mWindows.end(); i++ )
  {
    (*i)->update();
  }
  

  
}
