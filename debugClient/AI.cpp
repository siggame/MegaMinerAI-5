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
  srand(time(NULL));
  //resize the grid to be correct
  canBuildHere.resize(boardX()+2,vector<bool> (boardY()+2, true));
  //initialize the x boarders
  for(unsigned int i=0;i<canBuildHere.size();i++)
  {
    canBuildHere[i][0]=false;
    canBuildHere[i][canBuildHere[i].size()-1]=false;
  }
  //initialize the y boarders
  for(unsigned int j=0;j<canBuildHere[0].size();j++)
  {
    canBuildHere[0][j]=false;
    canBuildHere[canBuildHere.size()-1][j]=false;
  }
}

bool AI::run()
{
  //if the queue is empty
  if(que.empty())
  {
    cout<<"Turn: "<<turnNumber()<<" Plants: "<<plants.size()<<endl;
    setCanBuildHere();
    //initialize this turns info
    setCanBuildHere();
    buildQueue();
  }
  else
  {
    cout<<"Turn: "<<turnNumber()<<" Repeat"<<endl;
  }
while(!doActions());
  //do actions
  return doActions();
}
float AI::evalSpace(space sp)
{
  return rand();
}
bool AI::canDo(GROW action)
{
  //TODO Replace with flexible versions
  switch (action)
  {
    case LEAF:
      return myLight()>=2;
    case ROOT:
      return myLight()>=10;
    case FLOWER:
      return myLight()>=20;
    case SEED:
      return myLight()>=2;
    //if you don't know, give it a shot!
    default:
      return true;
  }
}
void AI::setCanBuildHere()
{
  //ignore the boundaries
  for(unsigned int x=1;x<canBuildHere.size()-1;x++)
  {
    for(unsigned int y=1;y<canBuildHere[x].size()-1;y++)
    {
      //return them all to true
      canBuildHere[x][y]=true;
    }
  }
  //for every plant
  for(unsigned int i=0;i<plants.size();i++)
  {
    //you can't build here
    canBuildHere[plants[i].x()][plants[i].y()]=false; //TODO Do something special IF we add spread as attack/defend
  }
}
void AI::buildQueue()
{
  //for every plant
  for(unsigned int i=0;i<plants.size();i++)
  {
    //if its my plant
    if(plants[i].ownerID() == playerID())
    {
      //if it can act
      if(plants[i].canAct())
      {
        //if you don't have a leaf
        if(!plants[i].leaf() && canDo(LEAF))
        {
          //a place to try growing a leaf
          space sp(plants[i].x(), plants[i].y(),i,LEAF);
          sp.rating=evalSpace(sp);
          que.push(sp);
        }
        //if you have the resources for a root
        if(canDo(ROOT))
        {
          //if you don't have one
          if(!plants[i].root())
          {
            //a place to try growing a root
            space sp(plants[i].x(), plants[i].y(),i,ROOT);
            sp.rating=evalSpace(sp);
            que.push(sp);
          }
          //to call a spread
          else
          {
            //for the 4 cardinal directions
            for(unsigned int r=0;r<4;r++)
            {
              space sp(plants[i].x()+xoff[r], plants[i].y()+yoff[r],i,ROOT);
              //if you can validly build here
              if(canBuildHere[sp.x+1][sp.y+1])
              {
                sp.rating=evalSpace(sp);
                que.push(sp);
              }
            }
          }
        }
        //if you can build a flower
        if(!plants[i].flower() && canDo(FLOWER))
        {
          //a place to try growing a flower
          space sp(plants[i].x(), plants[i].y(),i,FLOWER);
          sp.rating=evalSpace(sp);
          que.push(sp);
        }
        
        //if you have a flower and can make a seed
        if(plants[i].flower() && canDo(SEED))
        {
          for(unsigned int r=0;r<4;r++)
          {
            space sp(plants[i].x()+xoff[r], plants[i].y()+yoff[r],i,SEED);
            //if you can send a seed there
            if(canBuildHere[sp.x+1][sp.y+1])
            {
              sp.rating=evalSpace(sp);
              que.push(sp);
            }
          }
        }
      }
    }
  }
}


bool AI::doActions()
{
  space sp;
  do
  {
    //if at any time you have nothing to do, exit
    if(que.empty())return true;
    //get the next best
    sp = que.top();
    //pop it off
    que.pop();
    //while that action isn't valid
  }while( (!plants[sp.acting].canAct() || !canDo(sp.action)));
  cout<<"DOING: "<<growToString[sp.action]<<endl;
  if(sp.action==LEAF)
  {
    plants[sp.acting].growLeaf();
  }
  else if(sp.action==FLOWER)
  {
    //TODO Currently you can only build one type of flower
    plants[sp.acting].growFlower(0,1,0);
  }
  else if(sp.action==ROOT)
  {
    //if its Not a spread
    if(sp.x ==plants[sp.acting].x()  && sp.y ==plants[sp.acting].y())
    {
      plants[sp.acting].growRoot();
    }
    else
    {
      plants[sp.acting].spread(sp.x,sp.y);
      canBuildHere[sp.x][sp.y]=false;
    }
  }
  else if(sp.action==SEED)
  {
    plants[sp.acting].spawn(sp.x,sp.y);
    canBuildHere[sp.x][sp.y]=false;
  }
  //if no action should be performed
  else
  {
    //clean the queue
    while(!que.empty())
    {
      que.pop();
    }
  }
  //if there is still stuff to do, return false
  return que.empty();
}



