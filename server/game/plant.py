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
        self.root = 0
        self.leaf = 0
        self.flower = 0
        self.health = Plant.initialHealth
        self.owner = owner
        self.techLevelRoot = 1
        self.techLevelLeaf = 1
        self.techLevelFlower = 1
        self.flowerRootUp = 0
        self.flowerLeafUp = 0
        self.flowerFlowerUp = 0
        self.canAct = 0

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
        if not self.canAct:
            return str(self.id) + " has no actions."
        if(self.leaf):
            return str(self.id) + " cannot grow a leaf; it already has a leaf."
        if self.owner.light < Plant.leafCost * self.techLevelLeaf:
            return str(self.id) + " cannot grow leaf; not enough resources: have %s, need %s" % (self.owner.light, Plant.leafCost * self.techLevelLeaf)
        self.game.animations.append(['grow-leaf', self.id])
        self.leaf = 1
        self.owner.light -= Plant.leafCost * self.techLevelLeaf
        self.canAct -= 1
        return True

    @checkOwnership("grow a root")
    def buildRoot(self):
        if not self.canAct:
            return str(self.id) + " has no actions."
        if self.root:
            return str(self.id) + " cannot grow roots; it already has roots."
        if self.owner.light < Plant.rootCost * self.techLevelRoot: 
            return str(self.id) + " cannot grow root; not enough resources: have %s, need %s" % (self.owner.light, Plant.rootCost * self.techLevelRoot)
        self.game.animations.append(['grow-root', self.id])
        self.root = 1
        self.health += Plant.rootHealth * self.techLevelRoot
        self.owner.light -= Plant.rootCost * self.techLevelRoot
        self.canAct -= 1
        return True

    @checkOwnership("grow a flower")
    def buildFlower(self, rootUp, leafUp, flowerUp):
        if not self.canAct:
            return str(self.id) + " has no actions."
        if(self.flower):
            return str(self.id) + "cannot grow a flower; It already has a flower."
        if rootUp < 0 or leafUp < 0 or flowerUp < 0:
            return str(self.id) + " cannot have negative 'up' values."
        if rootUp + leafUp + flowerUp > self.techLevelFlower:
            return str(self.id) + " flower enhancements exceed flower level"
        if self.owner.light < Plant.flowerCost * self.techLevelFlower:
            return str(self.id) + "cannot grow flower; not enough resources: have %s, need %s" % (self.owner.light, Plant.flowerCost * self.techLevelFlower)
        self.game.animations.append(['grow-flower', self.id])
        self.flower = 1
        self.owner.light -= Plant.flowerCost * self.techLevelFlower
        self.flowerRootUp = rootUp
        self.flowerLeafUp = leafUp
        self.flowerFlowerUp = flowerUp
        self.canAct -= 1
        return True

    @checkOwnership("spread")
    def spread(self, x, y):
        cost = Plant.spreadCost * (self.techLevelRoot + self.techLevelLeaf + self.techLevelFlower)
        if not self.canAct:
            return str(self.id) + " has no actions."
        if not self.root:
            return str(self.id) + " does not have a root, cannot spread"
        if not  abs(x - self.x) + abs(y - self.y) == 1:
            return "Coordinate not within range of plant"
        try:
            self.game.area[(x, y)]
        except IndexError:
            return "Cannot spread; outside the world."
            
        if self.owner.light < cost:
            return "Cannot spread; not enough resources: have %s, need %s" % (self.owner.light, cost)
        
        self.owner.light -= cost
        self.game.animations.append(['spread', self.id, x, y])
        
        if self.game.area[(x, y)]:
            target = self.game.area[(x, y)][0]
            target.health -= Plant.rootDamage * self.techLevelRoot
        else:
            newPlant = Plant(self.game, x, y, self.owner)
            newPlant.techLevelRoot = self.techLevelRoot
            newPlant.techLevelLeaf = self.techLevelLeaf
            newPlant.techLevelFlower = self.techLevelFlower
            self.game.addObject(newPlant)
        
        self.canAct -= 1
        return True

    @checkOwnership("spawn")
    def spawn(self, x, y):
        cost = Plant.spawnCost * (self.techLevelRoot + self.techLevelLeaf + self.techLevelFlower + self.flowerRootUp + self.flowerLeafUp + self.flowerFlowerUp)
        if not self.canAct:
            return str(self.id) + " has no actions."
        if(not self.flower):
            return str(self.id) + " does not have a flower, cannot spawn"
        if not abs(x - self.x) + abs(y - self.y) == 1:
            return "Cannot spawn here; it's not within range"
        try:
            if self.game.area[(x, y)]:
                return "Cannot spawn; destination populated."
        except IndexError:
            return "Cannot spawn; outside the wold."
        if self.owner.light < cost:
            return "Cannot spawn; not enough resources: have %s, need %s" % (self.owner.light, cost)
        self.game.animations.append(['spawn', self.id, x, y])
        self.owner.light -= cost
        newPlant = Plant(self.game, x, y, self.owner)
        newPlant.techLevelRoot = self.techLevelRoot + self.flowerRootUp
        newPlant.techLevelLeaf = self.techLevelLeaf + self.flowerLeafUp
        newPlant.techLevelFlower = self.techLevelFlower + self.flowerFlowerUp
        self.game.addObject(newPlant)
        self.canAct -= 1
        return True

    @checkOwnership("talk")
    def talk(self, message):
        self.game.animations.append(['talk', self.id, message])
        return True

    def nextTurn(self):
        MappableObject.nextTurn(self)
        if (self.owner != self.game.turn):
            self.owner.light += self.techLevelLeaf * self.leaf  + Plant.minLight
            self.owner.score += self.techLevelLeaf * self.leaf + Plant.minLight

            self.health -= 1
            
            if(self.leaf):
                self.health -= (Plant.leafHealthCost)
            if(self.root):
                self.health -= (Plant.rootHealthCost)
            if(self.flower):
                self.health -= (Plant.flowerHealthCost)

            if ( self.health <= 0 ):
                self.game.removeObject(self)
            
            self.canAct = 0
        else:
            self.canAct = 1
