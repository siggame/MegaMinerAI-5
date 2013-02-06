#include "getters.h"

int plantGetObjectID(_Plant* ptr)
{
  return ptr->objectID;
}
int plantGetX(_Plant* ptr)
{
  return ptr->x;
}
int plantGetY(_Plant* ptr)
{
  return ptr->y;
}
int plantGetOwnerID(_Plant* ptr)
{
  return ptr->ownerID;
}
int plantGetRoot(_Plant* ptr)
{
  return ptr->root;
}
int plantGetLeaf(_Plant* ptr)
{
  return ptr->leaf;
}
int plantGetFlower(_Plant* ptr)
{
  return ptr->flower;
}
int plantGetHealth(_Plant* ptr)
{
  return ptr->health;
}
int plantGetRootLevel(_Plant* ptr)
{
  return ptr->rootLevel;
}
int plantGetLeafLevel(_Plant* ptr)
{
  return ptr->leafLevel;
}
int plantGetFlowerLevel(_Plant* ptr)
{
  return ptr->flowerLevel;
}
int plantGetRootLevelUp(_Plant* ptr)
{
  return ptr->rootLevelUp;
}
int plantGetLeafLevelUp(_Plant* ptr)
{
  return ptr->leafLevelUp;
}
int plantGetFlowerLevelUp(_Plant* ptr)
{
  return ptr->flowerLevelUp;
}
int plantGetCanAct(_Plant* ptr)
{
  return ptr->canAct;
}

