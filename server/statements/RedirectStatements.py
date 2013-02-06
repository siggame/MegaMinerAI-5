"""
    Statements for Redirect Server.
    Copyright (C) 2009  Josh Bohde <josh.bohde@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""
from StatementUtils import require_login, require_length, dict_wrapper
from ServerStatements import statements as server_statements
statements = dict(server_statements)
mapper = dict_wrapper(statements)

@mapper("ping")
@require_length(1)
def ping(self, expression):
    self.writeSExpr(['pong'])
    return True

@mapper("whoami")
@require_length(1)
def whoAmI(self, expression):
    self.writeSExpr(['who-you-are', ['id', self.ID], ['address', self.address]])
    return True

@mapper('register-server')
@require_length(1)
@require_login
def registerServer(self, expression):
    self.registerAsServer()
    self.writeSExpr(['registered-status', 'successful'])
    return True

@mapper('list-servers')
@require_length(1)
@require_login
def listServers(self, expression):
    self.writeSExpr(['servers', self.getServers()])
    return True

@mapper('get-server')
@require_length(1)
@require_login
def getServer(self, expression):
    self.writeSExpr(["server"] + self.chooseServer())
    return True

@mapper('start-game')
@require_length(1)
@require_login
def startGame(self, expression):
    self.writeSExpr(self.createGame())
    return True

@mapper('join-game')
@require_length(2)
@require_login
def joinGame(self, expression):
    try:
        self.writeSExpr(self.lookupGame(int(expression[1])))
        return True
    except:
        self.writeSExpr(['join-game-denied', ['invalid-number', expression[1]]])
    
@mapper('game-over')
@require_length(4)
@require_login
def endGame(self, expression):
    if cmp(self.user, "slave") != 0:
        print self.user
        print "game-over message received from a user"
        return
    try:
        gameID = int(expression[1])
        winnerUser = str(expression[2])
        if self.deleteGame(gameID):
            self.writeSExpr(['game-ended', gameID])
            #print "%s just won game %d!" % (winnerUser, gameID)
            return
    except:
        pass
    self.writeSExpr(['end-game-denied', ['invalid-number', expression[1]]])

