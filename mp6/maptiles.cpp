/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
  int row = theSource.getRows();
 	int column = theSource.getColumns();
 	MosaicCanvas* out = new MosaicCanvas(row,column);

 	vector<Point <3> > imgPoints;
 	map<Point<3>, TileImage> map;

 	for(auto tile = theTiles.begin();tile < theTiles.end(); tile++)
 	{
 		RGBAPixel ave = tile->getAverageColor();
 		Point<3> point(ave.red, ave.green, ave.blue);
 		map[point] = *tile;
 		imgPoints.push_back(point);
 	}

 	KDTree<3> pixelTree(imgPoints);

 	for(int i = 0; i < row; i++)
 	{
 		for(int j = 0; j < column; j++)
 		{
 			RGBAPixel regColor = theSource.getRegionColor(i, j);
 			Point<3> newpoint(regColor.red, regColor.green, regColor.blue);
 			out->setTile(i, j, map[pixelTree.findNearestNeighbor(newpoint)]);
 		}
 	}
 	return out;
}
