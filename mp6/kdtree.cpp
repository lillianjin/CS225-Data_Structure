/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] == second[curDim])
      return first < second;
    else
      return first[curDim] < second[curDim];
}


//============================	shouldReplace	==================================

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
	if(distance(potential, target) == distance(currentBest, target))
		return potential<currentBest;
  else
    return distance(potential,target)<distance(currentBest,target);
}

template <int Dim>
int KDTree<Dim>::distance(const Point<Dim> & point1, const Point<Dim> & point2) const
{
  int distance = 0;
	for(int i = 0; i < Dim; i++)
		distance += pow(point1[i]-point2[i],2);
	return distance;
}

//============================	CONSTRUCTOR	====================================

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    points=newPoints;
    build(0,0,points.size()-1);
}

template <int Dim>
void KDTree<Dim>::build(int currDim, int left, int right)
{
  if(left>right)
    return;
  int mid=(left+right)/2;
  mid=quickSelect(left, right, currDim, mid);
  build((currDim+1)%Dim, left, mid-1);
  build((currDim+1)%Dim, mid+1, right);
}

//finding the median of the vector of points
template <int Dim>
int KDTree<Dim>::quickSelect(int left, int right, int currDim, int n)
{
  if(left==right)
    return left;
  int mid=(left+right)/2;
  mid=partition(left, right, currDim, mid);

  if(n==mid)
    return n;
  else if(n>mid)
    return quickSelect(mid+1, right, currDim, n);
  else
    return quickSelect(left, mid-1, currDim, n);

}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int currDim, int n)
{
    Point<Dim> value = points[n];
    swap(n, right);
    int index = left;

    for(int i = left; i < right; i++)
    {
        if(smallerDimVal(points[i], value, currDim))
        {
            swap(index, i);
            index++;
        }
    }
    swap(right, index);
    return index;
}


template<int Dim>
void KDTree<Dim>::swap(int x, int y)
{
	Point<Dim> temp = points[x];
	points[x] = points[y];
	points[y] = temp;
}

//=========================	findNearestNeighbor	===============================

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return searchNN(0, query, 0, points.size()-1);
}

template <int Dim>
Point<Dim> KDTree<Dim>::searchNN(int currDim, const Point<Dim>& query, int left, int right)const
{
  int mid = (left+right)/2;
	Point<Dim> root = points[mid];
	Point<Dim> Best ,newBest;

	if(left>=right)
		return root;

	if(smallerDimVal(query,root,currDim))
		Best = searchNN((currDim+1)%Dim, query, left, mid-1);
	else
		Best = searchNN((currDim+1)%Dim, query, mid+1,right);

	if(shouldReplace(query,Best,root))
		Best = root;

	int r = distance(Best, query);

	if(pow(root[currDim]-query[currDim],2) <= r)
	{
		if(smallerDimVal(query,root,currDim))
			newBest = searchNN((currDim+1)%Dim, query, mid+1, right);
		else
			newBest = searchNN((currDim+1)%Dim, query, left, mid-1);

		if(shouldReplace(query,Best,newBest))
			Best = newBest;
	}

	return Best;
}
