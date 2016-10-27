/*
 * Region.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#include "Region.h"
#include "RegionsManager.h"
#include <assert.h>

using namespace std;
using namespace cv;

Region::Region( RegionsManager *regionsManager, int id ) :
	_regionsManager( regionsManager ),
	id( id ),
	stopped(false),
	limits({1000000, -1, 1000000, -1}),
	_destMergedRegion( nullptr )
{
}

Region::~Region()
{
}

void Region::addPoint( const Point &point )
{
	if(stopped) return;

	points.push_back( point );
	limits.addPoint(point);
	_regionsManager->setRegion( point, this );
}

void Region::merge( Region *other )
{
	limits.merge(other->limits);
	_destMergedRegion = other;
	other->_srcMergedRegions.push_back(this);

	replaceId(other->id);
}

void Region::replaceId(int newId)
{
	_regionsManager->regionsIndexMap[id] = newId;
	for(auto &srcRegion : _srcMergedRegions)
	{
		srcRegion->replaceId(newId);
	}
}

bool Region::wasMergedIntoAnotherRegion() const
{
	return !_destMergedRegion;
}

void Region::getPoints(std::vector<cv::Point> &outPoints) const
{
	outPoints.insert(outPoints.end(), points.begin(), points.end());
	for(auto &srcRegion : _srcMergedRegions)
	{
		srcRegion->getPoints(outPoints);
	}
}
