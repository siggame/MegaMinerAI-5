#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "window.h"

class Scoreboard : public Window
{
  private:
    int turn;
//    int p1light, p2light;
//    int p1water, p2water;
    int p1score, p2score;
    
  public:
    void update();
    void updateScore( int rTurn, int rP1score, int rP2score );
    Scoreboard( int x, int y, int width, int height );
  
  
};

#endif
