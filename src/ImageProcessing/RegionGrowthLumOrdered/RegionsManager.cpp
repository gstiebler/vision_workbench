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

#define INVALID_REGION 0

RegionsManager::RegionsManager( int width, int height )
{
	_regionOfPixel.resize( height );
	for(auto &ropLine : _regionOfPixel)
	{
		ropLine.resize(width);
		std::fill(ropLine.begin(), ropLine.end(), 0);
	}

	// null region
	regionsIndexMap.push_back( 0 );
	regions.push_back( new Region( this, INVALID_REGION ) );
}

RegionsManager::~RegionsManager()
{
	for(auto &region : regions)
	{
		delete region;
	}
}

Region* RegionsManager::getRegion( const Point &point )
{
	int originalId = _regionOfPixel[point.y][point.x];
	if(originalId == INVALID_REGION)
	{
		return nullptr;
	}
	int newId = regionsIndexMap[originalId];
	return regions[newId];
}

void RegionsManager::setRegion( const Point &point, Region *region )
{
	_regionOfPixel[point.y][point.x] = region->id;
}

void RegionsManager::createRegion( const Point &point )
{
	regionsIndexMap.push_back( regions.size() );
	Region *region = new Region( this, regions.size() );
	region->addPoint(point);
	regions.push_back( region );
	activeRegions.insert(region);
}

void RegionsManager::mergeRegions( Region *region1, Region *region2, const Point &point )
{
	if( region1 == region2 )
		return;

	if(region1->stopped || region2->stopped)
		return;

	region1->merge( region2 );
	region2->addPoint( point );

	activeRegions.erase(region1);
}

void RegionsManager::processRegionsAfterLum()
{
	auto regionIt = activeRegions.begin();
	while(regionIt != activeRegions.end())
	{
		Region *region = *regionIt;
		region->heightHistory.push_back(region->height());

		if(shouldStopRegionFn(*region))
		{
			region->stopped = true;
			stoppedRegions.push_back(region);

			auto previous = regionIt;
			activeRegions.erase(previous);
			regionIt++;
		}
		else
		{
			regionIt++;
		}
	}
}
