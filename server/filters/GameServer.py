"""
    Class files for a game server, interacting with the redirect server.
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

import sys
import signal
import threading
import sexpr.sexpr as sexpr

from functools import wraps
from networking.Client import AsyncClient
from GameFilter import GameFilter
from networking.Filter import PacketizerFilter, CompressionFilter
from networking.Server import TCPServer

class ServerException(Exception):
    pass

class GameServer(object):
    """
    Contacts redirect server.
    Accepts clients
    """

    class CustomGameFilter(GameFilter):
        """
        Inner class that is used to make hooks from methods in GameFilter to methods in GameServer
        Note: __init__ must have "self.controller = controller" as it's first line.
        """
        @staticmethod
        def runFunctionBeforeMethod(f):
            def decoratorMethod(m):
                @wraps(m)
                def wrapper(self, *args, **kwargs):
                    f(self.controller)
                    return m(self, *args, **kwargs)
                return wrapper
            return decoratorMethod

        @staticmethod
        def runFunctionAfterMethod(f):
            def decoratorMethod(m):
                @wraps(m)
                def wrapper(self, *args, **kwargs):
                    ret = m(self, *args, **kwargs)
                    f(self.controller)
                    return ret
                return wrapper
            return decoratorMethod

        def __init__(self, controller):
            self.controller = controller
            GameFilter.__init__(self)


    def __init__(self, user, password):
        self.client = AsyncClient()
        self.user = user
        self.password = password

    def GameFilter(self):
            return GameServer.CustomGameFilter(self)

    def sendToRedirect(self, l):
        self.client.send(sexpr.sexpr2str(l))

    def login(self):
        self.sendToRedirect(['login', self.user, self.password])
        if not('login-accepted' in self.client.getText()):
            raise ServerException("Could not login as %s" % self.user)

    def registerAsServer(self):
        self.sendToRedirect(['register-server'])
        if not('successful' in self.client.getText()):
            raise ServerException("Couldn't regiser as a server")

    def runServer(self, telnet_disabled):
        filters = ([PacketizerFilter, CompressionFilter] if telnet_disabled else []) + [self.GameFilter]
        self.server = TCPServer(19001,  *filters)
        server_thread = threading.Thread(None, self.server.run)
        server_thread.run()

    def run(self, telnet_disabled, address="localhost", port=19000):
        self.client.connect(address, port)
        self.login()
        self.registerAsServer()
        self.runServer(telnet_disabled)
