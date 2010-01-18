#include "player.h"

Player::Player()
{
  fitness=0;
  scores.resize(ACTION_COUNT);
}

void Player::act()
{
  //TODO Remove evaluation of unavailable actions
  //evaluate each action
  scores[NOOP]=noOpScore();
  scores[LEAF]=leafScore();
  scores[ROOT]=rootScore();
  unsigned int choice=0;
  for(unsigned int i=1;i<ACTION_COUNT;i++)
  {
    if(scores[choice]<scores[i])
    {
      choice=i;
    }
  }
  switch (choice)
  {
    case LEAF:
      //TODO Grow Leaf
      break;
    case ROOT:
      //TODO Grow Root
      break;
    case NOOP:
    default:
      break;
  }
}

int Player::getFitness()
{
  return fitness;
}

int Player::noOpScore()
{
  return 1;
}

int Player::leafScore()
{
  return 1;
}
int Player::rootScore()
{
  return 1;
}

