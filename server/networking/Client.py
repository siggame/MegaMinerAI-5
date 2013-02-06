"""
    Definition of client classes.
    Copyright (C) 2009 by Steven Wallace <snwallace@gmail.com>
                          Josh Bohde <josh.bohde@gmail.com>
    
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

from Server import *
from Filter import *
import thread

class Client(object):
    def __init__(self):
        self.connection = ConnectionWrapper(self)

    def connect(self, server='127.0.0.1', port=2100):
        self.connection.connect("127.0.0.1", int(port))

    def disconnect(self):
        self.connection.disconnect()

    def exit(self):
        self.disconnect()
        sys.exit()

    def send(self, message):
        self.connection.send(message)

    def display(self, text, type='default'):
        print text

    def mainloop(self, server='127.0.0.1', port=19000):
        self.connect(server, port)

class AsyncClient(Client):
    def __init__(self):
        self.receivedData = ""
        self.received = threading.Event()
        Client.__init__(self)

    def send(self, message):
        self.received.clear()
        Client.send(self, message)

    def display(self, text, type='default'):
        self.receivedData = text
        self.received.set()

    def getText(self):
        self.received.wait()
        return self.receivedData


class WrapperFilter(Filter):
    _wrapper = None
    def _init(self):
        self.wrapper = WrapperFilter._wrapper

    def readOut(self, data):
        self.wrapper.receive(data)

    def disconnect(self):
        self.wrapper.connection = None
        self.wrapper.receive("Disconnected", "status")

class ConnectionWrapper(object):
    def __init__(self, telnet):
        self.telnet = telnet
        WrapperFilter._wrapper = self
        self.server = TCPServer(None,  PacketizerFilter, CompressionFilter, WrapperFilter)
        self.connection = None

    def connect(self, server, port, filters = []):
        if self.connection:
            self.disconnect()
        if filters:
            self.server.filters = filters
        self.connection = self.server.openConnection(server, port)
        thread.start_new_thread(self.run_server, ())

    def disconnect(self):
        if not self.connection:
            return False
        self.connection.end()

    def send(self, message):
        if not self.connection:
            return False
        self.connection.writeOut(message)

    def receive(self, message, type="default"):
        self.telnet.display(message, type)

    def run_server(self):
        try:
            self.server.run()
        except Exception, e:
            print e
