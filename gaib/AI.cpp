#include "AI.h"

int xoff[4] = { -1, 1,0,0 };
int yoff[4] = { 0, 0 , -1,1};

const char* AI::username()
{
  
  return "GAIB";
}

const char* AI::password()
{
  return "hardtobeat";
}

AI::AI()
{
  //TODO Fill in rating with random values
  rate.resize(RATE_SIZE);
  early.resize(RATE_SIZE);
  late.resize(RATE_SIZE);
}
void AI::myGene(vector<float>& myRate)
{
  rate.resize(myRate.size());
  {
    for(unsigned int i=0;i<rate.size();i++)
    {
      rate[i]=myRate[i];
    }
  }
}

void AI::init()
{
  sendTag("GAIB");
  sendTag("Version Stupid");
  for(unsigned int i=0;i<rate.size();i++)
  {
    rate[i]=early[i];
  }
  //cout<<"Player: "<<playerID()<<" in init"<<endl;
  canSpawnHere.resize(boardX()+2);
  canSpreadHere.resize(boardX()+2);
  range.resize(boardX()+2);
  center.resize(boardX()+2);
  for(unsigned int x=0;x<canSpawnHere.size();x++)
  {
    canSpawnHere[x].resize(boardY()+2);
    canSpreadHere[x].resize(boardY()+2);
    range[x].resize(boardY()+2);
    center[x].resize(boardY()+2);
    for(unsigned int y=0;y<canSpawnHere[x].size();y++)
    {
      canSpawnHere[x][y]=true;
      canSpreadHere[x][y]=true;
      range[x][y]=10000;
    }
  }
  for(unsigned int x=0;x<canSpawnHere.size();x++)
  {
    canSpawnHere[x][0]=false;
    canSpawnHere[x][canSpawnHere[x].size()-1]=false;
    canSpreadHere[x][0]=false;
    canSpreadHere[x][canSpawnHere[x].size()-1]=false;

  }
  for(unsigned int y=0;y<canSpawnHere[0].size();y++)
  {
    canSpawnHere[0][y]=false;
    canSpawnHere[canSpawnHere.size()-1][y]=false;
    canSpreadHere[0][y]=false;
    canSpreadHere[canSpawnHere.size()-1][y]=false;

  }
  for(int x=0;x<(int)center.size();x++)
  {
    for(int y=0;y<(int)center[x].size();y++)
    {
      center[x][y]=abs(1+9.5-x)+abs(1+9.5-y);
    }
  }
  //cout<<"Player: "<<playerID()<<" done init"<<endl;
}

void AI::buildQueue()
{
  char temp [255];
  string message="E";
  for(unsigned int i=0;i<RATE_SIZE;i++)
  {
    sprintf (temp, "%g ",(early[i]));
    message+=temp;
  }
  message+="\nN";
  for(unsigned int i=0;i<RATE_SIZE;i++)
  {
    sprintf (temp, "%i ",(int)(rate[i]));
    message+=temp;
  }
  message+="\nL";
  for(unsigned int i=0;i<RATE_SIZE;i++)
  {
    sprintf (temp, "%g ",(late[i]));
    message+=temp;
  }
  unsigned int highestLevel=0;
  for(unsigned int i=0;i<plants.size();i++)
  {
    //if its my plant
    if(plants[i].ownerID() == playerID() && turnNumber()<500)
    {
      if(combinedLevel(highestLevel)<combinedLevel(i))
      {
        highestLevel=i;
      }

      plants[i].talk(message.c_str());
    }
    if(plants[i].ownerID() == playerID() && plants[i].canAct())
    {
      //if you don't have a leaf
      if(!plants[i].leaf())
      {
        if(canDo(i,LEAF))
        {
          //a place to try growing a leaf
          space sp(plants[i].x(), plants[i].y(),i,LEAF);
          getRating(sp);
          que.push(sp);
        }
      }
      //if it doesn't have a root
      if(!plants[i].root())
      {
        //I can do a root
        if(canDo(i,ROOT))
        {
          //a place to try growing a root
          space sp(plants[i].x(), plants[i].y(),i,ROOT);
          getRating(sp);
          que.push(sp);
        }
      }
      //for expansion
      else
      {
        if(canDo(i,SPREAD))
        {
          for(unsigned int r=0;r<4;r++)
          {
            space sp(plants[i].x()+xoff[r], plants[i].y()+yoff[r],i,SPREAD);
            //if you can spread there, but not spawn there
            if(canSpreadHere[sp.x+1][sp.y+1] && !canSpawnHere[sp.x+1][sp.y+1])
            {
              sp.action=ATTACK;
            }
            if(canSpreadHere[sp.x+1][sp.y+1])
            {
              getRating(sp);
              que.push(sp);
            }
          }
        }
      }
      //if it doesn't have a flower and can make one
      if(!plants[i].flower())
      {
        if(canDo(i,FLOWER))
        {
          //a place to try growing a flower
          space sp(plants[i].x(), plants[i].y(),i,FLOWER);
          getRating(sp);
          que.push(sp);
        }
      }
      //if you have a flower and can spawn
      else
      {
        if(canDo(i,SPAWN))
        {
          for(unsigned int r=0;r<4;r++)
          {
            space sp(plants[i].x()+xoff[r], plants[i].y()+yoff[r],i,SPAWN);
            if(canSpawnHere[sp.x+1][sp.y+1])
            {
              getRating(sp);
              que.push(sp);
            }
          }
        }
      }
    }
  }
  sprintf(temp,"\nHighest Level Plant=%i",combinedLevel(highestLevel));
  for(unsigned int i=0;i<plants.size();i++)
  {
    if(plants[i].ownerID()==playerID())
      plants[i].talk(temp);
  }
}
unsigned int AI::combinedLevel(unsigned int index)
{
  //cout<<"Combined level"<<plants[index].leafLevel()+plants[index].rootLevel()+plants[index].flowerLevel()<<endl;
  return plants[index].leafLevel()+plants[index].rootLevel()+plants[index].flowerLevel();
}
bool AI::canDo(unsigned int index,GROW action)
{
  switch (action)
  {
    case LEAF:
      //ensure you have enough light AND the plant will live 1 turn with the structure
      return myLight()>=plants[index].leafCost() && plants[index].health()>(1+plants[index].flower()*10 + 1);
    case ROOT:
      return myLight()>=plants[index].rootCost();
    case FLOWER:
      return (myLight()>= (plants[index].flowerCost() + plants[index].spawnCost())) && (plants[index].health()>(1+plants[index].leaf()+10));
    case SPREAD:
    case ATTACK:
      return myLight()>=plants[index].spreadCost();
    case SPAWN:
      return myLight()>=plants[index].spawnCost();
    default:
      return true;
  }
}

bool AI::doActions()
{
  unsigned int r,l,f;
  space sp;
  do
  {
    if(que.empty())return true;
    //get the next best
    sp = que.top();
    //pop it off
    que.pop();
  }while( !plants[sp.acting].canAct() || !canDo(sp.acting,sp.action));
  //cout<<plants[sp.acting].objectID()<<" ("<<plants[sp.acting].leafLevel()<<","<<plants[sp.acting].rootLevel()<<","<<plants[sp.acting].flowerLevel()<<") "<<" light: "<<myLight();sp.display();
  switch (sp.action)
  {
    case LEAF:
      if(!plants[sp.acting].growLeaf()){cout<<"TOP Returned False in Leaf:"<<endl;}
      //plants[sp.acting].talk("I grew a leaf");
      break;
    case ROOT:
      if(!plants[sp.acting].growRoot()){cout<<"TOP Returned False in Root:"<<endl;}
      //plants[sp.acting].talk("I grew a root");
      break;
    case FLOWER:
      getFlowerUp(sp.acting,r,l,f);
      if(!plants[sp.acting].growFlower(r,l,f)){cout<<"TOP Returned False in Flower:"<<endl;}
      //plants[sp.acting].talk("I grew a flower");
      break;
    case SPREAD:
    case ATTACK:
      if(canSpreadHere[sp.x+1][sp.y+1])
      {
        if(!plants[sp.acting].spread(sp.x,sp.y)){cout<<"TOP Returned False in Spread or Attack:"<<endl;}
        if(sp.action==SPREAD)
        {
          canSpreadHere[sp.x+1][sp.y+1]=false;
          //plants[sp.acting].talk("I spread");
        }
        else
        {
          //plants[sp.acting].talk("I attacked");
        }
        canSpawnHere[sp.x+1][sp.y+1]=false;
      }
      break;
    case SPAWN:
      if(canSpawnHere[sp.x+1][sp.y+1])
      {
        if(!plants[sp.acting].spawn(sp.x,sp.y)){cout<<"TOP Returned False in Spawn:"<<endl;}
        //plants[sp.acting].talk("I spawned");
        canSpawnHere[sp.x+1][sp.y+1]=false;
        canSpreadHere[sp.x+1][sp.y+1]=false;
      }
      break;            
    default:
      break;
  }
  return que.empty();
}

void AI::resetDataStructures()
{
  int temp;
  //ignore the boundaries
  for(unsigned int x=1;x<canSpawnHere.size()-1;x++)
  {
    for(unsigned int y=1;y<canSpawnHere[x].size()-1;y++)
    {
      //return them all to true
      canSpawnHere[x][y]=true;
      canSpreadHere[x][y]=true;
      range[x][y]=10000;
    }
  }
  //for every plant
  for(unsigned int i=0;i<plants.size();i++)
  {
    //you can't build here
    canSpawnHere[plants[i].x()+1][plants[i].y()+1]=false;
    //if its my plant
    if(plants[i].ownerID() == playerID())
    {
      canSpreadHere[plants[i].x()+1][plants[i].y()+1] = false;
    }
    //if its not my plant
    else
    {
      for(int x=0;x<(int)range.size();x++)
      {
        for(int y=0;y<(int)range[x].size();y++)
        {
          temp=abs(plants[i].x()-x)+abs(plants[i].y()-y);
          if(temp<range[x][y])
          {
            range[x][y]=temp;
          }
        }
      }
    }
  }
}
bool AI::run()
{
  //hack to force init
  if(turnNumber() <2)init();

  for(unsigned int i=0;i<rate.size();i++)
  {
    rate[i]=(((500-turnNumber())*early[i])+(turnNumber()*late[i]))/500;
  }
  //cout<<"Turn: "<<turnNumber()<<" Player: "<<playerID()<<" Light: "<<myLight()<<endl;
  
  //if the queue is empty
  if(que.empty())
  {
  //  cout<<"First time on this turn"<<endl;
    resetDataStructures();
    buildQueue();
  }
  
  while(!doActions()){};
 // if(turnNumber()==499)cout<<"Ending Game: "<<getGameNumber()<<endl;
  return true;
}
void AI::getFlowerUp(unsigned int index,unsigned int& root,unsigned int& leaf,unsigned int& flower)
{
  flower=root=leaf=0;
  for(unsigned int i=0;i<plants[index].flowerLevel();i++)
  {
    //if flower is the lowest
    if((plants[index].flowerLevel()+flower)/(rate[UFLOWER]+1)<(plants[index].rootLevel()+root)/(rate[UROOT]+1))
    {
      flower++;
    }
    //if root is less than leaf
    else if((plants[index].rootLevel()+root)/(rate[UROOT]+1)<(plants[index].leafLevel()+leaf)/(rate[ULEAF]+1))
    {
      root++;
    }
    else
    {
      leaf++;
    }
  }
}
void AI::getRating(space & sp)
{
  //the intial rating ased on the action
  sp.rating=rate[sp.action]*1000;
  
  float agr=0,cent=0;
  //prioritize directionally
  if(rate[AGGRESSIVE]<3)
  {
    agr+=range[sp.x+1][sp.y+1];
  }
  else
  {
    agr-=range[sp.x+1][sp.y+1];
  }
  if(rate[CENTER]<3)
  {
    cent+=center[sp.x+1][sp.y+1];
  }
  else
  {
    cent-=center[sp.x+1][sp.y+1];
  }
  sp.rating+= ((agr*(5-rate[BALANCE]))/5.0+(cent*rate[BALANCE])/5.0)*10;
  //prioritize healthier plants for leaf an flower
  if(sp.action==LEAF || sp.action==FLOWER)
  {
    //add its turns left alive
    sp.rating+=plants[sp.acting].health()/(1+plants[sp.acting].leaf()*1 + plants[sp.acting].flower()*10);
  }
  //TODO This may need to be a tunable param
  sp.rating+=combinedLevel(sp.acting);
  
  //if you want a flower and are blocked in
  if(sp.action==FLOWER)
  {
    bool blocked = true;
    for(int r=0;r<4 && blocked;r++)
    {
      blocked= !canSpawnHere[plants[sp.acting].x()+1+xoff[r]][plants[sp.acting].y()+1+yoff[r]];
    }
    if(blocked)
    {
      //reduce your rating by half
      sp.rating-= abs(sp.rating/2);
    }
  }
  
}
//ASSUMES YOU ARE PLAYER ZERO
int AI::getWinValue ()
{
  if(player0Score() ==0 || player1Score()==0)
  {
    cout<<"TOP Someone died"<<endl;
  }
  return player0Score()-player1Score();
}

