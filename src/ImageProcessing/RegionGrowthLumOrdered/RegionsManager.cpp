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

RegionsManager::RegionsManager( int width, int height )
{
	_regionOfPixel.resize( height );
	for(auto &ropLine : _regionOfPixel)
	{
		ropLine.resize(width);
		std::fill(ropLine.begin(), ropLine.end(), nullptr);
	}
}

RegionsManager::~RegionsManager()
{
}

Region* RegionsManager::getRegion( const Point &point )
{
	Region *region = _regionOfPixel[point.y][point.x];
	if( region )
		return region->finalRegion();
	else
		return nullptr;
}

void RegionsManager::setRegion( const Point &point, Region *region )
{
	_regionOfPixel[point.y][point.x] = region;
}

void RegionsManager::createRegion( const Point &point )
{
	Region region( this, _regions.size() + 1 );
	_regions.push_back( region );
	region.addPoint( point );
}

void RegionsManager::mergeRegions( Region *region1, Region *region2, Point &point )
{
	region1 = region1->finalRegion();
	region2 = region2->finalRegion();

	if( region1 == region2 )
		return;

	region1->merge( region2 );
	region2->addPoint( point );
}
