//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <vector>
#include <string>

const int ADD = 0;
const int GROWFLOWER = 1;
const int GROWLEAF = 2;
const int GROWROOT = 3;
const int REMOVE = 4;
const int SPAWN = 5;
const int SPREAD = 6;
const int TALK = 7;

struct Plant
{
  int objectID;
  int x;
  int y;
  int ownerID;
  int root;
  int leaf;
  int flower;
  int health;
  int rootLevel;
  int leafLevel;
  int flowerLevel;
  int rootLevelUp;
  int leafLevelUp;
  int flowerLevelUp;
  int canAct;
  
  friend std::ostream& operator<<(std::ostream& stream, Plant obj);
};


struct Animation
{
  int type;
};

struct Add : public Animation
{
  int plantID;
  
  friend std::ostream& operator<<(std::ostream& stream, Add obj);
};

struct GrowFlower : public Animation
{
  int plantID;
  
  friend std::ostream& operator<<(std::ostream& stream, GrowFlower obj);
};

struct GrowLeaf : public Animation
{
  int plantID;
  
  friend std::ostream& operator<<(std::ostream& stream, GrowLeaf obj);
};

struct GrowRoot : public Animation
{
  int plantID;
  
  friend std::ostream& operator<<(std::ostream& stream, GrowRoot obj);
};

struct Remove : public Animation
{
  int plantID;
  
  friend std::ostream& operator<<(std::ostream& stream, Remove obj);
};

struct spawn : public Animation
{
  int parentID;
  int childID;
  
  friend std::ostream& operator<<(std::ostream& stream, spawn obj);
};

struct Spread : public Animation
{
  int parentID;
  int childID;
  
  friend std::ostream& operator<<(std::ostream& stream, Spread obj);
};

struct Talk : public Animation
{
  int plantID;
  char* message;
  
  friend std::ostream& operator<<(std::ostream& stream, Talk obj);
};


struct GameState
{
  std::vector<Plant> plants;
  
  int boardX;
  int boardY;
  int gameNumber;
  int player0Light;
  int player0Score;
  int player1Light;
  int player1Score;
  int playerID;
  int turnNumber;
  
  std::vector<Animation*> animations;
  friend std::ostream& operator<<(std::ostream& stream, GameState obj);
};

struct Game
{
  std::vector<GameState> states;
  std::string players[2];
  int winner;

  Game();
};

#endif
