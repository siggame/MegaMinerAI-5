//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#pragma warning(disable : 4996)

#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

#include "game.h"
#include "network.h"
#include "structures.h"

#include "sexp/sexp.h"
#include "sexp/sexp_ops.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef WIN32
//Doh, namespace collision.
namespace Windows
{
    #include <Windows.h>
};
#else
#include <unistd.h>
#endif

using namespace std;

static int boardX = 0;
static int boardY = 0;
static int gameNumber = 0;
static int player0Light = 0;
static int player0Score = 0;
static int player1Light = 0;
static int player1Score = 0;
static int playerID = 0;
static int turnNumber = 0;


static _Plant* Plants = NULL;
static int PlantCount = 0;


static int socket;

//These two are needed to save the login credentials for repeated internal use
static char* last_username = NULL;
static char* last_password = NULL;
static string gameName;


DLLEXPORT bool serverLogin(int s, const char* username, const char* password)
{
  socket = s;
  
  if(!last_username)
    last_username = strdup(username);
  if(!last_password)
    last_password = strdup(password);

  string expr = "(login \"";
  expr += username;
  expr += "\" \"";
  expr += password;
  expr +="\")";

  send_string(socket, expr.c_str());

  sexp_t* expression;

  expression = extract_sexpr(rec_string(socket));
  expression = expression->list;
  if(expression->val == NULL || strcmp(expression->val, "login-accepted") != 0)
  {
    cerr << "Unable to login to server" << endl;
    return false;
  }
  return true;
}

DLLEXPORT int createGame()
{
  sexp_t* expression;

  send_string(socket, "(start-game)");
  expression = extract_sexpr(rec_string(socket));
  expression = expression->list->next;
  gameNumber = atoi(expression->val);
  
  std::cout << "Creating game " << gameNumber << endl;
  
  expression = expression->next->list->next->next;

  socket = open_server_connection(expression->val, "19001");
  serverLogin(socket, last_username, last_password);

  stringstream expr;
  expr << "(create-game " << gameNumber << ")";
  send_string(socket, expr.str().c_str());
  
  expr.str("");
  expr << "(join-game " << gameNumber << ")";
  send_string(socket, expr.str().c_str());
  
  stringstream name;
  name << gameNumber;
  gameName = name.str();
  playerID = 0;
  
  return socket;

}

DLLEXPORT int joinGame(int gameNum)
{
  sexp_t* expression;
  stringstream expr;
  
  gameNumber = gameNum;
  
  //get the server of the game
  expr << "(join-game " << gameNumber << ")";
  send_string(socket, expr.str().c_str());
  
  //redirect
  expression = extract_sexpr(rec_string(socket));
  expression = expression->list->next->next;
  
  if(!expression)
  {
    cerr << "Game " << gameNumber << " doesn't exist." << endl;
    return 0;
  }
  
  socket = open_server_connection(expression->val, "19001");
  serverLogin(socket, last_username, last_password);
  
  //join and start the game
  send_string(socket, expr.str().c_str());
  send_string(socket, "(game-start)");
  
  stringstream name;
  name << gameNumber;
  gameName = name.str();
  playerID = 1;
  
  return socket;
}

static int myLight()
{
  if(playerID == 0)
    return player0Light;
  return player1Light;
}

static int spendLight(int amount)
{
  if(playerID == 0)
    return player0Light -= amount;
  return player1Light -= amount;
}

DLLEXPORT void endTurn()
{
  send_string(socket, "(end-turn)");
}

DLLEXPORT void getStatus()
{
  send_string(socket, "(game-status)");
}


DLLEXPORT bool plantGrowLeaf(_Plant* object)
{
  stringstream expr;
  if(!(object->canAct) || myLight() < plantLeafCost(object))
    return false;
  expr << "(game-grow-leaf " << object->objectID
       << ")";
  send_string(socket, expr.str().c_str());
  object->canAct = false;
  spendLight(plantLeafCost(object));
  return true;
}

DLLEXPORT bool plantGrowRoot(_Plant* object)
{
  stringstream expr;
  if(!(object->canAct) || myLight() < plantRootCost(object))
    return false;
  expr << "(game-grow-root " << object->objectID
       << ")";
  send_string(socket, expr.str().c_str());
  object->canAct = false;
  spendLight(plantRootCost(object));
  return true;
}

DLLEXPORT bool plantGrowFlower(_Plant* object, int rootUp, int leafUp, int flowerUp)
{
  stringstream expr;
  if(!(object->canAct) || myLight() < plantFlowerCost(object))
    return false;
  expr << "(game-grow-flower " << object->objectID
       << " " << rootUp
       << " " << leafUp
       << " " << flowerUp
       << ")";
  send_string(socket, expr.str().c_str());
  object->canAct = false;
  spendLight(plantFlowerCost(object));
  return true;
}

DLLEXPORT bool plantSpread(_Plant* object, int x, int y)
{
  stringstream expr;
  if(!(object->canAct) || myLight() < plantSpreadCost(object))
    return false;
  expr << "(game-spread " << object->objectID
       << " " << x
       << " " << y
       << ")";
  send_string(socket, expr.str().c_str());
  object->canAct = false;
  spendLight(plantSpreadCost(object));
  for(int i = 0; i < PlantCount; i++)
    if(Plants[i].x == x && Plants[i].y == y)
      Plants[i].health -= object->rootLevel;
  return true;
}

DLLEXPORT bool plantSpawn(_Plant* object, int x, int y)
{
  stringstream expr;
  if(!(object->canAct) || myLight() < plantSpawnCost(object))
    return false;
  for(int i = 0; i < PlantCount; i++)
    if(Plants[i].x == x && Plants[i].y == y)
      return false;
  expr << "(game-spawn " << object->objectID
       << " " << x
       << " " << y
       << ")";
  send_string(socket, expr.str().c_str());
  object->canAct = false;
  spendLight(plantSpawnCost(object));
  return true;
}

DLLEXPORT bool plantTalk(_Plant* object, const char* message)
{
  stringstream expr;
  expr << "(game-talk " << object->objectID
      << " \"" << escape_string(message) << "\""
       << ")";
  send_string(socket, expr.str().c_str());
  return true;
}

//Utility functions for parsing data
void parsePlant(_Plant* object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object->objectID = atoi(sub->val);
  sub = sub->next;
  object->x = atoi(sub->val);
  sub = sub->next;
  object->y = atoi(sub->val);
  sub = sub->next;
  object->ownerID = atoi(sub->val);
  sub = sub->next;
  object->root = atoi(sub->val);
  sub = sub->next;
  object->leaf = atoi(sub->val);
  sub = sub->next;
  object->flower = atoi(sub->val);
  sub = sub->next;
  object->health = atoi(sub->val);
  sub = sub->next;
  object->rootLevel = atoi(sub->val);
  sub = sub->next;
  object->leafLevel = atoi(sub->val);
  sub = sub->next;
  object->flowerLevel = atoi(sub->val);
  sub = sub->next;
  object->rootLevelUp = atoi(sub->val);
  sub = sub->next;
  object->leafLevelUp = atoi(sub->val);
  sub = sub->next;
  object->flowerLevelUp = atoi(sub->val);
  sub = sub->next;
  object->canAct = atoi(sub->val);
  sub = sub->next;
  
}

DLLEXPORT int networkLoop(int socket)
{
  while(true)
  {
    sexp_t* expression, *sub, *subsub;
    expression = extract_sexpr(rec_string(socket));
    expression = expression->list;
    if(expression->val != NULL && strcmp(expression->val, "game-winner") == 0)
    {
      expression = expression->next;
      int winnerID = atoi(expression->val);
      if(winnerID == playerID)
      {
        cout << "You win!" << endl;
      }
      else
      {
        cout << "You lose. :(" << endl;
      }
      stringstream expr;
      expr << "(request-log " << gameName << ")";
      send_string(socket, expr.str().c_str());
      return 0;
    }
    else if(expression->val != NULL && strcmp(expression->val, "log") == 0)
    {
      ofstream out;
      char filename[100];
      expression = expression->next;
      strcpy(filename, expression->val);
      strcat(filename, ".gamelog");
      expression = expression->next;
      out.open(filename);
      if (out.good())
        out.write(expression->val, strlen(expression->val));
      else
        cerr << "Error : Could not create log." << endl;
      out.close();
      return 0;
    }
    else if(expression->val != NULL && strcmp(expression->val, "game-accepted")==0)
    {
      char gameID[30];

      expression = expression->next;
      strcpy(gameID, expression->val);
      cout << "Created game " << gameID << endl;
    }
    else if(expression->val != NULL && strstr(expression->val, "denied"))
    {
      cout << expression->val << endl;
      cout << expression->next->val << endl;
    }
    else if(expression->val != NULL && strcmp(expression->val, "ident") == 0)
    {
      expression = expression->next->next->next;
      playerID = atoi(expression->val);
    }
    else if(expression->val != NULL && strcmp(expression->val, "status") == 0)
    {
      while(expression->next != NULL)
      {
        expression = expression->next;
        sub = expression->list;
        if(string(sub->val) == "game")
        {
          sub = sub->next;
          turnNumber = atoi(sub->val);
          sub = sub->next;
          
          player0Score = atoi(sub->val);
          sub = sub->next;
          
          player1Score = atoi(sub->val);
          sub = sub->next;

          player0Light = atoi(sub->val);
          sub = sub->next;

          player1Light = atoi(sub->val);
          sub = sub->next;
          
          boardX = atoi(sub->val);
          sub = sub->next;
          
          boardY = atoi(sub->val);
        }
        else if(string(sub->val) == "Plant")
        {
          for(int i = 0; i < PlantCount; i++)
          {
          }
          delete[] Plants;
          PlantCount =  sexp_list_length(expression)-1; //-1 for the header
          Plants = new _Plant[PlantCount];
          for(int i = 0; i < PlantCount; i++)
          {
            sub = sub->next;
            parsePlant(Plants+i, sub);
          }
        }
      }
      if(turnNumber % 2 == playerID) return 1;
    }
  }
}

DLLEXPORT _Plant* getPlant(int num)
{
  return Plants + num;
}
DLLEXPORT int getPlantCount()
{
  return PlantCount;
}


DLLEXPORT int getBoardX()
{
  return boardX;
}
DLLEXPORT int getBoardY()
{
  return boardY;
}
DLLEXPORT int getGameNumber()
{
  return gameNumber;
}
DLLEXPORT int getPlayer0Light()
{
  return player0Light;
}
DLLEXPORT int getPlayer0Score()
{
  return player0Score;
}
DLLEXPORT int getPlayer1Light()
{
  return player1Light;
}
DLLEXPORT int getPlayer1Score()
{
  return player1Score;
}
DLLEXPORT int getPlayerID()
{
  return playerID;
}
DLLEXPORT int getTurnNumber()
{
  return turnNumber;
}


DLLEXPORT int plantLeafCost(_Plant* ptr)
{
  return ptr->leafLevel * 2;
}
DLLEXPORT int plantRootCost(_Plant* ptr)
{
  return ptr->rootLevel * 1;
}
DLLEXPORT int plantFlowerCost(_Plant* ptr)
{
  return ptr->flowerLevel * 5;
}
DLLEXPORT int plantSpreadCost(_Plant* ptr)
{
  return (ptr->leafLevel + ptr->leafLevel + ptr->flowerLevel)  * 1;
}
DLLEXPORT int plantSpawnCost(_Plant* ptr)
{
  return (ptr->leafLevel + ptr->leafLevel + ptr->flowerLevel) * 2;
}