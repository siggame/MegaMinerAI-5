/*Brian Goldman <bwgxc9@mst.edu>
  This is a debug client for Bloom.  It should make only legal actions
  It should make every action at random.
  If you want to change the order things are perform in, change how they are rated by evalSpace(space sp)
  If you want to turn of actions, in the buildQueue() function comment out the que.push command for that action
  
*/
#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <vector>
#include <queue>
#include <ctime>

using namespace std;
//an enum for actions
enum GROW {LEAF,ROOT,FLOWER,SEED,NOOP,GROW_SIZE};
const static string growToString[] = {"LEAF","ROOT","FLOWER","SEED","NOOP","SIZE"};
//Data structure that stores everything about a possible action
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
};


///The class implementing gameplay logic.
class AI: public BaseAI
{
public:
  virtual const char* username();
  virtual const char* password();
  virtual void init();
  virtual bool run();
  //a function to get my light value
  int myLight(){return (playerID())?player1Light():player0Light();};
  //the queue for actions
  priority_queue<space> que;
  //a grid listing valid spread and spawn locations
  //THIS IS OFFSET to include a row/col for both -1 and boardSize+1
  vector< vector< bool > > canBuildHere;
  //sets up blocking information
  void setCanBuildHere();
  //builds up a queue of everything you can do
  void buildQueue();
  //does the best action, returns false if more is to be done
  bool doActions();
  //returns true if you have the resources for an action
  bool canDo(GROW ACTION);
  
  //sets the rating on an action
  float evalSpace(space sp);
  
};

#endif
