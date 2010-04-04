#ifndef PLANTINFO_H
#define PLANTINFO_H

#include "../visualizer/structures.h"
#include "window.h"

class Plantinfo : public Window
{
  public:
    Plantinfo( int x, int y, int width, int height );
    
    void update();
    
};


#endif
