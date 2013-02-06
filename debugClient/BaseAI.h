//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef BASEAI_H
#define BASEAI_H

#include <vector>
#include <ctime>
#include "game.h"
#include "wrappers.h"

/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of boiler-plate code out of the way
///The provided AI class does just that.
class BaseAI
{
protected:
  std::vector<Plant> plants;
public:
  int boardX();
  int boardY();
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
  int turnNumber();
  
  ///
  ///Make this your username, which should be provided.
  virtual const char* username() = 0;
  ///
  ///Make this your password, which should be provided.
  virtual const char* password() = 0;
  ///
  ///This is run on turn 1 before run
  virtual void init() = 0;
  
  virtual bool run() = 0;

  bool startTurn();
};

#endif
