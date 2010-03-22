// -*-c++-*-

#include "structures.h"

#include <iostream>


std::ostream& operator<<(std::ostream& stream, Plant ob)
{
  stream << "objectID: " << ob.objectID  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "ownerID: " << ob.ownerID  <<'\n';
  stream << "root: " << ob.root  <<'\n';
  stream << "leaf: " << ob.leaf  <<'\n';
  stream << "flower: " << ob.flower  <<'\n';
  stream << "health: " << ob.health  <<'\n';
  stream << "rootLevel: " << ob.rootLevel  <<'\n';
  stream << "leafLevel: " << ob.leafLevel  <<'\n';
  stream << "flowerLevel: " << ob.flowerLevel  <<'\n';
  stream << "rootLevelUp: " << ob.rootLevelUp  <<'\n';
  stream << "leafLevelUp: " << ob.leafLevelUp  <<'\n';
  stream << "flowerLevelUp: " << ob.flowerLevelUp  <<'\n';
  stream << "canAct: " << ob.canAct  <<'\n';
  return stream;
}



std::ostream& operator<<(std::ostream& stream, Add ob)
{
  stream << "Add" << "\n";
  stream << "plantID: " << ob.plantID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, GrowFlower ob)
{
  stream << "GrowFlower" << "\n";
  stream << "plantID: " << ob.plantID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, GrowLeaf ob)
{
  stream << "GrowLeaf" << "\n";
  stream << "plantID: " << ob.plantID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, GrowRoot ob)
{
  stream << "GrowRoot" << "\n";
  stream << "plantID: " << ob.plantID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Remove ob)
{
  stream << "Remove" << "\n";
  stream << "plantID: " << ob.plantID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, spawn ob)
{
  stream << "spawn" << "\n";
  stream << "parentID: " << ob.parentID  <<'\n';
  stream << "childID: " << ob.childID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Spread ob)
{
  stream << "Spread" << "\n";
  stream << "parentID: " << ob.parentID  <<'\n';
  stream << "childID: " << ob.childID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Talk ob)
{
  stream << "Talk" << "\n";
  stream << "plantID: " << ob.plantID  <<'\n';
  stream << "message: " << ob.message  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, GameState ob)
{
  stream << "boardX: " << ob.boardX  <<'\n';
  stream << "boardY: " << ob.boardY  <<'\n';
  stream << "gameNumber: " << ob.gameNumber  <<'\n';
  stream << "player0Light: " << ob.player0Light  <<'\n';
  stream << "player0Score: " << ob.player0Score  <<'\n';
  stream << "player1Light: " << ob.player1Light  <<'\n';
  stream << "player1Score: " << ob.player1Score  <<'\n';
  stream << "playerID: " << ob.playerID  <<'\n';
  stream << "turnNumber: " << ob.turnNumber  <<'\n';
  
  stream << "\n\nPlants:\n";
  for(std::vector<Plant>::iterator i = ob.plants.begin(); i != ob.plants.end(); i++)
    stream << *i << '\n';
  stream << "\nAnimation\n";
  for(std::vector<Animation*>::iterator i = ob.animations.begin(); i != ob.animations.end(); i++)
  {
    if((**i).type == ADD)
      stream << *((Add*)*i) << "\n";
    if((**i).type == GROWFLOWER)
      stream << *((GrowFlower*)*i) << "\n";
    if((**i).type == GROWLEAF)
      stream << *((GrowLeaf*)*i) << "\n";
    if((**i).type == GROWROOT)
      stream << *((GrowRoot*)*i) << "\n";
    if((**i).type == REMOVE)
      stream << *((Remove*)*i) << "\n";
    if((**i).type == SPAWN)
      stream << *((spawn*)*i) << "\n";
    if((**i).type == SPREAD)
      stream << *((Spread*)*i) << "\n";
    if((**i).type == TALK)
      stream << *((Talk*)*i) << "\n";
  }
}

Game::Game()
{
  winner = -1;
}