#ifndef VISCONTROL_H
#define VISCONTROL_H

#include "window.h"
#include "scoreboard.h"
#include "gameboard.h"
#include "plantinfo.h"
#include "minimap.h"
#include "../visualizer/structures.h"

#define MODE_PLAY 0
#define MODE_PAUSE 1 
#define MODE_REWIND 2



//#define Y_OFFSET 40 

class Viscontrol : public Window
{
  private:   
    #if 0
    int currentMode; // Play/Pause
    int frameNumber;
    int speed;	// How fast should we Play/Rewind
    #endif
    
    Gameboard *gameboard;
    Scoreboard *score;
    Plantinfo *plantInfo;
    Minimap *minimap;
    
    Game *game;
       
    bool selected;
    
  public:
    Viscontrol( int x, int y, Game *g );
    ~Viscontrol();
    
    int run();
    
    void updateMode( int mode );    
    void update(); 
    void nextFrame();
    void prevFrame();
    
    void giveSelected();
    void takeSelected();
    
  
  
};

#endif
