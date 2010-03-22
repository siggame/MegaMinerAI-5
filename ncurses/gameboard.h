#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "../visualizer/structures.h"
#include "window.h"
#include "legend.h"

#include <list>

class Gameboard : public Window
{
  private:
    Piece pieces[2][4];
    Piece background;
    void setupPieces();
    
    char **board;
    void drawBoard();
    
    int curX, curY;
    int boardX, boardY;
       
  public:
    Gameboard( int x, int y, int width, int height ) ;
    void newState( GameState state );
    
    void setCursor( int x, int y );
  
};

#endif
