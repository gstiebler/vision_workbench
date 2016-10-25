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
	_id( id ),
	_xMin( 10000000 ),
	_xMax( -1 ),
	_mergedRegion( nullptr )
{
}

Region::Region(const Region &other) :
		_xMin(other._xMin),
		_xMax(other._xMax),
		_id(other._id),
		_points(other._points),
		_regionsManager(other._regionsManager),
		_mergedRegion(other._mergedRegion)
{
}

void Region::addPoint( const Point &point )
{
	_points.push_back( point );
	if( point.x < _xMin )
		_xMin = point.x;

	if( point.x > _xMax )
		_xMax = point.x;

	assert( length() <= _points.size() );

	_regionsManager->setRegion( point, this );
}

void Region::merge( Region *other )
{
	for(int n(0); n < _points.size(); ++n)
		_regionsManager->setRegion( _points[n], other );

	other->_points.insert( other->_points.end(), _points.begin(), _points.end() );

	if(_xMin < other->_xMin)
		other->_xMin = _xMin;

	if(_xMax > other->_xMax)
		other->_xMax = _xMax;

	_mergedRegion = other;
}

int Region::length() const
{
	return _xMax - _xMin + 1;
}

Region* Region::finalRegion()
{
	assert(this != _mergedRegion);

	if( _mergedRegion )
		return _mergedRegion->finalRegion();
	else
		return this;
}