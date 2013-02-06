#include "gp.h"

void permutation(vector< unsigned int >& list)
{
  int choice;
  int temp;
  for(unsigned int i=0;i<list.size();i++)
  {
    list[i]=i;
  }
  for(unsigned int i=list.size()-1;i>0;i--)
  {
    //chose a random number between 0 and i
    choice=rand()%i;
    //does a swap
    temp=list[choice];
    list[choice]=list[i];
    list[i]=temp;
  }
}
GP::GP(char* Host,unsigned int popSize)
{
  host=Host;
  pop.resize(popSize);
  mutant.resize(popSize);
  parent.resize(popSize/2);
  lost.resize(popSize/2);
  child.resize(popSize/4);
  top.resize(popSize/4);
  perm.resize(popSize);
  lilp.resize(popSize/2);
  unsigned int seed=time(NULL);
  srand(seed);
  redWin=bluWin=0;
  cout<<"SEED: "<<seed<<endl;
  for(unsigned int i=0;i<pop.size();i++)
  {
    pop[i].aiNum=i;
    for(unsigned int j=0;j<pop[i].rate.size();j++)
    {
      pop[i].early[j]=rand()%6;
      pop[i].late[j]=rand()%6;
    }
    pop[i].turnSwap=rand()%250+50;
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
    do
    {
      results=rand()%mutant[i].early.size();
      mutant[i].early[results]=rand()%6;
    }
    //ensure that its changed
    while(mutant[i].early[results] == pop[i].early[results]);
    do
    {
      results=rand()%mutant[i].late.size();
      mutant[i].late[results]=rand()%6;
    }
    //ensure that its changed
    while(mutant[i].late[results] == pop[i].late[results]);

    if(!playGame(pop[i],mutant[i],host,results))
    {
      cerr<<"GAIB: playGame failed during mutation step"<<endl;
    }
    mutant[i].turnSwap=rand()%6+247;
    //if the original LOST
    if(results<0)
    {
      cout<<"TOPTEIR Someone was selfImproved"<<endl;
      pop[i]=mutant[i];
    }
  } 
}

void GP::competition()
{
  permutation(perm);
  permutation(lilp);
  int results;
  //Thread here
  for(unsigned int i=0;i<pop.size()-1;i+=2)
  {
    //TODO May be a good idea to play 2 games, so each AI can be first player
    //if the game fails
    //cout<<"Above Play Game"<<i<<" vs "<<i+1<<endl;
    if(!playGame(pop[perm[i]],pop[perm[i+1]],host,results))
    {
      cerr<<"GAIB: playGame failed during first round of the tournament"<<endl;
    }
    //if player 1 won
    if(results>0)
    {
      redWin++;
      //first round winners = parents
      parent[i/2]=perm[i];//divide i to get the game number
      lost[i/2]=perm[i+1];
    }
    else
    {
      bluWin++;
      parent[i/2]=perm[i+1];
      lost[i/2]=perm[i];
    }
  }
  //cout<<"First round over!"<<endl;
  //Thread here
  for(unsigned int i=0;i<lost.size()-1;i+=2)
  {
    //if either game fails
    if(!playGame(pop[lost[lilp[i]]],pop[lost[lilp[i+1]]],host,results))
    {
      cerr<<"GAIB: playGame failed during second round of the tournament"<<endl;
    }
    if(results>0)
    {
      redWin++;
      child[i/2]=lost[lilp[i+1]];
    }
    else
    {
      bluWin++;
      child[i/2]=lost[lilp[i]];
    }
  }
  cout<<"TOP REDWIN: "<<redWin<<" BLUWIN: "<<bluWin<<endl;
  /*
  cout<<"Competition complete!"<<endl;
  cout<<"Parents: "<<endl;
  for(unsigned int i=0;i<parent.size();i++)
  {
    cout<<parent[i]<< ":";
    for(unsigned int j=0;j<pop[parent[i]].rate.size();j++)
    {
      cout<<pop[parent[i]].rate[j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl<<"Children: "<<endl;
  for(unsigned int i=0;i<child.size();i++)
  {
    cout<<child[i]<< ":";
    for(unsigned int j=0;j<pop[child[i]].rate.size();j++)
    {
      cout<<pop[child[i]].rate[j]<<" ";
    }
    cout<<endl;
  }
  */
}

void GP::recombination()
{
  //for every child
  for(unsigned int i=0;i<parent.size();i+=2)
  {
    unsigned int c=child[i/2];
    for(unsigned int r=0;r<pop[c].rate.size();r++)
    {
      if(rand()%2)
      {
        pop[c].early[r]=pop[parent[i]].early[r];
      }
      else
      {
        pop[c].early[r]=pop[parent[(i+1)%parent.size()]].early[r];
      }
      if(rand()%2)
      {
        pop[c].late[r]=pop[parent[i]].late[r];
      }
      else
      {
        pop[c].late[r]=pop[parent[(i+1)%parent.size()]].late[r];
      }
    }
    pop[c].turnSwap=(pop[parent[i]].turnSwap+pop[parent[(i+1)%parent.size()]].turnSwap)/2;
  }
}
void GP::popDump()
{
  cout<<"TOPPOP>>:{";
  for(unsigned int i=0;i<pop.size();i++)
  {
    cout<<"{";
    for(unsigned int j=0;j<pop[j].early.size();j++)
    {
      cout<<pop[i].early[j]<<",";
    }
    for(unsigned int j=0;j<pop[j].late.size();j++)
    {
      cout<<pop[i].late[j]<<",";
    }
    cout<<"},";
  }
  cout<<"}"<<endl;
}



void GP::topTeir()
{
  int results;
  //Thread here
  for(unsigned int i=0;i<parent.size()-1;i+=2)
  {
    //if either game fails
    if(!playGame(pop[parent[i]],pop[parent[i+1]],host,results))
    {
      cerr<<"GAIB: playGame failed during second round of the tournament"<<endl;
    }
    if(results<0)
    {
      //cout<<"FLIP THE LESS THAN"<<endl;
      top[i/2]=parent[i+1];
    }
    else
    {
      top[i/2]=parent[i];
    }
  }
  cout<<"TOPTEIR complete!"<<endl;
  for(unsigned int i=0;i<top.size();i++)
  {
    cout<<"TOPTEIR"<<top[i]<< ":";
    for(unsigned int j=0;j<pop[top[i]].rate.size();j++)
    {
      cout<<pop[top[i]].early[j]<<" ";
    }
    cout<<endl<<"after "<<pop[top[i]].turnSwap<< ":";
    for(unsigned int j=0;j<pop[top[i]].rate.size();j++)
    {
      cout<<pop[top[i]].late[j]<<" ";
    }
    cout<<endl;

  }
  
}
/*
void GP::best()
{
  permutation(perm);
  int results;
  vector<unsigned int> big(pop.size()/2);
  vector<unsigned int> small(pop.size()/4);
  for(unsigned int i=0;i<pop.size()-1;i+=2)
  {
    //TODO May be a good idea to play 2 games, so each AI can be first player
    //if the game fails
    //cout<<"Above Play Game"<<i<<" vs "<<i+1<<endl;
    if(!playGame(pop[perm[i]],pop[perm[i+1]],host,results))
    {
      cerr<<"GAIB: playGame failed during first round of the tournament"<<endl;
    }
    //if player 1 won
    if(results>0)
    {
      //first round winners
      big[i/2]=perm[i];//divide i to get the game number
    }
    else
    {
      big[i/2]=perm[i+1];
    }
  }
  while(big.size()>1)
  {
    for(unsigned int i=0;i<big.size()-1;i+=2)
    {
      //if either game fails
      if(!playGame(pop[big[i]],pop[big[i+1]],host,results))
      {
        cerr<<"GAIB: playGame failed during second round of the tournament"<<endl;
      }
      if(results>0)
      {
        small[i/2]=parent[i];
      }
      else
      {
        small[i/2]=parent[i+1];
      }
    }
    big.resize(small.size());
    for(unsigned int i=0;i<big.size();i++)
    {
      big[i]=small[i];
    }
    small.resize(big.size()/2);
  }
    cout<<"TOPOFALL: ";
    for(unsigned int j=0;j<pop[big[0]].rate.size();j++)
    {
      cout<<pop[big[0]].early[j]<<" ";
    }
    cout<<endl<<"TOPafter "<<pop[big[0]].turnSwap<< ":";
    for(unsigned int j=0;j<pop[big[0]].rate.size();j++)
    {
      cout<<pop[big[0]].late[j]<<" ";
    }
    cout<<endl;
}
*/

