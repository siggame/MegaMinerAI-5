#include <vector>
#include <fstream>

struct node
{
  char op;
  float number;

};

using namespace std;
template <class T>
struct NDVector
{
  T value;
  vector<NDVector> level;
  
  unsigned int size(){return level.size();};
  void resize(unsigned int size){level.resize(size);};
  NDVector& operator[](int i){return level[i];};
};



//helper function
template <class T>
void growVector(NDVector<T> & tree,unsigned int depth,unsigned int width)
{
  if(depth==0 || width==0)
  {
    tree.value.op='#';
    tree.value.number=0;
    return;
  }
  tree.value.op='0'+depth;
  tree.resize(width);
  for(unsigned int i=0;i<tree.size();i++)
  {
    growVector(tree[i],depth-1,width);
  }
}
template <class T>
void PreOrder(NDVector<T> & tree,ofstream& out)
{
  out<<"("<<tree.value.op;
  if(tree.value.op=='#') out<<tree.value.number;
  for(unsigned int i=0;i<tree.size();i++)
  {
    PreOrder(tree[i],out);
  }
  out<<")";

}
template <class T>
void BuildTree(NDVector<T>& tree,ifstream& input)
{
  char in;
  input>>tree.value.op;
  //handles the very beginning
  if(tree.value.op == '(')
  {
    input>>tree.value.op;
  }
  if(tree.value.op == '#') 
  {
    input>>tree.value.number;
    //gets the trailing )
    input>>in;
  }
  else
  {
    input>>in;
    //while my list hasn't ended
    while(in !=')')
    {
       tree.resize(tree.size()+1);
       BuildTree(tree[tree.size()-1],input);
       input>>in;
    }
  }

}
