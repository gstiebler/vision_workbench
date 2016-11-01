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

RegionsManager::RegionsManager(int width, int height) {
	_regionOfPixel.resize(height);
	for (auto &ropLine : _regionOfPixel) {
		ropLine.resize(width);
		std::fill(ropLine.begin(), ropLine.end(), 0);
	}

	// null region
	regionsIndexMap.push_back(0);
	regions.push_back(new Region(this, INVALID_REGION));
}

RegionsManager::~RegionsManager() {
	for (auto &region : regions) {
		delete region;
	}
}

Region* RegionsManager::getRegion(const Point &point) {
	int originalId = _regionOfPixel[point.y][point.x];
	if (originalId == INVALID_REGION) {
		return nullptr;
	}
	int newId = regionsIndexMap[originalId];
	return regions[newId];
}

void RegionsManager::setRegion(const Point &point, Region *region) {
	_regionOfPixel[point.y][point.x] = region->id;
}

void RegionsManager::createRegion(const Point &point) {
	regionsIndexMap.push_back(regions.size());
	Region *region = new Region(this, regions.size());
	region->addPoint(point);
	regions.push_back(region);
	activeRegions[region->id] = region;
	notStoppedActiveRegions[region->id] = region;
}

void RegionsManager::mergeRegions(std::vector<Region*> &regions, const cv::Point &point) {
	if(!shouldMergeRegionsFn(regions)) return;

	for(size_t i(1); i < regions.size(); ++i) {
		mergePairOfRegions( regions[i], regions[i - 1]);
	}
	regions.back()->addPoint(point);
}

void RegionsManager::mergePairOfRegions(Region *region1, Region *region2) {
	region1->merge(region2);
	activeRegions.erase(region1->id);
	notStoppedActiveRegions.erase(region1->id);
}

void RegionsManager::processRegionsAfterLum() {
	auto regionIt = notStoppedActiveRegions.begin();
	while (regionIt != notStoppedActiveRegions.end()) {
		Region *region = (*regionIt).second;
		region->rectHistory.push_back(region->limits);

		if (shouldStopRegionFn(*region)) {
			region->stopped = true;
			notStoppedActiveRegions.erase(region->id);

			auto previous = regionIt;
			regionIt++;
			//activeRegions.erase(previous);
		} else {
			regionIt++;
		}
	}
}
