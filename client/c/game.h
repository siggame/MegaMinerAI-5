//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef GAME_H
#define GAME_H

#include "network.h"
#include "structures.h"

#ifdef WIN32
#define DLLEXPORT extern "C" __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C"
{
#endif
  DLLEXPORT bool serverLogin(int socket, const char* username, const char* password);
  DLLEXPORT int createGame();
  DLLEXPORT int joinGame(int id);

  DLLEXPORT void sendTag(const char* message);
  DLLEXPORT void endTurn();
  DLLEXPORT void getStatus();


//commands

  DLLEXPORT bool plantGrowLeaf(_Plant* object);
  DLLEXPORT bool plantGrowRoot(_Plant* object);
  DLLEXPORT bool plantGrowFlower(_Plant* object, int rootUp, int leafUp, int flowerUp);
  DLLEXPORT bool plantSpread(_Plant* object, int x, int y);
  DLLEXPORT bool plantSpawn(_Plant* object, int x, int y);
  DLLEXPORT bool plantTalk(_Plant* object, const char* message);

//accessors

DLLEXPORT int myLight();
DLLEXPORT int myScore();


DLLEXPORT int getBoardX();
DLLEXPORT int getBoardY();
DLLEXPORT int getGameNumber();
DLLEXPORT int getPlayer0Light();
DLLEXPORT int getPlayer0Score();
DLLEXPORT int getPlayer1Light();
DLLEXPORT int getPlayer1Score();
DLLEXPORT int getPlayerID();
DLLEXPORT int getTurnNumber();

DLLEXPORT _Plant* getPlant(int num);
DLLEXPORT int getPlantCount();

DLLEXPORT int plantLeafCost(_Plant* ptr);
DLLEXPORT int plantRootCost(_Plant* ptr);
DLLEXPORT int plantFlowerCost(_Plant* ptr);

DLLEXPORT int plantSpreadCost(_Plant* ptr);
DLLEXPORT int plantSpawnCost(_Plant* ptr);



DLLEXPORT int networkLoop(int socket);
#ifdef __cplusplus
}
#endif

#endif
