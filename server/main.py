#!/usr/bin/python
"""
   Main executable for the servers. 
   Copyright (C) 2009 by Steven Wallace <snwallace@gmail.com>,
                         Josh Bohde <josh.bohde@gmail.com >
   
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

from networking.Server import TCPServer
from networking.Filter import PacketizerFilter, CompressionFilter
from optparse import OptionParser
from filters.RedirectFilter import RedirectFilter
from filters.GameServer import GameServer
from networking.Server import TCPServer
from networking.Filter import PacketizerFilter, CompressionFilter
from visualizer.visualizer import VisualizerClient

def runAsMain(f):
    def wrapper(*args, **kwargs):
        try:
            f(*args, **kwargs)
        except KeyboardInterrupt:
            sys.exit(0)
        except Exception, exception:
            print f.__name__, " - Unexpected error:", exception
            sys.exit(1)
        sys.exit(0)
    return wrapper

@runAsMain
def runRedirect(telnet_disabled, address, port):
    print "Running Redirect Server.", 
    filters = ([PacketizerFilter, CompressionFilter] if telnet_disabled else []) + [RedirectFilter]
    master = TCPServer(19000,  *filters)
    print "Listening on port 19000."
    master.run()

@runAsMain
def runGameServer(telnet_disabled, address, port):
    server = GameServer("slave", "12345")
    server.run(telnet_disabled, address, port)

@runAsMain
def runServerAndRedirect(telnet_disabled, address, port):
    from multiprocessing import Process
    redir = Process(target=runRedirect, args=(telnet_disabled,address, port))
    redir.start()
    server = Process(target=runGameServer, args=(telnet_disabled,address, port))
    server.start()
    redir.join()
    server.join()

def main():
    parser = OptionParser()

    parser.add_option("-r", "--redirect", action="store_true", dest="redirect",
                      default=False, help="Run a redirect server locally.")
    parser.add_option("-t", "--telnet-mode", action="store_false", dest="telnet_disabled",
                      default=True, help="Make any servers started accessible via telnet")
    parser.add_option("-b", "--run-both", action="store_true", dest="both", default=False,
                      help="Run both a redirect and game server.")
    parser.add_option("-p", "--port", action="store", dest="port", type="int", default=19000,           
                      help="Use the specified port. Defaults to 1900")
    parser.add_option("-a", "--address", action="store", dest="address", type="string",
                      default="127.0.0.1", help="Use the specified address. Defaults to localhost")
    
    (options, args) = parser.parse_args()

    runner = None
    if(options.both):
        runner = runServerAndRedirect
    else:
        runner = (runGameServer, runRedirect)[options.redirect]
    runner(options.telnet_disabled, options.address, options.port)

if __name__ == "__main__":
    main()

