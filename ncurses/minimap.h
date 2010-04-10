#ifndef MINIMAP_H
#define MINIMAP_H

#include "window.h"
#include "visettings.h"


class Minimap : public Window
{
  public:
    Minimap( int x, int y, int width, int height );
    void newState();
};

#endif
