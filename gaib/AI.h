#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

enum GROW { LEAF, ROOT, FLOWER, SPREAD, SPAWN, ATTACK,GROW_SIZE};
enum RATE {RLEAF,RROOT,RFLOWER,RSPREAD,RSPAWN,RATTACK,ULEAF,UROOT,UFLOWER,AGGRESSIVE,CENTER,BALANCE,RATE_SIZE};
const string growDisplay[GROW_SIZE+1] = {"LEAF","ROOT","FLOWER","SPREAD","SPAWN","ATTACK","GROW_SIZE"};
const string rateDisplay[RATE_SIZE+1] =
 {"RLEAF","RROOT","RFLOWER","RSPREAD","RSPAWN","RATTACK","ULEAF","UROOT","UFLOWER","AGGRESSIVE","CENTER","BALANCE","RATE_SIZE"};

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
  
  
  AI();
  void myGene(vector<float>& myRate);

  vector< vector< bool > > canSpawnHere;
  vector< vector< bool > > canSpreadHere;
  vector< vector< unsigned int  > > range;
  vector< vector< float > > center;
  
  vector<float> rate;
  vector<float> early;
  vector<float> late;
  unsigned int turnSwap;
  //the queue for actions
  priority_queue<space> que;
  
  bool canDo(unsigned int plant,GROW action);
  void resetDataStructures();
  void buildQueue();
  bool doActions();
  void getRating(space &  sp);
  
  void getFlowerUp(unsigned int index, unsigned int& root,unsigned int& leaf,unsigned int& flower);
  
  unsigned int combinedLevel(unsigned int index);

  int getWinValue ();
  unsigned int aiNum;
};

#endif
