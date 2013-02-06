#ifndef GP_H
#define GP_H
#include "AI.h"
#include "playGame.h"
#include <vector>

using namespace std;

struct GameInfo
{
  AI fp,sp;
  int results;
  GameInfo(){}
  GameInfo(AI& FP,AI& SP):fp(FP),sp(SP){}
  void set(AI& FP,AI& SP){fp=FP;sp=SP;};
};
//used to control who is outputing
//pthread_mutex_t screen;

class GP
{
  private:
    vector<AI> pop,mutant;
    //Stores the indexs of where the parents are
    vector<unsigned int> parent;
    //Stores the indexs of where the children will be
    vector<unsigned int> child;
    //location of the server to compete on
    char* host;
    //list of where the first round losers are
    vector<unsigned int> lost;
    
    
    //thread crap
    vector<pthread_t> pid;
    vector<GameInfo> info;
    
  public:
    //GP();
    GP(char* Host,unsigned int popSize);
    //Pre:  None
    //Post: Sets up Pop, auto run with constructor
    void initialize();
    //Pre:  Pop is initialized
    //Post: Will make mutated copies of each player and have those
    //      new versions try to replace their predicesors.
    void selfImprovePop();
    
    //Pre:  Pop is initialized
    //Post: Runs reverese single elimiation tournement to determine survival/parents
    //      Winners in first round = parents, losers play in next round
    //      Losers of second round get replaced by offspring
    void competition();
    
    //Pre:  Pop is initialized
    //Post: Recombines parents from parent vector into children
    void recombination();
    

};


#endif

