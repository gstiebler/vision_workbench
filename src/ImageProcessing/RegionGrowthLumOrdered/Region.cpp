/*
 * Region.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#include "Region.h"
#include "RegionsManager.h"
#include <assert.h>
#include <algorithm>

using namespace std;
using namespace cv;


Region::Region( RegionsManager *regionsManager, int id ) :
	_regionsManager( regionsManager ),
	id( id ),
	xMin( 10000000 ),
	xMax( -1 ),
	yMin( 10000000 ),
	yMax( -1 ),
	_destMergedRegion( nullptr )
{
}

Region::~Region()
{
}

void Region::addPoint( const Point &point )
{
	_points.push_back( point );

	xMin = min(point.x, xMin);
	xMax = max(point.x, xMax);
	yMin = min(point.y, yMin);
	yMax = max(point.y, yMax);

	_regionsManager->setRegion( point, this );
}

void Region::merge( Region *other )
{
	xMin = min(xMin, other->xMin);
	xMax = max(xMax, other->xMax);
	yMin = min(yMin, other->yMin);
	yMax = max(yMax, other->yMax);

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

int Region::width() const
{
	return xMax - xMin + 1;
}

int Region::height() const
{
	return yMax - yMin + 1;
}

bool Region::isFinal() const
{
	return !_destMergedRegion;
}

void Region::getPoints(std::vector<cv::Point> &points) const
{
	points.insert(points.end(), _points.begin(), _points.end());
	for(auto &srcRegion : _srcMergedRegions)
	{
		srcRegion->getPoints(points);
	}
}
