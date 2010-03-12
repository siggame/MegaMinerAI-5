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
    # leafCost
    # rootCost
    # flowerCost

    def __init__(self, game, x, y, owner):
        MappableObject.__init__(self, game, x, y)
        self.root = False
        self.leaf = False
        self.flower = False
        self.health = Plant.initialHealth
        self.owner = owner
        self.techLevelRoot = 1
        self.techLevelLeaf = 1
        self.techLevelFlower = 1
        self.flowerRootUp
        self.flowerLeafUp
        self.flowerFlowerUp
        self.canAct = True

    def toList(self):
        list = MappableObject.toList(self)
        ownerIndex = self.game.players.index(self.owner)
        list.extend([ownerIndex ,self.root, self.leaf, self.flower, \
                         self.health, self.techLevelRoot, self.techLevelLeaf, \
                         self.techLevelFlower, self.flowerRootUp, \
                         self.flowerLeafUp, self.flowerFlowerUp, self.canAct])
        return list

    @checkOwnership("grow a leaf")
    def buildLeaf(self):
        if(self.leaf):
            return str(self.id) + "cannot grow a leaf. It already has a leaf."
        else:
            if self.owner.light >= Plant.leafCost:
                    self.leaf = True
                    self.owner.light -= Plant.leafCost
            else:
                return str(self.id) + "cannot grow leaf, not enough resources"
        return True
                
    @checkOwnership("grow a root")
    def buildRoot(self):
        if(self.root):
            return str(self.id) + " cannot grow roots. It already has roots."
        else:
            if( self.owner.light >= Plant.rootCost ): 
                self.root = True
                self.owner.light -= Plant.rootCost
            else:
                return str(self.id) + " cannot grow root, not enough resources"
        return True

    @checkOwnership("grow a flower")
    def buildFlower(self, rootUp, leafUp, flowerUp):
        if(self.flower):
            return str(self.id) + "cannot grow a flower. It already has a leaf."
        if rootUp < 0 or leafUp < 0 or flowerUp < 0:
            return str(self.id) + " cannot have negative 'up' values."
        if rootUp + leafUp + flowerUp > self.flowerLevel:
            return str(self.id) + " does not have enough resources to grow" + \
                " a flower with these features."
        else:
            if( self.owner.light >= flowerCost ):
                self.flower = True
                self.owner.light -= flowerCost
            else:
                return str(self.id) + "cannot grow flower, not enough resources"
        self.flowerRootUp = rootUp
        self.flowerLeafUp = leafUp
        self.flowerFlowerUp = flowerUp
        return True

    @checkOwnership("spread")
    def spread(self, x, y):
        if(not self.root):
            return str(self.id) + " does not have a root, cannot spread"
        if(((x == self.x+1) or (x == self.x-1)) and ((y == self.y+1) or (y == self.y-1))):
            if(self.owner.light >= Plant.rootCost):
                newPlant = Plant(self.game, x, y, self.owner)
                newPlant.root = True
                newPlant.techLevelRoot = self.techLevelRoot
                newPlant.techLevelLeaf = self.techLevelLeaf
                newPlant.techLevelFlower = self.techLevelFlower
                self.game.addObject(newPlant)
            else:
                return "Cannot spread. You do not have enough resources"
        else:
            return "Coordinate not within range of plant"

    @checkOwnership("spawn")
    def spawn(self, x, y):
        if(not self.flower):
            return str(self.id) + " does not have a flower, cannot spawn"
        if(((x == self.x+1) or (x == self.x-1)) 
           and ((y == self.y+1) or (y == self.y-1))):
            if(self.owner.light >= Plant.rootCost):
                newPlant = Plant(self.game, x, y, self.owner)
                newPlant.techLevelRoot = self.techLevelRoot + self.flowerRootUp
                newPlant.techLevelLeaf = self.techLevelLeaf + self.flowerLeafUp
                newPlant.techLevelFlower = self.techLevelFlower + self.flowerFlowerUp
                self.game.addObject(newPlant)
            else:
                return "Cannot spawn. You do not have enough resources"
        else:
            return "Cannot spawn here, it's not within range"

    @checkOwnership("talk")
    def talk(self, message):
        self.game.animations.append(['talk', self.id, message])
        return True

    def nextTurn(self):
        MappableObject.nextTurn(self)
        if (self.owner == self.game.turn and canAct):
            self.owner.light += techLevelLeaf
            #self.light += techLevelLeaf
            self.owner.score += techLevelLeaf

            self.health -= 1

            if(self.root and self.leaf and self.flower):
                self.health -= (Plant.rootHealthCost + Plant.leafHealthCost + Plant.flowerHealthCost)
            elif(self.root and self.leaf):
                self.health -= (Plant.rootHealthCost + Plant.leafHealthCost)
            elif(self.root and self.flower):
                self.health -= (Plant.rootHealthCost + Plant.flowerHealthCost)
            elif(self.leaf and self.flower):
                self.health -= (Plant.leafHealthCost + Plant.flowerHealthCost)
            elif(self.leaf):
                self.health -= (Plant.leafHealthCost)
            elif(self.root):
                self.health -= (Plant.rootHealthCost)
            elif(self.flower):
                self.health -= (Plant.flowerHealthCost)

            if ( self.health <= 0 ):
                self.game.removeObject(self)
