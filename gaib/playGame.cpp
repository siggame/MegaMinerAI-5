#include "playGame.h"


bool playGame(AI& fp,AI& sp,char* host,int&results)
{
  //cout<<"PlayGame Function Called"<<endl;
  int socket = open_server_connection(host, "19000");
  if(socket == -1)
  {
    cerr << "Unable to connect to server" << endl;
    return false;
  }
  if(!serverLogin(socket, fp.username(), fp.password()))
  {
    cerr << "Login Failed" << endl;
    return false;
  }
  socket = createGame();
  int game = getGameNumber();
  cout<<"TOP Game: "<<game<<endl;
  //cout<<"Above Fork"<<endl;
  pid_t pID = fork();
  if(pID ==0)//PLAYER 2
  {
    //cout<<"Fork Happened for Player 2"<<endl;
    socket = open_server_connection(host, "19000");
    if(socket == -1)
    {
      cerr << "Unable to connect to server" << endl;
      return false;
    }
    //cout<<"Attempting to log in"<<endl;
    if(!serverLogin(socket, sp.username(), sp.password()))
    {
      return false;
    }
    //cout<<"Joining Game"<<endl;
    socket = joinGame(game);
    //cout<<"Above while loop"<<endl;
    while(networkLoop(socket))
    {
      if(sp.startTurn())
      {
        endTurn();
      }
      else
      {
        getStatus();
      }
    }
  }
  else
  {
    //cout<<"P1 above while"<<endl;
    while(networkLoop(socket))
    {
      if(fp.startTurn())
      {
        endTurn();
      }
      else
      {
        getStatus();
      }
    }
  }

  //Wait for log
  while (networkLoop(socket)){}
  //Get the scores
  results=(fp.getWinValue());
  if(pID == 0)
  {
    close(socket);
       
    exit(0);
    //TODO Hack to kill the spawned copy
  }
  close(socket);
  cout<<"Game["<<game<<"] "<<fp.aiNum<<" VS "<<sp.aiNum<<" final score = "<<results<<endl;
  return true;
}
