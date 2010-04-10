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
  ///This plant's unique identifier, which will never change
  int objectID();
  ///The x coordinate of this plant on the grid
  int x();
  ///The y coordinate of this plant on the grid
  int y();
  ///The owner of this plant, either 0 or 1
  int ownerID();
  ///1 if this plant has a root, 0 otherwise

  ///Having a root allows your plant to use spread.
  ///When the root is first created, you gain health.
  int root();
  ///1 if this plant has a leaf, 0 otherwise

  ///Having a leaf allows your plant to collect light.
  int leaf();
  ///1 if this plant has a flower, 0 otherwise

  ///Having a flower allows your plant to use spawn.
  int flower();
  ///The amount of health remaining for this plant

  ///If your plant has 0 or less health at the end of YOUR turn,
  ///it dies.
  int health();
  ///The root level of this plant

  ///Higher root levels increase the amount of health gained
  ///when using growLeaf and the amount of damage delt when using
  ///spead on an occupied square.
  ///Has no impact if this plant does not have a root.
  int rootLevel();
  ///The leaf level of this plant.

  ///Higher leaf levels increase the amount of light generated per turn.
  ///Has no effect if this plant does not have a leaf.
  int leafLevel();
  ///The flower level of this plant.

  ///Higher flower levels allow your plant to pass on more upgrades to its 
  ///offspring created by using spawn.
  ///Has no effect if this plant does not have a flower.
  int flowerLevel();
  ///The root tech bonus provided to offspring when using spawn

  ///This is set when growing a new flower.  If this plant does not have
  ///a flower, this is 0.
  int rootLevelUp();
  ///The leaf tech bonus provided to offspring when using spawn

  ///This is set when growing a new flower.  If this plant does not have
  ///a flower, this is 0.
  int leafLevelUp();
  ///The flower tech bonus provided to offspring when using spawn

  ///This is set when growing a new flower.  If the plant does not have
  ///a flower, this is 0.
  int flowerLevelUp();
  ///1 if this plant has done nothing this turn, 0 otherwise.

  ///Plants can only perform one action per turn.
  int canAct();

  // Actions
  /// Grow a leaf

  /// Requires an action and sufficient light.
  /// You may only grow one leaf per plant.
  /// Creates a leaf on this plant.
  /// Leaves generate light at the end of your turn.
  /// Having a leaf increases the amount of health lost each turn.
  /// The light cost of this action increases with leaf level.
  /// The amount of light generated increases with leaf level.
  bool growLeaf();
  
  /// Grow a root

  /// Requires an action and sufficient light.
  /// You may only grow one root per plant.
  /// Creates a root on the current plant.
  /// A root allows this plant to use spread.
  /// Increases the health of this plant based on root level.
  /// The light cost of this action increases with root level.
  bool growRoot();
  
  /// Grow a flower

  /// Requires an action and sufficient light.
  /// You may only grow one flower per plant.
  /// Creates a flower on the current plant.
  /// A flower allows this plant to use spawn.
  /// The sum of the three parameters must be equal to flower level.
  /// The light cost of this action increases with flower level.
  bool growFlower(int rootUp, int leafUp, int flowerUp);
  
  /// Spread, creating a new plant

  ///Requires an action, sufficient light, and a root.
  ///Creates a new plant at (x,y) with the same tech levels.
  ///The new plant does not start with any structures,
  ///can not perform actions this turn, and has full health.
  ///The light cost of this action increases with leaf, root, and flower levels
  bool spread(int x, int y);
  
  /// Spawn, creating a new (and better!) plant
  
  ///Requires an action, sufficient light, and a flower.
  ///Creates a new plant at (x,y) with the same tech levels plus the levels
  ///of flowerLevelUp, rootLevelUp, and leafLevelUp.
  ///The new plant does not start with any structures,
  ///can not perform actions this turn, and has full health.
  ///The light cost of this action increases with leaf, root, and flower
  ///levels, as well as leafLevelUp, rootLevelUp, and flowerLevelUp.
  bool spawn(int x, int y);
  
  /// Adds tags for this plant in the visualizer.

  /// Let the world know what this plant is thinking.  What are its hopes
  /// and dreams?  Where does it see itself in the next 5 turns?  When you
  /// select this plant in the ncurses visualizer, this text will be visible.
  bool talk(const char* message);
  
  
  // Utilities
  /// The base amount of light required to grow a leaf.

  /// This amount is multiplied by leaf level to determine the actual cost
  /// of growing a leaf.
  int leafCost();
  /// The base amount of light required to grow a root.

  /// This amount is multiplied by root level to determine the actual cost
  /// of growing a root.
  int rootCost();
  /// The base amount of light required to grow a flower.

  /// This amount is multiplied by flower level to determine the actual cost
  /// of growing a flower.
  int flowerCost();
  /// The amount of health lost each turn if you have a leaf.

  /// At the end of each of your turns, all plants that have a leaf will lose
  /// this much health.
  int leafHealthCost();
  /// The amount of health lost each turn if you have a root.

  /// At the end of each of your turns, all plants that have a root will lose
  /// this much health.
  int rootHealthCost();
  /// The amount of health lost each turn if you have a flower.

  /// At the end of each of your turns, all plants that have a flower will lose
  /// this much health.
  int flowerHealthCost();

  /// The base cost of performing a spread action.

  /// This amount is multiplied by the sum of this plant's levels to 
  /// determine the actual cost of spreading.
  int spreadCost();
  ///The base cost of performing a spawn action

  /// This amount is multiplied by the sum of this plant's levels and flower
  /// levels to determine the actual cost of spawning.
  int spawnCost();
  
  /// Output to a stream
  friend std::ostream& operator<<(std::ostream& stream, Plant ob);
};

#endif

