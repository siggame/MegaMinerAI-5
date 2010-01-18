#ifndef PLAYER_H
#define PLAYER_H

class Player
{
  private:
    int fitness;
  public:
    Player();
    int makeChoice();
    int getFitness();
};

#endif
