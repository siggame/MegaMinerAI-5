from base import *
from matchUtils import *
import plant
import config.config
from collections import defaultdict
from sexpr.sexpr import *
import os
import itertools
import scribe

Plant = plant.Plant
Scribe = scribe.Scribe

def loadClassDefaults(cfgFile = "config/defaults.cfg"):
    cfg = config.config.readConfig(cfgFile)
    for className in cfg.keys():
        for attr in cfg[className]:
            setattr(eval(className), attr, cfg[className][attr])

class Match(DefaultGameWorld):
    def __init__(self, id, controller):
        self.id = int(id)
        self.controller = controller
        DefaultGameWorld.__init__(self, Match.maxX, Match.maxY)
        self.scribe = Scribe(self.logPath())
        self.addPlayer(self.scribe, "spectator")

    def addPlayer(self, connection, type="player"):
        connection.type = type
        if (len(self.players) >= 2 and cmp(type, "player") == 0):
            return "Game is full"
        if (cmp(type, "player") == 0):
            self.players.append(connection)
        elif (cmp(type, "spectator") == 0):
            self.spectators.append(connection)
            #If the game has already started, send them the ident message
            if (self.turn is not None):
                self.sendIdent([connection])
        return True

    def removePlayer(self, connection):
        if (cmp(connection.type, "player"))==0:
            if self.turn is not None:
                winner = self.players[1 - self.getPlayerIndex(connection)]
                self.declareWinner(winner)
            self.players.remove(connection)
        else:
            self.spectators.remove(connection)

    def start(self):
        if len(self.players) < 2:
            return "Game is not full"
        if (self.winner is not None or self.turn is not None):
            return "Game has already begun"
        for i in self.players:
            i.score = 0
        self.mapGeneration()
        self.turnNum = -1
        self.sendIdent(itertools.chain(self.players, self.spectators))

        self.nextTurn()
        return True

    def mapGeneration(self):
        startX = 2
        startY = 2
        self.addObject(Plant(self, startX, startY, self.players[0]))
        self.addObject(Plant(self, -startX, -startY, self.players[1]))

    def nextTurn(self):
        self.turnNum += 1
        if (self.turn == self.players[0]):
            self.turn = self.players[1]
        else:
            self.turn = self.players[0]

        for obj in self.objects.values():
            obj.nextTurn()

        self.dealBarkDamage()

        self.sendStatus(itertools.chain(self.players, self.spectators))

        for obj in self.objects.values():
            obj.changed = False
        self.animations = ["animations"]
        self.checkWinner()

    def dealBarkDamage(self):
        barkDamage = 0
        for obj in self.objects.values():
            if obj.owner == self.turn:
                barkDamage -= obj.bark
            else:
                barkDamage += obj.bark
        barkDamage = max(0, barkDamage)
        for obj in self.objects.values():
            if obj.owner == self.turn:
                obj.light -= barkDamage
                obj.water -= barkDamage
            if obj.light < 0 or obj.water < 0:
                self.removeObject(obj)


    def checkWinner(self):
        if (self.turnNum >= self.turnLimit):
            if (self.netWorth(self.players[0]) > \
              self.netWorth(self.players[1])):
                self.declareWinner(self.players[0])
            else:
                self.declareWinner(self.players[1])

    def netWorth(self, player):
        value = player.score
        return value
    
    def declareWinner(self, winner):
        self.winner = winner
        self.turn = None

        msg = ["game-winner", self.id, self.winner.user, self.getPlayerIndex(self.winner)]
        self.scribe.writeSExpr(msg)
        self.scribe.finalize()
        self.removePlayer(self.scribe)

        for p in self.players:
            p.writeSExpr(msg)
        
    def logPath(self):
        return "logs/" + str(self.id) + ".gamelog"
    
    @requireReferences(Plant)
    def buildLeaf(self, plantID):
        return self.objects[plantID].buildLeaf()

    @requireReferences(Plant)
    def buildRoot(self, plantID):
        return self.objects[plantID].buildRoot()

    @requireReferences(Plant)
    def buildBark(self, plantID):
        return self.objects[plantID].buildBark()

    @requireReferences(Plant)
    def buildFlower(self, plantID):
        return self.objects[plantID].buildFlower()

    def sendIdent(self, players):
        if len(self.players) < 2:
            return False
        list = []
        for i in itertools.chain(self.players, self.spectators):
            list += [[self.getPlayerIndex(i), i.user, i.screenName, i.type]]
        for i in players:
            i.writeSExpr(['ident', list, self.id, self.getPlayerIndex(i)])

    def getPlayerIndex(self, player):
        try:
            playerIndex = self.players.index(player)
        except ValueError:
            playerIndex = -1
        return playerIndex

    def sendStatus(self, players):
        for i in players:
            i.writeSExpr(self.status())
            i.writeSExpr(self.animations)

    def sendChanged(self, players):
        """
        An alternative to sendStatus, where objects are only sent if they
        have changed since last turn.
        """
        for i in players:
            i.writeSExpr(self.status(False))
            i.writeSExpr(self.animations)

    def status(self):
        msg = ["status"]

        msg.append(["game", self.turnNum, self.players[0].score, 
                    self.players[1].score, Match.maxX, Match.maxY])
        typeLists = defaultdict(list)
        for obj in self.objects.values():
            typeLists[obj.__class__].append(obj)
        for type in typeLists.keys():
            if (len(typeLists[type]) > 0):
                msg.append([type.__name__] +
                           [j.toList() for j in typeLists[type]])
        return msg

    @requireReferences(Plant)
    def talk(self, plantID, message):
        return self.objects[plantID].talk(message)

loadClassDefaults()

