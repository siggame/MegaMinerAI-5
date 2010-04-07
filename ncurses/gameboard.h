#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "../visualizer/structures.h"
#include "window.h"
#include "legend.h"

#include <list>

class Gameboard : public Window
{
  private:
    int background;
    void setupPieces();       
  public:
    Gameboard( int x, int y, int width, int height ) ;
    void newState();
    void playWinAnim( int player );
  
};

#endif
