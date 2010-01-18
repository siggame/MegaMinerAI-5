#include "player.h"
#include "gp.h"
#include <iostream>
using namespace std;

int main()
{
  cout<<"Top of Main"<<endl;
  Player dummy;
  GP gp;
  gp.selfImprovePop();
  gp.competition();
  gp.recombination();
  
  cout<<"Bottom of Main"<<endl;  
}
