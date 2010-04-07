//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that

#include "BaseAI.h"
#include "game.h"

int BaseAI::boardX()
{
  return getBoardX();
}
int BaseAI::boardY()
{
  return getBoardY();
}
int BaseAI::gameNumber()
{
  return getGameNumber();
}
int BaseAI::player0Light()
{
  return getPlayer0Light();
}
int BaseAI::player0Score()
{
  return getPlayer0Score();
}
int BaseAI::player1Light()
{
  return getPlayer1Light();
}
int BaseAI::player1Score()
{
  return getPlayer1Score();
}
int BaseAI::playerID()
{
  return getPlayerID();
}
int BaseAI::turnNumber()
{
  return getTurnNumber();
}

bool BaseAI::startTurn()
{
  static bool initialized = false;
  int count = 0;
  count = getPlantCount();
  plants.clear();
  plants.resize(count);
  for(int i = 0; i < count; i++)
  {
    plants[i] = Plant(getPlant(i));
  }
  if(!initialized)
  {
    initialized = true;
    init();
  }
  return run();
}
