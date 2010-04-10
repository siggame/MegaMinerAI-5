//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef BASEAI_H
#define BASEAI_H

#include <vector>
#include <ctime>
#include "game.h"

#include "Plant.h"

/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of boiler-plate code out of the way
///The provided AI class does just that.
class BaseAI
{
protected:
  std::vector<Plant> plants;
public:
  ///The number of rows on the grid
  int boardX();
  ///The number of columns on the grid
  int boardY();
  ///The identifier for this game. Matches the gamelog
  int gameNumber();
  ///Player 0's light
  int player0Light();
  ///Player 0's score
  int player0Score();
  ///Player 1's light
  int player1Light();
  ///Player 1's score
  int player1Score();
  ///Player Number; either 0 or 1
  int playerID();
  ///The current turn number. The first turn number is 0
  int turnNumber();
  
  ///
  ///Make this your username, which should be provided.
  virtual const char* username() = 0;
  ///
  ///Make this your password, which should be provided.
  virtual const char* password() = 0;
  ///
  ///This function is run once, before your first turn.
  virtual void init() = 0;
  ///
  ///This function is called each time it is your turn
  ///Return true to end your turn, return false to ask the server for updated information
  virtual bool run() = 0;

  bool startTurn();
};

#endif
