/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <math.h>
#include <stdlib.h>

using namespace std;

SquareMaze::SquareMaze()
{
}

// SquareMaze::~SquareMaze()
// {
// 	maze.v.clear();
// }

void SquareMaze::makeMaze(int width, int height)
{
	Width=width;
	Height=height;
	int size=width*height;

	maze.addelements(size);

	for(int i=0; i<size; i++)
	{
		rWall.push_back(true);
		dWall.push_back(true);
	}

	int count = 0;

	//select random walls
	srand(time(NULL));

	while(count != size-1)
	{
		int checkRight = rand() % 2;
		int number = rand()%size;
		int x = number % width;
		int y = number / width;

		if(x!=width-1 && checkRight==0)
		{
			//not right neighbors
			if(maze.find(number)!= maze.find(number+1))
			{
				setWall(x,y,0,false);
				maze.setunion(number,number+1);
				count++;
			}
		}

		if(y!=height-1 && checkRight==1)
		{
			//not down neighbors
			if(maze.find(number)!= maze.find(number+width))
			{
				setWall(x,y,1,false);
				maze.setunion(number,number+width);
				count++;
			}
		}
	}
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
		//right direction
		int n=y*Width+x;
		if(dir==0 && x!=Width-1)
			return (rWall[n] == false);

		//down direction
		if(dir==1 && y!=Height-1)
			return (dWall[n] == false);

		//left direction
		if(dir==2 && x!=0)
			return (rWall[n-1] == false);

		//up direction
		if(dir==3 && y!=0)
			return (dWall[n-Width] == false);

		else
		return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	int n=y*Width+x;
	//rightmost cell
	if(dir == 0 && x >= 0 && y >= 0 && x < Width-1 && y < Height)
		rWall[n] = exists;

	//downmost cell
	if(dir == 1 && x >= 0 && y >= 0 && y < Height-1 && x < Width)
		dWall[n] = exists;
}


vector<int> SquareMaze::solveMaze()
{
	// int* endRowPointer = new int[Width];
	// vector<int> p;//path
	// solvePointer(0, 0, endRowPointer, p);
	//
	// int index = 0;//end
	// for(int i = 1; i < Width; i++)
	// {
	// 	if(endRowPointer[index] < endRowPointer[i])
	// 	//find the minimum index
	// 		index = i;
	// }
	//
	// p.clear();
	// solveIndex(0, 0, index, p);
	// delete[] endRowPointer;
	// return p;

	queue<int> q;

	while(!q.empty())
	{

	}

}


// void SquareMaze::solvePointer(int x, int y, int* endRow, vector<int> & path)
// {
// 	if(y == Height-1)
// 		endRow[x] = path.size();
//
// 	if(canTravel(x, y, 0) == true)
// 	{
// 		setWall(x, y, 0, true);
// 		path.push_back(0);
// 		solvePointer(x+1, y, endRow, path);
// 		setWall(x, y, 0, false);
// 		path.pop_back();
// 	}
//
// 	if(canTravel(x, y, 1) == true)
// 	{
// 		setWall(x, y, 1, true);
// 		path.push_back(1);
// 		solvePointer(x, y+1, endRow, path);
// 		setWall(x, y, 1, false);
// 		path.pop_back();
// 	}
//
// 	if(canTravel(x, y, 2) == true)
// 	{
// 		setWall(x-1, y, 0, true);
// 		path.push_back(2);
// 		solvePointer(x-1, y, endRow, path);
// 		setWall(x-1, y, 0, false);
// 		path.pop_back();
// 	}
//
// 	if(canTravel(x, y, 3) == true)
// 	{
// 		setWall(x, y-1, 1, true);
// 		path.push_back(3);
// 		solvePointer(x, y-1, endRow, path);
// 		setWall(x, y-1, 1, false);
// 		path.pop_back();
// 	}
// 	return;
// }
//
//
// bool SquareMaze::solveIndex(int x, int y, int end, vector<int> & path)
// {
// 	if(x == end && y == Height -1)
// 		return true;
//
// 	if(canTravel(x, y, 0))
// 	{
// 		setWall(x, y, 0, true);
// 		path.push_back(0);
// 		if(solveIndex(x+1, y, end, path))
// 		{
// 			setWall(x, y, 0, false);
// 			return true;
// 		}
// 		else
// 		{
// 			path.pop_back();
// 			setWall(x, y, 0, false);
// 		}
// 	}
//
// 	if(canTravel(x, y, 1))
// 	{
// 		setWall(x, y, 1, true);
// 		path.push_back(1);
// 		if(solveIndex(x, y+1, end, path))
// 		{
// 			setWall(x, y, 1, false);
// 			return true;
// 		}
// 		else
// 		{
// 			path.pop_back();
// 			setWall(x, y, 1, false);
// 		}
// 	}
//
// 	if(canTravel(x, y, 2))
// 	{
// 		setWall(x-1, y, 0, true);
// 		path.push_back(2);
// 		if(solveIndex(x-1, y, end, path))
// 		{
// 			setWall(x-1, y, 0, false);
// 			return true;
// 		}
// 		else
// 		{
// 			path.pop_back();
// 			setWall(x-1, y, 0, false);
// 		}
// 	}
//
// 	if(canTravel(x, y, 3))
// 	{
// 		setWall(x, y-1, 1, true);
// 		path.push_back(3);
// 		if(solveIndex(x, y-1, end, path))
// 		{
// 			setWall(x, y-1, 1, false);
// 			return true;
// 		}
// 		else
// 		{
// 			path.pop_back();
// 			setWall(x, y-1, 1, false);
// 		}
// 	}
// 	return false;
// }


PNG*  SquareMaze::drawMaze() const
{
	PNG* output = new PNG(Width*10+1, Height*10+1);

	//Blacken the entire topmost row and leftmost column of pixels
	for (int m=0; m<(Width*10)+1; m++)
		*((*output)(0, m)) = RGBAPixel(0,0,0);

	for (int n=10; n<(Height*10+1); n++)
		*((*output)(n, 0)) = RGBAPixel(0,0,0);

	for (int i=0; i<Width; i++)
	{
		for (int j=0; j<Height; j++)
		{
			//the right wall exists
			if (!canTravel(i, j, 0))
				for(int k=0; k<=10; k++)
					*(*output)((i+1)*10, (j*10)+k) = RGBAPixel(0,0,0);
			//the bottom wall exists
			if (!canTravel(i, j, 1))
				for(int k=0; k<=10; k++)
					*(*output)((i*10)+k, (j+1)*10) = RGBAPixel(0,0,0);
		}
	}

	return output;
}


PNG* SquareMaze::drawMazeWithSolution()
{
	vector<int> solution = solveMaze();
	PNG* output = drawMaze();
	int x = 5;
	int y = 5;

	for (int i=0; i<(int)solution.size(); i++)
	{
		if (solution[i]==0)
		{
			for (int j=0; j<=10; j++)
				*(*output)((x+j), y) = RGBAPixel(255,0,0);
			x += 10;
		}

		if (solution[i]==1)
		{
			for (int j=0; j<=10; j++)
				*(*output)(x, (y+j)) = RGBAPixel(255,0,0);
			y += 10;
		}

		if (solution[i]==2)
		{
			for (int j=0; j<=10; j++)
				*(*output)((x-j), y) = RGBAPixel(255,0,0);
			x -= 10;
		}

		if (solution[i]==3)
		{
			for (int j=0; j<=10; j++)
				*(*output)(x, (y-j)) = RGBAPixel(255,0,0);
			y -= 10;

		}
	}

	//draw the exit
	int endx = x/10;
	int endy = Height-1;

	for (int k=1; k<=9; k++)
		*(*output)(endx*10+k, (endy+1)*10) = RGBAPixel(255,255,255);

	return output;
}
