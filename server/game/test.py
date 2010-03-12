import game.base as base
import unittest
import collections
import match
import matchUtils
import math

Match = match.Match

def string_exception(e):
    return ', '.join(str(n) for n in [e.__class__, e])

class TestBaseObjects(unittest.TestCase):

    def setUp(self):
        self.world = base.RectangularGameWorld(10, 10)

    def test_build_world(self):
        self.assertFalse(self.world == None)
        self.assertFalse(self.world.area == None)

    def test_lookup(self):
	k = self.world
	self.assertTrue(isinstance(k.area, collections.defaultdict))
        try:
            k.area[1]
        except Exception, e:
            self.assertTrue(isinstance(e, TypeError), string_exception(e))
        try:
            k.area[(1,2,3)]
        except Exception, e:
            self.assertTrue(isinstance(e, TypeError), string_exception(e))
        try:
            k.area[('a',1)]
        except Exception, e:
            self.assertTrue(isinstance(e, TypeError), string_exception(e))
        try:
            k.area[(11,10)]
        except Exception, e:
            self.assertTrue(isinstance(e, IndexError), string_exception(e))
        e = 10
        try:
            k.area[(0,0)].append(e)
            self.assertTrue(e in k.area[(0,0)])
        except Exception, e:
            self.fail()

class MockPlayer(object):
    """
    An object to receive messages as if it were a player.  This class will
    be used to test the game code without having to rely on all the
    networking code.
    """
    def __init__(self):
        self.messages = [] #A list of messages this player has received
        self.user = "Username"
	self.screenName = "Screenname"
	self.ID = 0

    def writeSExpr(self, message):
        self.messages.append(message)

    def last(self):
        return self.messages[len(self.messages) - 1]


class TestMatchStart(unittest.TestCase):
    def setUp(self):
        self.game = Match(7000, None)
        self.players = [MockPlayer(), MockPlayer()]
        self.game.declareWinner = lambda self: None

    def test_join_game(self):
        """
        Tests Match.addPlayer and Match.nextTurn
        """
        self.assertEqual(self.game.players, [])
        self.game.addPlayer(self.players[0])
        self.assertNotEqual(True, self.game.start())
        self.assertEqual([self.players[0]], self.game.players)
        self.game.addPlayer(self.players[1])
        self.assertEqual(self.players, self.game.players)
        self.assertNotEqual(True, self.game.addPlayer(MockPlayer()))
        self.assertEqual(True, self.game.start())
        self.assertEqual(self.game.turn, self.players[0])
        self.game.nextTurn()
        self.assertEqual(self.game.turn, self.players[1])
        self.game.nextTurn()
        self.assertEqual(self.game.turn, self.players[0])

class MockGame(object):
    def __init__(self):
        self.objects = {}

    @matchUtils.requireReferences(str, None, int)
    def wrappedFunction(self, a, b, c):
	return True

class TestRequireReferences(unittest.TestCase):
    def setUp(self):
	self.game = MockGame()
	self.game.objects[0] = "Hello"
	self.game.objects[1] = 3.14159
	self.game.objects[2] = 42

    def test_require_refs(self):
	self.assertEqual(True, self.game.wrappedFunction(0, 1, 2))
	self.assertNotEqual(True, self.game.wrappedFunction(0, 2, 1))
	self.assertNotEqual(True, self.game.wrappedFunction(0, 1, 3))
	self.assertEqual(True, self.game.wrappedFunction(0, 83, 2))

class TestGameLogic(unittest.TestCase):
    def setUp(self):
	self.game = Match(7001, None)
	self.players = [MockPlayer(), MockPlayer(), MockPlayer()]
	self.players[0].screenName = "Bob"
	self.players[1].screenName = "Tod"
	self.players[2].screenName = "Joe"
	self.game.addPlayer(self.players[0], "player")
	self.game.addPlayer(self.players[1], "player")
	self.game.addPlayer(self.players[2], "spectator")

    def checkResources(self, p0Water, p0Light, p1Water, p1Light):
        self.assertEqual(self.game.objects[0].water, p0Water)
        self.assertEqual(self.game.objects[0].light, p0Light)
        self.assertEqual(self.game.objects[1].water, p1Water)
        self.assertEqual(self.game.objects[1].light, p1Light)

    def test_resource_collection(self):
	self.game.start()
	self.checkResources(1, 1, 0, 0)
	self.game.nextTurn()
	self.checkResources(1, 1, 1, 1)
	self.game.nextTurn()
	self.checkResources(2, 2, 1, 1)

    def test_status_messages(self):
	self.game.start()
	expected = ['ident', [[0, 'Username', 'Bob', 'player'], \
			[1, 'Username', 'Tod', 'player'], \
			[-1, 'Scribe', 'Scribe', 'spectator'], \
			[-1, 'Username', 'Joe', 'spectator']], 7001, 0]
	self.assertEqual(self.players[0].messages[0], expected)
	expected = ["status", ["game", 0, 2, 0, 10, 10], ["Plant", [0,2, 2, 0, 1, 1, 0, 0,1,1], [1, -2, -2, 1, 1, 1, 0, 0,0,0] ] ] 
	self.assertEqual(expected, self.game.status())

    def test_grow_parts(self):
	self.game.start()
	for i in xrange(8):
	    self.assertNotEqual(True, self.game.buildLeaf(0))
	    self.assertNotEqual(True, self.game.buildRoot(0))
	    self.assertNotEqual(True, self.game.buildLeaf(1))
	    self.assertNotEqual(True, self.game.buildRoot(1))
	    self.game.nextTurn()
	self.assertEqual(True, self.game.buildLeaf(0))
	self.assertNotEqual(True, self.game.buildRoot(1))
	self.game.nextTurn()
	self.game.nextTurn()
	self.assertNotEqual(True, self.game.buildRoot(1))
	self.game.nextTurn()
	self.assertEqual(True, self.game.buildRoot(1))
	self.game.nextTurn()
	self.game.nextTurn()
	self.checkResources(5, 4, 3, 5)

    def test_bark(self):
	self.game.start()
	self.game.objects[0].water = 10 + match.Plant.barkCostWater
	self.game.objects[0].light = 10 + match.Plant.barkCostLight
	self.game.objects[1].water = 3
	self.game.objects[1].light = 3
	self.game.objects[1].bark = 5
	self.assertEqual(True, self.game.buildBark(0))
	self.game.nextTurn()
	#ensure bark does no harm if you have more than the other player
	self.checkResources(10, 10, 4, 4)
	self.game.nextTurn()
	#ensure bark reduces resources if you have less
	self.checkResources(7, 7, 4, 4)
	self.game.objects[0].bark = 11
	self.game.nextTurn()
	#ensure falling into negative resources can kill a plant
	self.assertEqual(None, self.game.objects.get(1))
	expected = ["animations", ["remove", 1]]

    def test_declare_winner(self):
	self.game.start()
	for i in xrange(499):
	    self.assertEqual(self.game.winner, None)
	    self.game.nextTurn()
	self.assertEqual(self.game.netWorth(self.players[0]), 500)
	self.assertEqual(self.game.netWorth(self.players[1]), 500)
	expected = ["game-winner", 7001, "Username", 1]
	self.assertEqual(self.players[0].messages[-1], expected)
	self.assertEqual(self.game.winner, self.players[1])

    def test_animations(self):
	self.game.start()
	expected = ['animations', ['add', 0], ['add', 1]]
	self.assertEqual(self.players[0].messages[-1], expected)
	self.game.objects[0].water = 100
	self.game.objects[0].light = 100
	self.game.buildLeaf(0)
	self.game.buildRoot(0)
	expected = ['animations', ['grow-leaf', 0], ['grow-root', 0]]
	self.assertEqual(self.game.animations, expected)
	self.game.nextTurn()
	expected = ['animations']
	self.assertEqual(self.game.animations, expected)

    def test_talk(self):
	self.game.start()
	taunt1 = "Neener-neener."
	taunt2 = "You're mother is a fine lady"
	self.assertEqual(True, self.game.talk(0, taunt1))
	self.assertNotEqual(True, self.game.talk(1, taunt2))
	expected = ["animations", ["talk", 0, taunt1]]
	self.assertEqual(self.game.animations, expected)


    def test_steal(self):
	self.game.start()
	theif = match.Plant(self.game, -2, -1, self.players[0])
        theif.roots = int(match.Plant.rootsToSteal)
        theif.leaves = int(match.Plant.leavesToSteal - 1)
	self.game.addObject(theif)
	self.game.nextTurn()
	self.checkResources(1, 1, 0, 1)

    def test_reproduction(self):
	self.game.start()
	self.game.objects[1].flowers = 2
	self.game.nextTurn()
	self.assertNotEqual([], self.game.area[(-2,-3)])
	self.assertEqual(2, self.game.objects[2].water)

    def test_map_boundaries(self):
	self.game.start()
	for i in [0, 1]:
	    self.game.objects[i].x = int(math.pow(-1, i) * 10)
	    self.game.objects[i].y = int(math.pow(-1, i) * 10)
	    self.game.objects[i].flowers = 1
	self.game.nextTurn()
	self.game.nextTurn()
	self.game.objects.values()

    def test_join_mid_game(self):
	self.game.removePlayer(self.players[2])
	self.game.start()
	self.game.addPlayer(self.players[2], "spectator")
	self.assertEqual(self.players[2].messages[0][0], "ident")

    def test_leave_mid_game(self):
	self.game.start()
	self.game.removePlayer(self.players[0])
	self.assertEqual(self.game.winner, self.players[1])
