#!/usr/bin/python
from networking.Client import Client
import sys

class Telnet(Client):
    def readConsole(self):
        try:
            while 1:
                message = raw_input()
                self.send(message)
        except:
            self.exit()

    def mainloop(self, server='127.0.0.1', port=19000):
        self.connect(server, port)
        self.readConsole()


if __name__ == "__main__":
    telnet = Telnet()
    if len(sys.argv) == 3:
        telnet.mainloop(sys.argv[1], sys.argv[2])
    else:
        telnet.mainloop()
