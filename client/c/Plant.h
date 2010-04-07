// -*-c++-*-

#ifndef PLANT_H
#define PLANT_H

#include <iostream>
#include "structures.h"

///A pretty plant.
class Plant {
  public:
  _Plant* ptr;
  Plant(_Plant* ptr = NULL);

  // Accessors
  int objectID();
  int x();
  int y();
  int ownerID();
  int root();
  int leaf();
  int flower();
  int health();
  int rootLevel();
  int leafLevel();
  int flowerLevel();
  int rootLevelUp();
  int leafLevelUp();
  int flowerLevelUp();
  int canAct();

  // Actions
  bool growLeaf();
  bool growRoot();
  bool growFlower(int rootUp, int leafUp, int flowerUp);
  bool spread(int x, int y);
  bool spawn(int x, int y);
  bool talk(const char* message);

  friend std::ostream& operator<<(std::ostream& stream, Plant ob);
};

#endif

