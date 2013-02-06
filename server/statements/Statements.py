"""

   Copyright (C) 2008 by Steven Wallace, Ben Murrell
   snwallace@gmail.com, ben@benmurrell.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the
    Free Software Foundation, Inc.,
    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 """
import sexpr.sexpr
import random
import math
from game.match import Match
from StatementUtils import dict_wrapper, require_length, require_game, \
                           require_login
import bz2
import time
import threading

games = {}
id = 0
client_version = 2
statements = {}
wrapper = dict_wrapper(statements)

@wrapper('winner')
@require_length(2)
def winner(self, expression):
    try:
        game = int(expression[1])
    except:
        game = None

    if game not in games:
        self.writeSExpr(['winner-denied', 'no such game', game])
        return False
    self.writeSExpr(['game-winner', game, games[game].winner and games[game].winner.user])
    return True

@wrapper('create-game')
@require_length(2)
def createGame(self, expression):
    try:
        game = int(expression[1])
    except:
        self.writeSExpr(['create-game-denied', 'invalid game number'])
        return False

    print "Creating game " + str(game)

    if games.get(game, None) is not None:
        self.writeSExpr(['create-game-denied', 'game number already exists'])

    games[game] = Match(game, self.controller)

    return True

@wrapper('join-game')
@require_login
@require_length(2, 3)
def joinGame(self, expression):
    if self.game is not None:
        self.writeSExpr(['join-game-denied', 'already in a game'])
        return False

    try:
        game = int(expression[1])
    except:
        game = None

    try:
        self.type = str(expression[2])
    except:
        self.type = "player"

    if not self.type in ["player", "spectator"]:
        self.writeSExpr(['join-game-denied', 'invalid connection type'])
        self.type = None
        return False

    if game not in games:
        self.writeSExpr(['join-game-denied', 'no such game', game])
        return False

    errBuff = games[game].addPlayer(self, self.type)

    if errBuff != True:
        self.writeSExpr(['join-game-denied', errBuff])
        return False

    self.game = game

    return True

@wrapper('leave-game')
@require_game
@require_length(1)
def leaveGame(self, expression):
    games[self.game].removePlayer(self)
    if len(games[self.game].players) + len(games[self.game].spectators) == 0:
        del games[self.game]
    self.type = None
    self.game = None

@wrapper('request-log')
@require_length(2)
def requestLog(self, expression):
    logID = str(expression[1])
    infile = bz2.BZ2File("logs/" + logID + ".gamelog.bz2", "r")
    self.writeSExpr(['log', logID, infile.read()])

