/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */

 #include "quadtree.h"
 #include <iostream>
 #include <math.h>

 using namespace std;

 Quadtree::Quadtree()
 {
 	root = NULL;
 	res = 0;
 }


 Quadtree::Quadtree(PNG const & source, int resolution)
 {
 	root = NULL;
 	res = resolution;
 	buildTree(source,resolution);
 }


 Quadtree::QuadtreeNode::QuadtreeNode()
 {
 	this->nwChild = NULL;
 	this->neChild = NULL;
 	this->swChild = NULL;
 	this->seChild = NULL;
 	this->element = RGBAPixel();
 }


 Quadtree::Quadtree(Quadtree const & other)
 {
 	res = other.res;
 	root=copy(other.root);
 }


 Quadtree::QuadtreeNode* Quadtree::copy(QuadtreeNode* subRoot)
 {
 	if(subRoot==NULL)
 		return NULL;
 	else
 	{
 		QuadtreeNode* newRoot = new QuadtreeNode();
 		newRoot->element=subRoot->element;

 		if(subRoot->nwChild!=NULL)
 		{
 			newRoot->nwChild=copy(subRoot->nwChild);
 			newRoot->neChild=copy(subRoot->neChild);
 			newRoot->swChild=copy(subRoot->swChild);
 			newRoot->seChild=copy(subRoot->seChild);
 		}
 		return newRoot;
 	}
 }


 Quadtree::~Quadtree()
 {
 	res = 0;
 	clear(root);
 	//root = NULL;
 }


 void Quadtree::clear(QuadtreeNode*& subRoot)
 {

 	if(subRoot==NULL)
 		return;

 	clear(subRoot->nwChild);
 	clear(subRoot->neChild);
 	clear(subRoot->swChild);
 	clear(subRoot->seChild);
 	delete subRoot;
 	subRoot = NULL;
 }


 Quadtree const & Quadtree::operator=(Quadtree const & other)
 {
 	if(this != &other)
 	{
 		clear(root);
 		res=0;
 		if(other.root!=NULL)
 		{
 			root=copy(other.root);
 			res = other.res;
 		}
 	}
 	return *this;
 }


 void Quadtree::buildTree(PNG const & source, int resolution)
 {
 	clear(root);
 	res = resolution;
 	build(root,0,0,source,resolution);
 }


 void Quadtree::build(QuadtreeNode*& subRoot, int xCoord, int yCoord, PNG const & source, int resolution)
 {
 	subRoot = new QuadtreeNode();

 	if(resolution == 1)
 	{
 		subRoot->nwChild = NULL;
 		subRoot->neChild = NULL;
 		subRoot->swChild = NULL;
 		subRoot->seChild = NULL;
 		subRoot->element = *source(xCoord,yCoord);
 		return;
 	}

 	int tempRes = resolution/2;
 	build(subRoot->nwChild,xCoord,yCoord,source,tempRes);
 	build(subRoot->neChild,xCoord+tempRes,yCoord,source,tempRes);
 	build(subRoot->swChild,xCoord,yCoord+tempRes,source,tempRes);
 	build(subRoot->seChild,xCoord+tempRes,yCoord+tempRes,source,tempRes);

 	subRoot->element.red = ((subRoot->nwChild->element).red+(subRoot->neChild->element).red+(subRoot->swChild->element).red+(subRoot->seChild->element.red))/4;
 	subRoot->element.green = ((subRoot->nwChild->element).green+(subRoot->neChild->element).green+(subRoot->swChild->element).green+(subRoot->seChild->element).green)/4;
 	subRoot->element.blue = ((subRoot->nwChild->element).blue+(subRoot->neChild->element).blue+(subRoot->swChild->element).blue+(subRoot->seChild->element).blue)/4;
 }


 RGBAPixel Quadtree::getPixel(int x, int y) const
 {
 	if(root == NULL || x>=res || y >= res || x<0 || y<0)
 		return RGBAPixel();
 	else
 		return helpGetPixel(x,y,res,root);
 }

 RGBAPixel Quadtree::helpGetPixel(int x, int y, int resolution, QuadtreeNode* subRoot)const
 {
 	if(subRoot->nwChild == NULL || resolution == 1)
 		return subRoot->element;

 	if(x<resolution/2 && y<resolution/2)
 		return helpGetPixel(x,y,resolution/2,subRoot->nwChild);

 	else if(x>=resolution/2 && y<resolution/2)
 		return helpGetPixel(x-resolution/2,y,resolution/2,subRoot->neChild);

 	else if(x<resolution/2 && y>=resolution/2)
 		return helpGetPixel(x,y-resolution/2,resolution/2,subRoot->swChild);

 	//if(x>=resolution/2 && y>=resolution/2)
 	else
 		return helpGetPixel(x-resolution/2,y-resolution/2,resolution/2,subRoot->seChild);

 }

 PNG Quadtree::decompress() const
 {
 	if(root==NULL)
 		return PNG();

 	PNG result(res,res);
 	for(int i=0; i<res; i++)
 	{
 		for(int j=0; j<res; j++)
 		{
 			*result(i,j)=getPixel(i,j);
 		}
 	}
 	return result;
 }


 void Quadtree::clockwiseRotate()
 {
 	if(root == NULL)
 		return;
 	rotate(root);
 }


 void Quadtree::rotate(QuadtreeNode*& subRoot)
 {
 	if(subRoot->nwChild==NULL)
 		return;

 	else
 	{
 		QuadtreeNode* temp = subRoot->nwChild;
 		subRoot->nwChild = subRoot->swChild;
 		subRoot->swChild = subRoot->seChild;
 		subRoot->seChild = subRoot->neChild;
 		subRoot->neChild = temp;
 		temp = NULL;

 		rotate(subRoot->nwChild);
 		rotate(subRoot->neChild);
 		rotate(subRoot->swChild);
 		rotate(subRoot->seChild);
 	}
 }


 void Quadtree::prune(int tolerance)
 {
 	prune(root,tolerance);
 }


 void Quadtree::prune(QuadtreeNode*& subRoot,int tolerance)
 {
 	if(subRoot == NULL)
 		return;

 	if(diff(subRoot,subRoot,tolerance))
 	{
 		clear(subRoot->nwChild);
 		clear(subRoot->neChild);
 		clear(subRoot->swChild);
 		clear(subRoot->seChild);
 	}
 	else
 	{
 		prune(subRoot->nwChild,tolerance);
 		prune(subRoot->neChild,tolerance);
 		prune(subRoot->swChild,tolerance);
 		prune(subRoot->seChild,tolerance);
 	}
 }

 bool Quadtree::diff(QuadtreeNode*& tempNode, QuadtreeNode*& subRoot, int tolerance)
 {
 	if(subRoot == NULL)
 		return false;

 	if(subRoot->nwChild == NULL)
 	{
    int difference=pow(tempNode->element.red-subRoot->element.red,2)+
 			pow(tempNode->element.green-subRoot->element.green,2)+
 			pow(tempNode->element.blue-subRoot->element.blue,2);
    if(difference<=tolerance)
      return true;
    else
      return false;
 	}
 	return diff(tempNode,subRoot->nwChild,tolerance)&&
 			diff(tempNode,subRoot->neChild,tolerance)&&
 			diff(tempNode,subRoot->swChild,tolerance)&&
 			diff(tempNode,subRoot->seChild,tolerance);
 }


 int Quadtree::pruneSize(int tolerance) const
 {
 	return pruneSize(root,tolerance);
 }


 int Quadtree::pruneSize(QuadtreeNode* const & subRoot,int tolerance) const
 {
 	if(subRoot == NULL)
 		return 0;

 	if(diff2(subRoot,subRoot,tolerance))
 		return 1;

 	else
 	{
 		return pruneSize(subRoot->nwChild,tolerance)+pruneSize(subRoot->neChild,tolerance)
    +pruneSize(subRoot->swChild,tolerance)+pruneSize(subRoot->seChild,tolerance);
 	}
 }


 bool Quadtree::diff2(QuadtreeNode* const & tempNode, QuadtreeNode* const & subRoot, int tolerance)const
 {
  if(subRoot == NULL)
    return false;

  if(subRoot->nwChild == NULL)
  {
    int difference=pow(tempNode->element.red-subRoot->element.red,2)+
      pow(tempNode->element.green-subRoot->element.green,2)+
      pow(tempNode->element.blue-subRoot->element.blue,2);
    if(difference<=tolerance)
      return true;
    else
      return false;
  }
  return diff2(tempNode,subRoot->nwChild,tolerance)&&
      diff2(tempNode,subRoot->neChild,tolerance)&&
      diff2(tempNode,subRoot->swChild,tolerance)&&
      diff2(tempNode,subRoot->seChild,tolerance);
 }


 int Quadtree::idealPrune(int numLeaves) const
 {
   int maximum = pow(255,2)*3;
   int minimum = 0;
   if(root==NULL || numLeaves>pow(res,2))
    return 0;
   else
    return ideal(minimum,maximum,numLeaves);
 }


 int Quadtree::ideal(int minimum,int maximum,int numLeaves) const
 {
   //base case
  if(maximum-minimum<=1)
  {
    if (pruneSize(minimum)<=numLeaves)
      return minimum;
    else
      return maximum;
  }

  //use current to find the minimum value
  int current=(maximum+minimum)/2;
  if(pruneSize(current)>numLeaves)
  {
    return ideal(current,maximum,numLeaves);
  }

  else
    return ideal(minimum,current,numLeaves);

 	}
