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
  gp.competition();
  //gp.selfImprovePop();
  return 0;
}
