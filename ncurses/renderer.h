#ifndef RENDERER_H
#define RENDERER_H

#include "window.h"
#include <list>

class Renderer
{
  private:
    std::list<Window *> mWindows;
    
  public:
    Renderer();
    ~Renderer();
    void addWindow( Window *window );
    void updateWindows();
};

#endif