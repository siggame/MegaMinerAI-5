#!/bin/env python
# -*-python-*-

from library import library

from AI import AI

import sys

def main():
  if len(sys.argv) < 2:
    print "Please enter a host name."
    exit(1)
    
  ai = AI()
    
  socket = library.open_server_connection(sys.argv[1], "19000")
  if socket == -1:
    sys.stderr.write("Unable to connect to server\n")
    exit(1)
  
  if not library.serverLogin(socket, ai.username(), ai.password()):
    exit(1)
  
  if len(sys.argv) < 3:
    socket = library.createGame()
  else:
    socket = library.joinGame(int(sys.argv[2]))
  while library.networkLoop(socket, 0):
    if ai.startTurn():
      library.endTurn()
    else:
      library.getStatus()
  
  #request the log file
  while library.networkLoop(socket, 0):
    pass
  exit(0)


if __name__ == '__main__':
  main()
