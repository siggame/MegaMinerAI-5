#ifndef VISETTINGS_H
#define VISETTINGS_H

#include "../visualizer/structures.h"

// CodeProject's Configuration Loader
#include "config.h"

#define ATTRIBUTE( vType, x ) \
  private: \
    vType x; \
  public: \
    vType get##x() \
    { \
      return x; \
    } \
    void set##x( vType XXTemp ) \
    { \
      x = XXTemp; \
    }

#define setAttr( x, y ) visettings::instance()->set##x( y )
#define getAttr( x ) visettings::instance()->get##x()

class visettings
{
  // SETUP GLOBAL ATTRIBUTES

  ATTRIBUTE( int, curX )
  ATTRIBUTE( int, curY )
  ATTRIBUTE( int, maxX )
  ATTRIBUTE( int, maxY )
  ATTRIBUTE( int, boardX )
  ATTRIBUTE( int, boardY )

  ATTRIBUTE( Game *, game )

  ATTRIBUTE( GameState *, state )
  ATTRIBUTE( Plant *, plant )
  ATTRIBUTE( int, turnNumber )
  ATTRIBUTE( int, player1Score )
  ATTRIBUTE( int, player2Score )
  ATTRIBUTE( int, player1Light )
  ATTRIBUTE( int, player2Light )
  ATTRIBUTE( bool, winAnimation )

  ATTRIBUTE( int, p1pieceF )
  ATTRIBUTE( int, p1pieceB )
  ATTRIBUTE( int, p1textF )
  ATTRIBUTE( int, p1textB )

  ATTRIBUTE( int, p2pieceF )
  ATTRIBUTE( int, p2pieceB )
  ATTRIBUTE( int, p2textF )
  ATTRIBUTE( int, p2textB )

  ATTRIBUTE( int, instrF )
  ATTRIBUTE( int, instrB )

  ATTRIBUTE( int, backgroundF )
  ATTRIBUTE( int, backgroundB )

  ATTRIBUTE( int, selectionF )
  ATTRIBUTE( int, selectionB )

  ATTRIBUTE( int, defaultF )
  ATTRIBUTE( int, defaultB )

  ATTRIBUTE( bool, alwaysWin );

  ATTRIBUTE( int, currentMode );
  ATTRIBUTE( int, frameNumber );
  ATTRIBUTE( int, speed );

  ATTRIBUTE( int, playSpeed );

  ATTRIBUTE( char *, player1Name );
  ATTRIBUTE( char *, player2Name );

  ATTRIBUTE( int, player1Plants );
  ATTRIBUTE( int, player2Plants );

  ATTRIBUTE( bool, autoEnd );
  ATTRIBUTE( bool, done );

  ATTRIBUTE( int, startPause );
  ATTRIBUTE( int, endPause );

  public:
    static visettings *inst;
    static visettings *instance()
    {
      if( !inst )
        inst = new visettings();
      return inst;
    }

    visettings();
    ~visettings();

    void loadFromFile();

};


#endif
