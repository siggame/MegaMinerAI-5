#include "tree.h"

tree::tree()
{
  for(unsigned int i=0;i<4;i++)
  {
    child[i]=NULL;
  }
}
tree::~tree()
{
  for(unsigned int i=0;i<4;i++)
  {
    if(child[i] != NULL)
    {
      delete child[i];
    }
  }  

}
