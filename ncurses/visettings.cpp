#include "visettings.h"

visettings *visettings::inst = NULL;

visettings::visettings()
{
  winAnimation = true;
}

visettings::~visettings()
{
  if( inst )
    delete inst;
  inst = 0;
}

void visettings::loadFromFile()
{
  Config configFile( "VISCONFIG" );

  setAttr( winAnimation, configFile.pBool( "winAnimation" ) );

  setAttr( p1pieceF, configFile.pInt( "P1PieceForeground" ) );
  setAttr( p1pieceB, configFile.pInt( "P1PieceBackground" ) );

  setAttr( p1textF, configFile.pInt( "P1TextForeground" ) );
  setAttr( p1textB, configFile.pInt( "P1TextBackground" ) );

  setAttr( p2pieceF, configFile.pInt( "P2PieceForeground" ) );
  setAttr( p2pieceB, configFile.pInt( "P2PieceBackground" ) );

  setAttr( p2textF, configFile.pInt( "P2TextForeground" ) );
  setAttr( p2textB, configFile.pInt( "P2TextBackground" ) );

  setAttr( instrF, configFile.pInt( "InstructionsForeground" ) );
  setAttr( instrB, configFile.pInt( "InstructionsBackground" ) );

  setAttr( backgroundF, configFile.pInt( "BackgroundForeground" ) );
  setAttr( backgroundB, configFile.pInt( "BackgroundBackground" ) );

  setAttr( selectionF, configFile.pInt( "SelectionForeground" ) );
  setAttr( selectionB, configFile.pInt( "SelectionBackground" ) );

  setAttr( defaultF, configFile.pInt( "DefaultForeground" ) );
  setAttr( defaultB, configFile.pInt( "DefaultBackground" ) );

  setAttr( alwaysWin, configFile.pBool( "AlwaysPlayWin" ) );

  setAttr( playSpeed, configFile.pInt( "DefaultSpeed" ) );

  setAttr( autoEnd, false );
  setAttr( done, false );

  setAttr( startPause, configFile.pInt( "STARTPAUSE" ) );
  setAttr( endPause, configFile.pInt( "ENDPAUSE" ) );
}
