/* Your code here! */
#ifndef _MAZE_H_
#define _MAZE_H_

#include "dsets.h"
#include "png.h"
#include "rgbapixel.h"
#include <algorithm>
#include <vector>

using namespace std;

class SquareMaze {
public:
	//No-parameter constructor.
	SquareMaze();

	// ~SquareMaze();

	//Makes a new SquareMaze of the given height and width.
	//select random walls to delete without creating a cycle, until there are no more walls
	//only need to store 2 bits per square: the "down" and "right" walls.
	//The finished maze is always a tree of corridors.
	void makeMaze(int width, int height);

	//determine whether it is possible to travel in the given direction from the square at coordinates (x,y).
	//@dir	The desired direction to move from the current cel
	bool canTravel(int x, int y, int dir) const;

	//Sets whether or not the specified wall exists.
	//This function should be fast (constant time).
	//@exists	true if setting the wall to exist, false otherwise
	void setWall(int x, int y, int dir, bool exists);

	//returns the winning path from the origin to the destination as a vector of integers
	vector<int> solveMaze();

	//Draws the maze without the solution.
	//First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1).
	//Blacken the entire topmost row and leftmost column of pixels, except the entrance (1,0) through (9,0).
	//For each square in the maze, call its maze coordinates (x,y). If the right wall exists,
	//then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10.
	//If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
	PNG* drawMaze() const;

	//Make the exit by undoing the bottom wall of the destination square:
	//call the destination maze coordinates (x,y), and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
	PNG* drawMazeWithSolution();


private:
	// void solvePointer(int x, int y, int* endRow, vector<int> & path);
	// bool solveIndex(int x, int y, int end, vector<int> & path);

	int Width;
	int Height;
	vector<bool> rWall;
	vector<bool> dWall;
	DisjointSets maze;

	class soln{
		vector<int> d;
		vector<int> p;
		soln()
		{
			for(int i=0; i<(int)d.size(); i++)
			{
				d[i]=-1;
				p[i]=-1;
			}
		};

		// ~soln()
		// {
		// 	d.clear();
		// 	p.clear();
		// };
	};
};

#endif
