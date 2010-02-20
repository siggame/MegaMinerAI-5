import itertools
import collections
import functools
import mappableObject
MappableObject = mappableObject.MappableObject

class RectangularArea(collections.defaultdict):
    """
    The actual "board". Lookup on either a tuple or list of two integers. Can be thought of a matrix from (-x,-y) to (x,y).
    Returns a list of the objects at that location.
    """
    def __init__(self, max_x, max_y):
        collections.defaultdict.__init__(self, list)
        self.max_x = max_x
        self.max_y = max_y

    def __missing__(self, key):
        if not(isinstance(key, (list, tuple))):
                raise TypeError('%s is not a list or tuple.' % key.__class__)
        if len(key) != 2:
            raise TypeError('A coordinate does not have a length of %u!' % len(key))
        if not(all([isinstance(n, int) for n in key])):
            raise TypeError('Coordinates need to be integers!')
        x, y = key
        if not self.inBounds(x,y):
            raise IndexError('(%u, %u) is not within (-+%u, -+%u)' % (x, y, self.max_x, self.max_y))
        return collections.defaultdict.__missing__(self, key)

    def inBounds(self, x, y):
        return (abs(x) <= self.max_x and abs(y) <= self.max_y)


class GameWorld(object):
    """
    Base class for a game world object
    """
    def __init__(self):
        self.nextid = 0
        self.maxid = 2147483600
        self.turnNum = 0
        self.players = []
	self.spectators = []
        self.turn = None #the player whose turn it is;
                         #None before and after the game.
        self.winner = None #the player who won the game;
                           #None before and during the game
        self.objects = dict() #key: object's id
                              #value: instance of the object
        self.animations = ["animations"]

    def addObject(self, newObject):
        self.animations += [["add", newObject.id]]
        self.objects[newObject.id] = newObject
        if (isinstance(newObject, MappableObject)):
            newObject.addToMap()

    def removeObject(self, oldObject):
        self.animations += [["remove", oldObject.id]]
        if isinstance(oldObject, MappableObject):
            oldObject.removeFromMap()
        del self.objects[oldObject.id]

class RectangularGameWorld(GameWorld):
    def __init__(self, x, y):
	GameWorld.__init__(self)
	self.area = RectangularArea(x, y)

DefaultGameWorld = RectangularGameWorld
