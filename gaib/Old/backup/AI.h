#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <iostream>
#include "NDVector.hpp"

struct node
{
  float value;
  char op;
};

using namespace std;
///The class implementing gameplay logic.
class AI: public BaseAI
{
  
public:
  
  virtual const char* username();
  virtual const char* password();
  virtual void init();
  virtual bool run();
  unsigned int aiNum;
  bool canBuildLeaf(unsigned int index);
  bool canBuildRoot(unsigned int index);
  unsigned int rootcount;
  
  NDVector<node> tree;
  void makeTree(ifstream & file);


};

#endif
