/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

	vector<Point<3>> xyzpoints;
	map<Point<3>, TileImage*> map_;

	for(auto it = theTiles.begin(); it != theTiles.end(); ++it){
		LUVAPixel newPixel = it->getAverageColor();
		Point<3> point = convertToXYZ(newPixel);
		xyzpoints.push_back(point);
		map_[point] = &* it;
	}
	KDTree<3> KDTree_Color(xyzpoints);

	MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
	for( int i = 0; i < canvas->getRows(); i++){
		for(int j = 0; j < canvas->getColumns(); j++){
			Point<3> newPoint = convertToXYZ(theSource.getRegionColor(i,j));
			Point<3> KDTreePoint = KDTree_Color.findNearestNeighbor(newPoint);
			TileImage* newTile = map_[KDTreePoint];
			canvas->setTile(i, j,  newTile);
		}
	}

    return canvas;
}

