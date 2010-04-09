# -*- python -*-

from library import library

from ExistentialError import ExistentialError

class GameObject(object):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration


class Plant(GameObject):
  """A pretty plant.
  """
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.ID = library.plantGetObjectID(ptr)
  
  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.plants:
      if i.ID == self.ID:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  def growLeaf(self):
    self.validify()
    return library.plantGrowLeaf(self.ptr)

  def growRoot(self):
    self.validify()
    return library.plantGrowRoot(self.ptr)

  def growFlower(self, rootUp, leafUp, flowerUp):
    self.validify()
    return library.plantGrowFlower(self.ptr, rootUp, leafUp, flowerUp)

  def spread(self, x, y):
    self.validify()
    return library.plantSpread(self.ptr, x, y)

  def spawn(self, x, y):
    self.validify()
    return library.plantSpawn(self.ptr, x, y)

  def talk(self, message):
    self.validify()
    return library.plantTalk(self.ptr, message)

  def getObjectID(self):
    self.validify()
    return library.plantGetObjectID(self.ptr)

  def getX(self):
    self.validify()
    return library.plantGetX(self.ptr)

  def getY(self):
    self.validify()
    return library.plantGetY(self.ptr)

  def getOwnerID(self):
    self.validify()
    return library.plantGetOwnerID(self.ptr)

  def getRoot(self):
    self.validify()
    return library.plantGetRoot(self.ptr)

  def getLeaf(self):
    self.validify()
    return library.plantGetLeaf(self.ptr)

  def getFlower(self):
    self.validify()
    return library.plantGetFlower(self.ptr)

  def getHealth(self):
    self.validify()
    return library.plantGetHealth(self.ptr)

  def getRootLevel(self):
    self.validify()
    return library.plantGetRootLevel(self.ptr)

  def getLeafLevel(self):
    self.validify()
    return library.plantGetLeafLevel(self.ptr)

  def getFlowerLevel(self):
    self.validify()
    return library.plantGetFlowerLevel(self.ptr)

  def getRootLevelUp(self):
    self.validify()
    return library.plantGetRootLevelUp(self.ptr)

  def getLeafLevelUp(self):
    self.validify()
    return library.plantGetLeafLevelUp(self.ptr)

  def getFlowerLevelUp(self):
    self.validify()
    return library.plantGetFlowerLevelUp(self.ptr)

  def getCanAct(self):
    self.validify()
    return library.plantGetCanAct(self.ptr)

  def getRootCost(self):
    self.validify()
    return library.plantRootCost(self.ptr)

  def getLeafCost(self):
    self.validify()
    return library.plantLeafCost(self.ptr)

  def getFlowerCost(self):
    self.validify()
    return library.plantFlowerCost(self.ptr)

  def getRootHealthCost(self):
    self.validify()
    return library.plantRootHealthCost(self.ptr)

  def getLeafHealthCost(self):
    self.validify()
    return library.plantLeafHealthCost(self.ptr)

  def getFlowerHealthCost(self):
    self.validify()
    return library.plantFlowerHealthCost(self.ptr)

  def getSpreadCost(self):
    self.validify()
    return library.plantSpreadCost(self.ptr)

  def getSpawnCost(self):
    self.validify()
    return library.plantSpawnCost(self.ptr)

