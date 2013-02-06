// -*-c++-*-

#include "wrappers.h"
#include "game.h"

Plant::Plant(_Plant* ptr) : ptr(ptr)
{

}

int Plant::objectID()
{
  return ptr->objectID;
}

int Plant::x()
{
  return ptr->x;
}

int Plant::y()
{
  return ptr->y;
}

int Plant::ownerID()
{
  return ptr->ownerID;
}

int Plant::root()
{
  return ptr->root;
}

int Plant::leaf()
{
  return ptr->leaf;
}

int Plant::flower()
{
  return ptr->flower;
}

int Plant::health()
{
  return ptr->health;
}

int Plant::rootLevel()
{
  return ptr->rootLevel;
}

int Plant::leafLevel()
{
  return ptr->leafLevel;
}

int Plant::flowerLevel()
{
  return ptr->flowerLevel;
}

int Plant::rootLevelUp()
{
  return ptr->rootLevelUp;
}

int Plant::leafLevelUp()
{
  return ptr->leafLevelUp;
}

int Plant::flowerLevelUp()
{
  return ptr->flowerLevelUp;
}

int Plant::canAct()
{
  return ptr->canAct;
}


bool Plant::growLeaf()
{
  return plantGrowLeaf(ptr);
}

bool Plant::growRoot()
{
  return plantGrowRoot(ptr);
}

bool Plant::growFlower(int rootUp, int leafUp, int flowerUp)
{
  return plantGrowFlower(ptr, rootUp, leafUp, flowerUp);
}

bool Plant::spread(int x, int y)
{
  return plantSpread(ptr, x, y);
}

bool Plant::spawn(int x, int y)
{
  return plantSpawn(ptr, x, y);
}

bool Plant::talk(char* message)
{
  return plantTalk(ptr, message);
}


std::ostream& operator<<(std::ostream& stream,Plant ob)
{
  stream << "objectID: " << ob.ptr->objectID  <<'\n';
  stream << "x: " << ob.ptr->x  <<'\n';
  stream << "y: " << ob.ptr->y  <<'\n';
  stream << "ownerID: " << ob.ptr->ownerID  <<'\n';
  stream << "root: " << ob.ptr->root  <<'\n';
  stream << "leaf: " << ob.ptr->leaf  <<'\n';
  stream << "flower: " << ob.ptr->flower  <<'\n';
  stream << "health: " << ob.ptr->health  <<'\n';
  stream << "rootLevel: " << ob.ptr->rootLevel  <<'\n';
  stream << "leafLevel: " << ob.ptr->leafLevel  <<'\n';
  stream << "flowerLevel: " << ob.ptr->flowerLevel  <<'\n';
  stream << "rootLevelUp: " << ob.ptr->rootLevelUp  <<'\n';
  stream << "leafLevelUp: " << ob.ptr->leafLevelUp  <<'\n';
  stream << "flowerLevelUp: " << ob.ptr->flowerLevelUp  <<'\n';
  stream << "canAct: " << ob.ptr->canAct  <<'\n';
  return stream;
}

