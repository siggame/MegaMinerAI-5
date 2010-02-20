"""
    Generic logic filter for servers and clients.
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


import sexpr.sexpr as sexpr
from config.config import getUserInfo
from networking.Filter import Filter

LOGIN_CONFIG = 'config/login.cfg'

class SexprHandlerMixin(object):
    def writeSExpr(self, l):
        self.writeOut(sexpr.sexpr2str(l))

    def readSExpr(self, expression):
        for i in expression:
            self.evalStatement(i)

    def evalStatement(self, expression):
        if type(expression) != list:
            self.writeSExpr(['invalid-expression', expression])
            return False

        try:
            self.statements[expression[0]](self, expression)
        except Exception, e:
            print e
            self.writeSExpr(['malformed-statement', expression])

class LogicFilter(Filter, SexprHandlerMixin):
    ID = 0
    def _init(self, *args):
        self.user = None
        self.screenName = None
        self.password = None
        self.hash = None
        self.game = None
        self.type = None
        self.hasMap = None
        self.ID = str(LogicFilter.ID)
        LogicFilter.ID += 1
        self.run = True

    def _readOut(self, data):
        try:
            self.readSExpr(sexpr.str2sexpr(data))
        except ValueError:
            self.writeSExpr(['malformed-message', data])

    def disconnect(self):
        self.run = False
        if self.game:
            pass
            #self.readSExpr("(leave-game)")

    def login(self, user, password):
        registered = False
        output = ""
        userInfo = getUserInfo(user, LOGIN_CONFIG)

        if not (userInfo is None):
            if userInfo['password'] == password:
                registered = True
                self.user = user
                self.password = password
                self.screenName = userInfo['screenName']

        if not registered:
            output = "user    :" + user + '\n'
            output += "password:" + password + '\n\n'
            outFile = open("badLogin.dat", "a")
            outFile.write(output)
            outFile.close()

        return registered

    def logout(self):
        self.user = None
        self.password = None
        self.hash = None
        return True
