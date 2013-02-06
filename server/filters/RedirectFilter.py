"""
    Redirect Server implementation.
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

from __future__ import with_statement
from LogicFilter import LogicFilter
import statements.RedirectStatements as RedirectStatements
import threading

class RedirectFilter(LogicFilter):
    Servers = {}
    GameNumber = 0
    Games = dict()
    GameLock = threading.Lock()

    def _init(self):
        LogicFilter._init(self)
        self.statements = RedirectStatements.statements
        self.count = 0

    def disconnect(self):
        if self.ID:
            try:
                del RedirectFilter.Servers[self.ID]
            except Exception:
                pass
            self.ID = None
        LogicFilter.disconnect(self)

    def registerAsServer(self):
        RedirectFilter.Servers[self.ID] = self

    def getServers(self):
        return [[i, j.address] for i,j in RedirectFilter.Servers.iteritems()]

    def chooseServer(self):
        ret = [[i,j.address] for i, j in sorted(RedirectFilter.Servers.iteritems(), key=(lambda x: x[1].count))]
        return ret[0] if len(ret)>0 else []

    def createGame(self):
        srv = self.chooseServer()
        ret = ['game-number', RedirectFilter.GameNumber, ['server'] + srv]
        with RedirectFilter.GameLock:
            RedirectFilter.Games[RedirectFilter.GameNumber] = ret[2]
        RedirectFilter.Servers[srv[0]].sendGameCreation(RedirectFilter.GameNumber)
        RedirectFilter.GameNumber += 1
        RedirectFilter.Servers[ret[2][1]].count += 1
        return ret

    def sendGameCreation(self, id):
        self.writeSExpr(["create-game", id])
        
    def lookupGame(self, number):
        with RedirectFilter.GameLock:
            return RedirectFilter.Games[number]

    def deleteGame(self, number):
        with RedirectFilter.GameLock:
            if RedirectFilter.Servers[RedirectFilter.Games[number][1]] == self:
                del RedirectFilter.Games[number]
                self.count -= 1
                return True
            return False

