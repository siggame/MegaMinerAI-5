#include "parser.h"
#include "structures.h"

#include <vector>
#include <iostream>
#include <limits>

using namespace std;

int main(int argc, char** argv)
{
  Game g;
  parseFile(g, "test.gamelog");
  
  for(vector<GameState>::iterator i = g.states.begin(); i != g.states.end(); i++)
  {
    cout << *i;
    cout << "----------------------------------" << endl;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  return 0;
}
