/*
 * RegionsManager.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#include "RegionsManager.h"
#include "Region.h"

using namespace std;
using namespace cv;

RegionsManager::RegionsManager( int width, int height ) :
	_height( height ),
	_counter( 0 )
{
	_regionOfPixel = new Region ** [_height];
	for(int y(0); y < _height; ++y)
	{
		_regionOfPixel[y] = new Region * [width];
		memset( _regionOfPixel[y], 0, width * sizeof(Region*) );
	}
}



RegionsManager::~RegionsManager()
{
	for(int y(0); y < _height; ++y)
		delete [] _regionOfPixel[y];

	delete [] _regionOfPixel;

	for(int n(0); n < _regions.size(); ++n)
		delete _regions[n];
}



Region* RegionsManager::getRegion( const Point &point )
{
	Region *region = _regionOfPixel[point.y][point.x];
	if( region )
		return region->finalRegion();
	else
		return NULL;
}



void RegionsManager::setRegion( const Point &point, Region *region )
{
	_regionOfPixel[point.y][point.x] = region;
}



void RegionsManager::createRegion( const Point &point )
{
	Region *region = new Region( this, ++_counter );
	_regions.push_back( region );
	region->addPoint( point );
}



void RegionsManager::mergeRegions( Region *region1, Region *region2, Point &point, int maxHorizontalIntersection )
{
	region1 = region1->finalRegion();
	region2 = region2->finalRegion();

	if( region1 == region2 )
		return;

	if( region1->horizontalIntersection( region2 ) > maxHorizontalIntersection )
		return;

	region1->merge( region2 );
	region2->addPoint( point );
}
