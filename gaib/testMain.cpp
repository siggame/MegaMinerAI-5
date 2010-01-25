#include "player.h"
#include "gp.h"
#include <iostream>
#include "tree.h"
using namespace std;

int main()
{

  cout<<"Top of Main"<<endl;
  Player dummy;
  GP gp;
  gp.selfImprovePop();
  gp.competition();
  gp.recombination();
  dummy.act();
  
  cout<<"Bottom of Main"<<endl;  
}
