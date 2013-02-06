#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <vector>
#include <queue>
#include <ctime>
#include "NDVector.hpp"

using namespace std;
enum GROW {LEAF,ROOT,SPREAD,FLOWER,SPAWN,NOOP,GROW_SIZE};
const string growDisplay[GROW_SIZE+1] = {"LEAF","ROOT","SPREAD","FLOWER","SPAWN","NOOP","GROW_SIZE"};
//enum OP {PLUS,MINUS,MULTIPLY,DIVIDE,OP_SIZE};
struct space
{
  space(){};
  space(unsigned int X,unsigned int Y,unsigned int ACTING,GROW ACTION):x(X),y(Y),acting(ACTING),action(ACTION),rating(0){};
  unsigned int x,y,acting;
  GROW action;
  float rating;
  friend bool operator<(const space&lhs,const space & rhs)
  {
    return lhs.rating<rhs.rating;
  }
  void display()
  {
    cout<<growDisplay[action]<<" at ("<<x<<","<<y<<") performed by plants["<<acting<<"]"<<endl;
  }
};


//TODO Acting plants index may change!
///The class implementing gameplay logic.
class AI: public BaseAI
{
public:
  virtual const char* username();
  virtual const char* password();
  virtual void init();
  virtual bool run();
  
  //int myLight(){return (playerID())?player1Light():player0Light();};
  int myLight(){return realLight;};
  int myScore(){return (playerID())?player1Score():player0Score();};
  int realLight;
  
  vector< vector< bool > > canSpawnHere;
  vector< vector< bool > > canSpreadHere;
  vector< bool > notActing;
  //the queue for actions
  priority_queue<space> que;
  
  vector<unsigned int> idList;
  vector<unsigned int> healthList;
  unsigned int workingTurn;
  
  bool canDo(unsigned int plant,GROW action);
  void resetDataStructures();
  void buildQueue();
  bool doActions();
  float evalTree(NDVector<node> & tree,space &  sp);
  
  void getFlowerUp(unsigned int index, unsigned int& root,unsigned int& leaf,unsigned int& flower);
  
  unsigned int combinedLevel(unsigned int index);
  //The GP Trees
  NDVector<node> rootTree,leafTree,spawnTree,flowerTree,noopTree;
  unsigned int aiNum;
};

#endif
