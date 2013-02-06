#include "AI.h"

int xoff[4] = { -1, 1,0,0 };
int yoff[4] = { 0, 0 , -1,1};

const char* AI::username()
{
  
  return "Shell AI";
}

const char* AI::password()
{
  return "password";
}

void AI::init()
{
  unsigned int seed=time(NULL);
  cout<<"SEED: "<<seed<<endl;
  srand(seed);

  canSpawnHere.resize(boardX()+2);
  canSpreadHere.resize(boardX()+2);
  for(unsigned int x=0;x<canSpawnHere.size();x++)
  {
    canSpawnHere[x].resize(boardY()+2);
    canSpreadHere[x].resize(boardY()+2);
    for(unsigned int y=0;y<canSpawnHere[x].size();y++)
    {
      canSpawnHere[x][y]=true;
      canSpreadHere[x][y]=true;
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

}
//TODO Test if you can build something and act on it in one turn
void AI::buildQueue()
{
  for(unsigned int i=0;i<plants.size();i++)
  {
    //cout<<"Working on plant: "<<i<<endl;
    //cout<<"HP: "<<plants[i].health()<<endl;
    //if its my plant and it can do something
    if(plants[i].ownerID() == playerID() && plants[i].canAct())
    {
      //Spam talk
      string message="This is plant[" + plants[i].objectID();
      message+="] owned by Player: "+plants[i].ownerID();
      message+=" on turn "+turnNumber();
      //char * temp = message.c_str();
      plants[i].talk((char*)(message.c_str()));
      if(i==0)
      {
        plants[i].talk((char*)("Did calling talk twice append or replace the usual string?"));
      }
      //if you don't have a leaf
      if(!plants[i].leaf())
      {
        if(canDo(i,LEAF))
        {
          //a place to try growing a leaf
          space sp(plants[i].x(), plants[i].y(),i,LEAF);
          sp.rating=evalTree(leafTree,sp);
          que.push(sp);
        }
        /*
        else
        {
          space sp(plants[i].x(), plants[i].y(),i,LEAF);
          cout<<"CANT DO: ";
          sp.display();
        }
        */
      }
      //if you want to generate light
      else
      {
        //cout<<"Pushing NOOP"<<endl;
        space sp(plants[i].x(), plants[i].y(),i,NOOP);
        sp.rating=evalTree(noopTree,sp);
        //que.push(sp);
      }
      //if it doesn't have a root
      if(!plants[i].root())
      {
        //I can do a root
        if(canDo(i,ROOT))
        {
          //a place to try growing a root
          space sp(plants[i].x(), plants[i].y(),i,ROOT);
          sp.rating=evalTree(rootTree,sp);
          que.push(sp);
        }
        /*
        else
        {
          space sp(plants[i].x(), plants[i].y(),i,ROOT);
          cout<<"CANT DO: ";
          sp.display();        
        }
        */
      }
      //for expansion
      else
      {
        if(canDo(i,SPREAD))
        {
          for(unsigned int r=0;r<4;r++)
          {
            space sp(plants[i].x()+xoff[r], plants[i].y()+yoff[r],i,SPREAD);
            if(canSpawnHere[sp.x+1][sp.y+1])
            {
              sp.rating=evalTree(rootTree,sp);
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
          sp.rating=evalTree(flowerTree,sp);
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
              sp.rating=evalTree(spawnTree,sp);
              que.push(sp);
            }
          }
        }
      }
    }
  }
 // //cout<<"Bot of Build QUE"<<endl;
}
unsigned int AI::combinedLevel(unsigned int index)
{
  //cout<<"Combined level"<<plants[index].leafLevel()+plants[index].rootLevel()+plants[index].flowerLevel()<<endl;
  return plants[index].leafLevel()+plants[index].rootLevel()+plants[index].flowerLevel();
}
bool AI::canDo(unsigned int index,GROW action)
{
  //TODO Replace with flexible versions
  switch (action)
  {
    case LEAF:
      //ensure you have enough light AND the plant will live 1 turn with the structure
      return myLight()>=1 && plants[index].health()>(1+plants[index].flower()*10 + 1);
    case ROOT:
      return myLight()>=2;
    case FLOWER:
      return myLight()>=5 && plants[index].health()>(1+plants[index].leaf()+10);
    case SPREAD:
      return myLight()>=1*combinedLevel(index);
    case SPAWN:
      return myLight()>=2*combinedLevel(index);
    case NOOP:
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
  }while( !plants[sp.acting].canAct() || !canDo(sp.acting,sp.action) || notActing[sp.acting]);
  cout<<plants[sp.acting].objectID()<<" ("<<plants[sp.acting].x()<<","<<plants[sp.acting].y()<<") ";sp.display();
  switch (sp.action)
  {
    case LEAF:
      plants[sp.acting].growLeaf();
      break;
    case ROOT:
      plants[sp.acting].growRoot();
      break;
    case FLOWER:
      getFlowerUp(sp.acting,r,l,f);
      plants[sp.acting].growFlower(r,l,f);
      break;
    case SPREAD:
      if(canSpreadHere[sp.x+1][sp.y+1])
      {
        plants[sp.acting].spread(sp.x,sp.y);
        if(!canSpawnHere[sp.x+1][sp.y+1])
        {
          cout<<"\n\n\tAttack!";
          sp.display();
          cout<<"\n\n"<<endl;
        }
        canSpreadHere[sp.x+1][sp.y+1]=false;
      }
      break;
    case SPAWN:
      if(canSpawnHere[sp.x+1][sp.y+1])
      {
        plants[sp.acting].spawn(sp.x,sp.y);
        canSpawnHere[sp.x+1][sp.y+1]=false;
      }
      break;            
    case NOOP:
      notActing[sp.acting]=true;
      break;
  }
  return que.empty();
}

void AI::resetDataStructures()
{
  //ignore the boundaries
  for(unsigned int x=1;x<canSpawnHere.size()-1;x++)
  {
    for(unsigned int y=1;y<canSpawnHere[x].size()-1;y++)
    {
      //return them all to true
      canSpawnHere[x][y]=true;
      canSpreadHere[x][y]=true;
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
  }
  notActing.resize(plants.size());
  for(unsigned int i=0;i<notActing.size();i++)
  {
    notActing[i]=false;
  }
}
bool AI::run()
{
  realLight=(playerID())?player1Light():player0Light();
  cout<<"Turn: "<<turnNumber()<<" Player: "<<playerID()<<" Light: "<<realLight<<endl;
  cout<<"Plants: "<<plants.size()<<endl;
  if(plants.size()<2)
  {
    return true;
  }
  //if the queue is empty
  if(que.empty())
  {
  //  cout<<"First time on this turn"<<endl;
    resetDataStructures();
    buildQueue();
  }
  //cout<<"Queue Size: "<<que.size()<<endl;
  //runs once
  return doActions();
  /*
  while(!que.empty())
  {
    que.pop();
  }
  return true;
  */
  //otherwise
  //return doActions();
  /*
  while(!doActions()){};
  return true;
  */
}
void AI::getFlowerUp(unsigned int index,unsigned int& root,unsigned int& leaf,unsigned int& flower)
{
  flower=root=leaf=0;
  //leaf=plants[index].flowerLevel();
  leaf=plants[index].flowerLevel()/2;
  flower=plants[index].flowerLevel() - plants[index].flowerLevel()/2;
}
float AI::evalTree(NDVector<node> & tree,space & sp)
{
  if(sp.action == SPAWN)
  return 15;
  //TODO change to actually use the tree
  return rand()%11-5;

  unsigned int i;
  float partial=0;
  if(tree.value.op=='#')
  {
    return tree.value.number;
  }
  else
  {
    //operator
    if(tree.value.op == '+')
    {
      for(i=0;i<tree.size();i++)
      {
        partial+=evalTree(tree[i],sp);
      }
    }
    else if(tree.value.op == '*')
    {
      for(i=0;i<tree.size();i++)
      {
        partial*=evalTree(tree[i],sp);
      }
    }
//    else if(tree
  }
  return partial;
}

