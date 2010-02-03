//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that

#include <iostream>
#include <cstring>

#include "AI.h"
#include "network.h"
#include "game.h"
#include "sexp/sexp.h"

using namespace std;

int main(int argc, char** argv)
{

  if(argc < 2)
  {
    cout<<"Please enter a host name."<<endl;
    return 1;
  }

  AI ai;
  int socket = open_server_connection(argv[1], "19000");
  if(socket == -1)
  {
    cerr << "Unable to connect to server" << endl;
    return 1;
  }
  if(!serverLogin(socket, ai.username(), ai.password()))
  {
    return 1;
  }

  if(argc < 3)
  {
    socket = createGame();
  }
  else
  {
    socket = joinGame(atoi(argv[2]));
  }
  while(networkLoop(socket))
  {
    if(ai.startTurn())
    {
      endTurn();
    }
    else
    {
      getStatus();
    }
  }
  //Wait for log
  while (networkLoop(socket)){}
  return 0;
}
