import game.base as base
import unittest
import collections
import match
import matchUtils
import math
import os

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

    def checkResources(self, p0Light, p1Light):
        self.assertEqual(self.players[0].light, p0Light)
        self.assertEqual(self.players[1].light, p1Light)

    def test_resource_collection(self):
        self.game.start()
        self.checkResources(0, 1)
        self.game.nextTurn()
        self.checkResources(1, 1)
        self.game.nextTurn()
        self.checkResources(1, 2)

    def test_status_messages(self):
        self.game.start()
        expected = ['ident', [[0, 'Username', 'Bob', 'player'], \
                        [1, 'Username', 'Tod', 'player'], \
                        [-1, 'Scribe', 'Scribe', 'spectator'], \
                        [-1, 'Username', 'Joe', 'spectator']], 7001, 0]
        self.assertEqual(self.players[0].messages[0], expected)
        expected = ['status', ['game', 0, 0, 1, 0, 1, 20, 20], 
        ['Plant', [0, 9, 9, 0, 0, 1, 0, 20, 1, 1, 1, 0, 0, 0, 1], 
        [1, 10, 10, 1, 0, 1, 0, 18, 1, 1, 1, 0, 0, 0, 0]]]
        self.assertEqual(expected, self.game.status())

    def test_grow_parts(self):
        self.game.start()
        for i in xrange(3):
            self.assertNotEqual(True, self.game.buildLeaf(0))
            self.assertNotEqual(True, self.game.buildRoot(0))
            self.assertNotEqual(True, self.game.buildLeaf(1))
            self.assertNotEqual(True, self.game.buildRoot(1))
            self.game.nextTurn()
        self.checkResources(2, 2)
        self.assertEqual(True, self.game.buildRoot(1))
        self.checkResources(2, 0)

    def test_declare_winner(self):
        self.game.start()
        for i in xrange(499):
            self.assertEqual(self.game.winner, None)
            for obj in self.game.objects.values():
                obj.health = 1000
            self.game.nextTurn()
        self.assertEqual(self.game.netWorth(self.players[0]), 250)
        self.assertEqual(self.game.netWorth(self.players[1]), 250)
        expected = ["game-winner", 7001, "Username", 1]
        self.assertEqual(self.players[0].messages[-1], expected)
        self.assertEqual(self.game.winner, self.players[1])

    def test_annhilation(self):
        """ Ensure a player without plants loses """
        self.game.start()
        for i in xrange(200):
            self.assertEqual(self.game.winner, None)
            for obj in self.game.objects.values():
                obj.health = 1000
            self.game.nextTurn()
        self.game.removeObject(self.game.objects[1])
        self.game.nextTurn()
        expected = ["game-winner", 7001, "Username", 0]
        self.assertEqual(self.players[0].messages[-1], expected)
        self.assertEqual(self.game.winner, self.players[0])
        self.assertEqual(self.players[1].score, 0)


    def test_animations(self):
        self.game.start()
        expected = ['animations', ['add', 0], ['add', 1]]
        self.assertEqual(self.players[0].messages[-1], expected)
        self.players[0].light = 1000
        self.game.objects[0].leaf = 0
        self.game.objects[0].canAct = 1
        self.game.buildLeaf(0)
        self.game.objects[0].canAct = 1
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

    def test_join_mid_game(self):
        self.game.removePlayer(self.players[2])
        self.game.start()
        self.game.addPlayer(self.players[2], "spectator")
        self.assertEqual(self.players[2].messages[0][0], "ident")

    def test_leave_mid_game(self):
        self.game.start()
        self.game.removePlayer(self.players[0])
        self.assertEqual(self.game.winner, self.players[1])

    def test_tagging(self):
        filename = "logs/7001.tags"
        if os.path.exists(filename):
            os.remove(filename)
        self.game.start()
        self.game.addTag("first player tag")
        self.game.nextTurn()
        self.game.addTag("second")
        self.game.addTag("player")
        self.game.addTag("tags!")
        self.game.removeObject(self.game.objects[1])
        self.game.nextTurn()
        expected = "7001, Username, Username\nfirst player tag\n" \
                  +  "second, player, tags!\n"
        file = open(filename, 'r')
        self.assertEqual(file.read(), expected)

