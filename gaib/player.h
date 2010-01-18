#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
enum {NOOP,LEAF,ROOT,ACTION_COUNT};
using namespace std;
class Player
{
  private:
    int fitness;
    vector<int> scores;
  public:
    Player();
    //calls the command determined by scores
    void act();
    //For each action, determine how "good" that action is
    int leafScore();
    int rootScore();
    int noOpScore();
    int getFitness();
};

#endif
