#ifndef TREE_H
#define TREE_H
#include <iostream>
using namespace std;
enum NodeType{Term,Add,Sub,Mult,Div,LT,EQ};
class tree
{
  private:
    //4 is the maximum for any function
    tree* child[4];
    
  public:
    tree();
    ~tree();
    int result();
};



#endif
