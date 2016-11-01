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
	limits({1000000, -1, 1000000, -1}),
	_destMergedRegion( nullptr ),
	_stopped(false),
	_stoppedWidth(-1)
{
}

Region::~Region()
{
}

void Region::addPoint( const Point &point )
{
	//if(stopped) return;

	points.push_back( point );
	limits.addPoint(point);
	_regionsManager->setRegion( point, this );
}

void Region::merge( Region *other )
{
	other->limits.merge(limits);
	_destMergedRegion = other;
	other->_srcMergedRegions.push_back(this);
	other->mergeHistory(rectHistory);
	other->_stopped = other->_stopped || _stopped;
	other->_stoppedWidth = _stoppedWidth;
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
	return _destMergedRegion;
}

void Region::getPoints(std::vector<cv::Point> &outPoints) const
{
	outPoints.insert(outPoints.end(), points.begin(), points.end());
	for(auto &srcRegion : _srcMergedRegions)
	{
		srcRegion->getPoints(outPoints);
	}
}

void Region::stop() {
	_stopped = true;
	_stoppedWidth = limits.width();
}

bool Region::isStopped() const {
	return _stopped;
}

int Region::getStoppedWidth() const {
	return _stoppedWidth;
}

void Region::mergeHistory(vector<Rectangle> &other)
{
	vector<Rectangle> result;
	vector<Rectangle>::iterator mainIt, mainEndIt, secondaryIt;
	if(rectHistory.size() > other.size())
	{
		result = rectHistory;
		mainIt = result.begin() + rectHistory.size() - other.size();
		mainEndIt = result.end();
		secondaryIt = other.begin();
	}
	else
	{
		result = other;
		mainIt = result.begin() + other.size() - rectHistory.size();
		mainEndIt = result.end();
		secondaryIt = rectHistory.begin();
	}

	while(mainIt != mainEndIt)
	{
		mainIt->merge(*secondaryIt);
		mainIt++;
		secondaryIt++;
	}
	rectHistory = result;
}
