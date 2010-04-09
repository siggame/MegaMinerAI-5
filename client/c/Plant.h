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
  /// Grow a leaf
  bool growLeaf();
  
  /// Grow a root
  bool growRoot();
  
  /// Grow a flower
  bool growFlower(int rootUp, int leafUp, int flowerUp);
  
  /// Spread
  bool spread(int x, int y);
  
  /// Spawn
  bool spawn(int x, int y);
  
  /// Talk
  bool talk(const char* message);
  
  
  // Utilities
  int leafCost();
  int rootCost();
  int flowerCost();

  int leafHealthCost();
  int rootHealthCost();
  int flowerHealthCost();


  int spreadCost();
  int spawnCost();
  
  /// Output to a stream
  friend std::ostream& operator<<(std::ostream& stream, Plant ob);
};

#endif

