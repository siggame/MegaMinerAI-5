#include "AI.h"

const char* AI::username()
{
  return "GAIB";
}

const char* AI::password()
{
  return "goldmancheats";
}
bool AI::canBuildLeaf(unsigned int i)
{
  return (plants[i].leaves()*plants[i].leaves()<=plants[i].water()) &&
         (plants[i].leaves()<=plants[i].light());
}
bool AI::canBuildRoot(unsigned int i)
{
  return (plants[i].roots()*plants[i].roots()<=plants[i].light()) &&
         (plants[i].roots()<=plants[i].water());
}

void AI::init()
{
 // cout<<"PLAYERID: "<<playerID()<<endl;
}

void makeTree(ifstream & file)
{
  char symbol;
  float number;
  file>>symbol;//reads initial paren
  file>>symbol;
  if(symbol==')')return;
  if(symbol=='#')
  {
    file>>number;
    tree.value.value=number;
    
  }
  else
  {
    tree.op=symbol;
    makeTree(tree.level,file);
  }
}

makeTree(NDVector<node> & working,ifstream& file)
{
  
}

bool AI::run()
{
  if(turnNumber()>97)
  {
  for(unsigned int i=0;i<plants.size();i++)
  {
    //if its my plant
    if(plants[i].ownerID()==playerID())
    {

    cout<<"Player: "<<playerID()<<endl;	
                    cout<<"Light: "<<plants[i].light()<<endl;
      cout<<"Water: "<<plants[i].water()<<endl;
      cout<<"Leaves: "<<plants[i].leaves()<<endl;
      cout<<"Roots: "<<plants[i].roots()<<endl;
      cout<<"PlayerZeroScore: "<<player0Score()<<endl;
      cout<<"PlayerOneScore: "<<player1Score()<<endl;
      cout<<"MyID: "<<aiNum<<endl;
    }}  
  }
  //if(turnNumber()>2)return true;
  /*
  if(turnNumber()<2)
    rootcount=1;
  cout<<"Begining turn: "<<turnNumber()<<endl;
  */
  for(unsigned int i=0;i<plants.size();i++)
  {
    //if its my plant
    if(plants[i].ownerID()==playerID())
    {
 /*
      if(aiNum%4)
      {
                    cout<<"Light: "<<plants[i].light()<<endl;
      cout<<"Water: "<<plants[i].water()<<endl;
      cout<<"Leaves: "<<plants[i].leaves()<<endl;
      cout<<"Roots: "<<plants[i].roots()<<endl;
      }
   
      if(rootcount!=plants[i].roots())
      {
        rootcount=plants[i].roots();
        cout<<"Build Successful, resources now: "<<endl;
                cout<<"Light: "<<plants[i].light()<<endl;
      cout<<"Water: "<<plants[i].water()<<endl;
      cout<<"Leaves: "<<plants[i].leaves()<<endl;
      cout<<"Roots: "<<plants[i].roots()<<endl;
      

      }
      */
      if(canBuildLeaf(i))
      {
        if(aiNum%3==0)
        {
          plants[i].growLeaf();
          return false;
        }
      }
      if(canBuildRoot(i))
      {
        if(aiNum%4==0)
        {
 /*         cout<<"Building a root"<<endl;
                cout<<"Light: "<<plants[i].light()<<endl;
      cout<<"Water: "<<plants[i].water()<<endl;
      cout<<"Leaves: "<<plants[i].leaves()<<endl;
      cout<<"Roots: "<<plants[i].roots()<<endl;
   */
          plants[i].growRoot();
          
        }
      }
    }
  }
  return true;
}
