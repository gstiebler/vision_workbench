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
	_id( id ),
	_xMin( 10000000 ),
	_xMax( -1 ),
	_yMin( 10000000 ),
	_yMax( -1 ),
	_mergedRegion( nullptr )
{
}

Region::~Region()
{
}

void Region::addPoint( const Point &point )
{
	_points.push_back( point );

	_xMin = min(point.x, _xMin);
	_xMax = max(point.x, _xMax);
	_yMin = min(point.y, _yMin);
	_yMax = max(point.y, _yMax);

	assert( width() <= _points.size() );

	_regionsManager->setRegion( point, this );
}

void Region::merge( Region *other )
{
	for(int n(0); n < _points.size(); ++n)
		_regionsManager->setRegion( _points[n], other );

	other->_points.insert( other->_points.end(), _points.begin(), _points.end() );

	_xMin = min(_xMin, other->_xMin);
	_xMax = max(_xMax, other->_xMax);
	_yMin = min(_yMin, other->_yMin);
	_yMax = max(_yMax, other->_yMax);

	_mergedRegion = other;
}

int Region::width() const
{
	return _xMax - _xMin + 1;
}

int Region::height() const
{
	return _yMax - _yMin + 1;
}

Region* Region::finalRegion()
{
	assert(this != _mergedRegion);

	if( _mergedRegion )
		return _mergedRegion->finalRegion();
	else
		return this;
}
