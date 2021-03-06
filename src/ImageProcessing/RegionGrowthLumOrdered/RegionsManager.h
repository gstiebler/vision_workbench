/*
 * RegionsManager.h
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGIONSMANAGER_H_
#define SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGIONSMANAGER_H_

#include <opencv2/opencv.hpp>
#include <vector>
#include <functional>

class Region;

class RegionsManager
{
public:

	/**
	 * Constructor
	 * @param[in] width Width of the source image
	 * @param[in] height Height of the source image
	 */
	RegionsManager( int width, int height );

	/**
	 * Destructor
	 */
	~RegionsManager();

	/**
	 * Returns the region of a point
	 * @param[in] point The point of the region
	 * @return The region of the point
	 */
	Region* getRegion( const cv::Point &point );

	/**
	 * Sets the region of a point
	 * @param[in] point The point of the region
	 * @param[in] region The region of the point
	 */
	void setRegion( const cv::Point &point, Region *region );

	/**
	 * Creates a region from a point
	 * @param[in] point First point of the region
	 */
	void createRegion( const cv::Point &point );

	void mergeRegions( std::vector<Region*> &regions, const cv::Point &point );

	void processRegionsAfterLum();

	/** All the regions */
	std::vector<Region*> regions;

	std::vector<int> regionsIndexMap;

	std::function<bool(Region&)> shouldStopRegionFn;
	std::function<bool(std::vector<Region*> &regions)> shouldMergeRegionsFn;

	// regions not merged into another regions, and not stopped
	std::map<int, Region*> activeRegions;

	std::map<int, Region*> notStoppedActiveRegions;

private:

	/** Region id of each pixel */
	std::vector< std::vector< int > > _regionOfPixel;

	/**
	 * Merges 2 regions (if applicable)
	 * @param[in] region1 First region
	 * @param[in] region2 Second region
	 */
	void mergePairOfRegions( Region *region1, Region *region2);
};

#endif /* SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGIONSMANAGER_H_ */
