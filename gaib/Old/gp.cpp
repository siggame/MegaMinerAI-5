#include "gp.h"


GP::GP(char* Host,unsigned int popSize)
{
  host=Host;
  pop.resize(popSize);
  mutant.resize(popSize);
  parent.resize(popSize/2);
  lost.resize(popSize/2);
  child.resize(popSize/4);
  for(unsigned int i=0;i<pop.size();i++)
  {
    pop[i].aiNum=i;
  }
}
void GP::initialize()
{
  
}

void GP::selfImprovePop()
{
  int results;
  //Thread Here
  for(unsigned int i=0;i<pop.size();i++)
  {
    mutant[i]=pop[i];
    //TODO put mutation in here
    if(!playGame(pop[i],mutant[i],host,results))
    {
      cerr<<"GAIB: playGame failed during mutation step"<<endl;
    }
    //if the original LOST
    if(results<0)
    {
      pop[i]=mutant[i];
    }  
  }  
}

void GP::competition()
{
  int results;
  //Thread here
  for(unsigned int i=0;i<pop.size()-1;i+=2)
  {
    //TODO May be a good idea to play 2 games, so each AI can be first player
    //if the game fails
    if(!playGame(pop[i],pop[i+1],host,results))
    {
      cerr<<"GAIB: playGame failed during first round of the tournament"<<endl;
    }
    //if player 1 won
    if(results>0)
    {
      //first round winners = parents
      parent[i/2]=i;//divide i to get the game number
      lost[i/2]=i+1;
    }
    else
    {
      parent[i/2]=i+1;
      lost[i/2]=i;
    }
  }
  cout<<"First round over!"<<endl;
  //Thread here
  for(unsigned int i=0;i<lost.size()-1;i+=2)
  {
    //if either game fails
    if(!playGame(pop[lost[i]],pop[lost[i+1]],host,results))
    {
      cerr<<"GAIB: playGame failed during second round of the tournament"<<endl;
    }
    if(results>0)
    {
      child[i/2]=lost[i+1];
    }
    else
    {
      child[i/2]=lost[i];
    }
  }
  cout<<"Competition complete!"<<endl;
  cout<<"Parents: ";
  for(unsigned int i=0;i<parent.size();i++)
  {
    cout<<parent[i]<< " ";
  }
  cout<<endl<<"Children: ";
  for(unsigned int i=0;i<child.size();i++)
  {
    cout<<child[i]<< " ";
  }
  cout<<endl;
}

void GP::recombination()
{

}
