import functools
import mappableObject
MappableObject = mappableObject.MappableObject

# A decorator maker to ensure that this function can only be called
#   successfully if this plant is owned by the current player
def checkOwnership(actionText):
    def dec(f):
        @functools.wraps(f)
        def wrapper(self, *expression):
            if (self.owner != self.game.turn):
                result = str(self.id) + " can not " + actionText + ". "
                result += "Not your plant."
                return result
            else:
                return f(self, *expression)
        return wrapper
    return dec

class Plant(MappableObject):
    """
    Any object that is owned by a player and can move inherits from this class.
    This class handles functions related to attacking and moving.
    """
    # Configured Values (see config/defaults.cfg)
    # leafCostWater
    # leafCostLight
    # rootCostWater
    # rootCostLight
    # flowerCostWater
    # flowerCostLight
    # barkCostWater
    # barkCostLight
    # leavesToSteal
    # rootsToSteal

    def __init__(self, game, x, y, owner):
        MappableObject.__init__(self, game, x, y)
        self.owner = owner
        self.water = 0
        self.light = 0
        self.roots = 1
        self.leaves = 1
        self.bark = 0
        self.flowers = 0

    def toList(self):
        list = MappableObject.toList(self)
        ownerIndex = self.game.players.index(self.owner)
        list.extend([ownerIndex, self.leaves, self.roots, self.flowers, self.bark, self.water, self.light])
        return list

    @checkOwnership("grow a leaf")
    def buildLeaf(self):
        if ( self.light >= self.leaves and \
        self.water >= self.leaves**2 ):
            self.light -= self.leaves
            self.water -= self.leaves**2
            self.leaves += 1
            self.game.animations.append(['grow-leaf', self.id])
        else:
            return str(self.id)+" can not grow a leaf. Not enough resources."
        return True

    @checkOwnership("grow a root")
    def buildRoot(self):
        if ( self.light >= self.roots**2 and \
        self.water >= self.roots ):
            self.light -= self.roots**2
            self.water -= self.roots
            self.roots += 1
            self.game.animations.append(['grow-root', self.id])
        else:
            return str(self.id)+" can not grow a root. Not enough resources."
        return True

    @checkOwnership("grow bark")
    def buildBark(self):
        if ( self.light >= Plant.barkCostLight and \
        self.water >= Plant.barkCostWater ):
            self.bark += 1
            self.light -= Plant.barkCostLight
            self.water -= Plant.barkCostWater
            self.game.animations.append(['grow-bark', self.id])
        else:
            return str(self.id)+" can not grow bark. Not enough resources."
        return True

    @checkOwnership("grow a flower")
    def buildFlower(self):
        if ( self.light >= Plant.flowerCostLight and \
        self.water >= Plant.flowerCostWater ):
            self.flowers += 1
            self.light -= Plant.flowerCostLight
            self.water -= Plant.flowerCostWater
            self.game.animations.append(['grow-flower', self.id])
        else:
            return str(self.id)+" can not grow flowers. Not enough resources."
        return True

    @checkOwnership("talk")
    def talk(self, message):
        self.game.animations.append(['talk', self.id, message])
        return True

    def nextTurn(self):
        MappableObject.nextTurn(self)
        if (self.owner == self.game.turn):
            lightProduced = self.leaves
            waterProduced = self.roots
            adjacent = [[0,1],[1,0],[-1,0],[0,-1]]
            for xOff, yOff in adjacent:
                try:
                    other = self.game.area[(self.x+xOff,self.y+yOff)][0]
                    if other.owner != self.owner:
                        lightProduced -= other.leaves / Plant.leavesToSteal
                        waterProduced -= other.roots / Plant.rootsToSteal
                except IndexError:
                    #target area is not occupied or off the map.
                    pass
            self.light += lightProduced
            self.water += waterProduced
            self.owner.score += lightProduced + waterProduced
            for xOff, yOff in adjacent:
                try:
                    targetSquare = self.game.area[(self.x+xOff,self.y+yOff)]
                    if (targetSquare == [] and self.flowers > 0):
                        seed = Plant(self.game, self.x + xOff, self.y + yOff, \
                                    self.owner)
                        seed.water = self.flowers
                        seed.light = self.flowers
                        self.game.addObject(seed)
                except IndexError:
                    #target area is off the map
                    pass

