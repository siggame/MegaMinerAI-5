//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that

#include <iostream>
#include <cstring>

#include "AI.h"
#include "network.h"
#include "game.h"
#include "sexp/sexp.h"
#include "gp.h"

using namespace std;

int main(int argc, char** argv)
{
  if(argc < 3)
  {
    cout<<"Requires 2 arguments, host and pop size"<<endl;
    return 1;
  }
  GP gp(argv[1],atoi(argv[2]));

  //Used to prevent 508 Hangup.

  while(true)
  {
    for(unsigned int i=0;i<5;i++)
    {
      cout<<"TOP Begin Competition"<<endl;
      gp.competition();
      cout<<"TOP Starting Recombination"<<endl;
      gp.popDump();
      gp.recombination();
      
    }
    cout<<"TOP Doing Self Improvement"<<endl;
    gp.selfImprovePop();
    gp.popDump();
  }
  return 0;
}

