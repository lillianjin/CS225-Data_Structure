
/* Your code here! */

#ifndef _DSETS_H_
#define _DSETS_H_
#include <vector>
#include <iostream>
using namespace std;

class DisjointSets
{
public:
	/**
	 * Creates n unconnected root nodes at the end of the vector.
	 */
	void addelements(int num);

	/**
	 * This function should compress paths and works as described in lecture.
   * Returns the index of the root of the up-tree in which the parameter element resides.
	 */
	int find(int elem);

	/**
	 * Set union of two trees
   * the smaller (in terms of number of nodes) should point at the larger
   * find the roots of its arguments before combining the trees.
   * If the two sets are the same size, make the tree containing the second
   * argument point to the tree containing the first.
	 */
	void setunion(int a, int b);

private:
	vector<int> v;

};

#endif
