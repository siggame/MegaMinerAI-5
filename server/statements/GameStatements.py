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
from StatementUtils import dict_wrapper, require_length, require_game
import statements.Statements as Statements

games = Statements.games


id = 0
client_version = 2
statements = {}
wrapper = dict_wrapper(statements)


@wrapper('game-talk')
@require_length(3)
@require_game
def gameChat(self, expression):
    if games[self.game].turn != self:
        self.writeSExpr(['game-talk-denied', 'not your turn'])
        return False
    try:
        plantid = int(expression[1])
	message = expression[2]
    except:
        self.writeSExpr(['game-talk-denied', 'arguments not integers'])
        return False

    errBuff = games[self.game].talk(plantid, message)
    if errBuff != True:
        self.writeSExpr(['game-talk-denied', errBuff])
        return False
    return True


@wrapper('game-start')
@require_length(1)
@require_game
def gameStart(self, expression):
    errBuff = games[self.game].start()
    if errBuff != True:
        self.writeSExpr(['game-denied', errBuff])
        return False
    return True

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

@wrapper('game-status')
@require_length(1)
@require_game
def gameStatus(self, expression):
    games[self.game].sendStatus([self])
    return True

@wrapper('game-grow-leaf')
@require_length(2)
@require_game
def gameMove(self, expression):
    if games[self.game].turn != self:
        self.writeSExpr(['game-grow-leaf-denied', 'not your turn'])
        return False
    try:
        id = int(expression[1])
    except:
        self.writeSExpr(['game-grow-leaf-denied', 'arguments not integers'])
        return False
    
    errBuff = games[self.game].buildLeaf(id)
    if errBuff != True:
        self.writeSExpr(['game-grow-leaf-denied', errBuff])
        return False
    return True

@wrapper('game-grow-root')
@require_length(2)
@require_game
def gameMove(self, expression):
    if games[self.game].turn != self:
        self.writeSExpr(['game-grow-root-denied', 'not your turn'])
        return False
    try:
        id = int(expression[1])
    except:
        self.writeSExpr(['game-grow-root-denied', 'arguments not integers'])
        return False

    errBuff = games[self.game].buildRoot(id)
    if errBuff != True:
        self.writeSExpr(['game-grow-root-denied', errBuff])
        return False
    return True


@wrapper('game-grow-flower')
@require_length(2)
@require_game
def gameMove(self, expression):
    if games[self.game].turn != self:
        self.writeSExpr(['game-grow-flower-denied', 'not your turn'])
        return False
    try:
        id = int(expression[1])
    except:
        self.writeSExpr(['game-grow-flower-denied', 'arguments not integers'])
        return False

    errBuff = games[self.game].buildFlower(id)
    if errBuff != True:
        self.writeSExpr(['game-grow-flower-denied', errBuff])
        return False
    return True

@wrapper('game-grow-bark')
@require_length(2)
@require_game
def gameMove(self, expression):
    if games[self.game].turn != self:
        self.writeSExpr(['game-grow-bark-denied', 'not your turn'])
        return False
    try:
        id = int(expression[1])
    except:
        self.writeSExpr(['game-grow-bark-denied', 'arguments not integers'])
        return False

    errBuff = games[self.game].buildBark(id)
    if errBuff != True:
        self.writeSExpr(['game-grow-bark-denied', errBuff])
        return False
    return True



@wrapper('end-turn')
@require_length(1)
@require_game
def endTurn(self, expression):
    if games[self.game].turn != self:
        self.writeSExpr(['end-turn-denied', 'not your turn'])
        return False
    games[self.game].nextTurn()
    return True


