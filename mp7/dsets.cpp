/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num)
{
  for(int i=0; i<num; i++)
		v.push_back(-1);
}

int DisjointSets::find(int elem)
{
  if(v[elem]<0)
    return elem;
  else
    return v[elem]=find(v[elem]);
}


void DisjointSets::setunion(int a, int b)
{
  int root1=find(a);
  int root2=find(b);
  int newSize=v[root1]+v[root2];
  if(v[root1]<=v[root2])//root1 is root
  {
    v[root2]=root1;
    v[root1]=newSize;
  }
  else //root1 is root
  {
    v[root1]=root2;
    v[root2]=newSize;
  }
}
