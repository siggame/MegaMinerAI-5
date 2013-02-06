"""
   Copyright (C) 2008 by Steven Wallace
   snwallace@gmail.com

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
from __future__ import with_statement
import socket
import select
import threading
import functools

import Filter

class Server:
    def __init__(self):
        self.__stop = False
        self.server = False
        self.lock = threading.Lock()
        self.ready = threading.Event()
        
    def run(self):
        self.__stop = False
        while not self.__stop:
            self.poll()

    def stop(self):
        self.__stop = True

    def poll(self):
        pass

class TCPServer(Server):
    def __init__(self, port, *filters):
        Server.__init__(self)
        self.filters = filters
        self.serverSocket = None
        self.sockets = []
        self.localaddr = ""
        if port:
            self.serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.serverSocket.bind(('0.0.0.0', port))
            self.serverSocket.listen(5)

            self.sockets = [self.serverSocket]
        self.connections = {}

    def poll(self):
        with self.lock:
            try:
                inputReady = select.select(self.sockets, [], [])[0]

                for s in inputReady:
                    if s == self.serverSocket:
                        ssocket, address = s.accept()
                        address = address[0]
                        self.openSocket(ssocket, address, True)

                    else:
                        try:
                            self.connections[s].poll()
                        except Exception, e:
                            raise
            except Exception, e:
                raise

    def openConnection(self, host, port):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((host, port))
        return self.openSocket(s, host)

    def openSocket(self, socket, address, server=False):
        self.sockets.append(socket)
        filters = [Filter.TCPFilter(socket)] + [i() for i in self.filters]
        reduce(Filter.cascadeSetIn, filters)
        for i in filters:
            i.server = server
            i.address = address
            i.master = self
        t = threading.Thread(None, filters[0].begin)
        t.start()
        self.connections[socket] = filters[0]
        return filters[-1]

    def remove(self, key):
        if key in self.connections:
            del self.connections[key]
            self.sockets.remove(key)
            return True
        return False
