#ifndef GP_H
#define GP_H
#include "player.h"
#include <vector>
using namespace std;
class GP
{
  private:
    vector<Player> pop;
    //Stores the indexs of where the parents are
    vector<unsigned int> parent;
    //Stores the indexs of where the children will be
    vector<unsigned int> child;
  public:
    GP();
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

