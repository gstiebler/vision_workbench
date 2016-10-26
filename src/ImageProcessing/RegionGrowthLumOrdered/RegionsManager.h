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

	/**
	 * Merges 2 regions (if applicable)
	 * @param[in] region1 First region
	 * @param[in] region2 Second region
	 */
	static void mergeRegions( Region *region1, Region *region2, const cv::Point &point );

	/** All the regions */
	std::vector<Region*> regions;

private:

	/** Region of each pixel */
	std::vector< std::vector< Region* > > _regionOfPixel;
};

#endif /* SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGIONSMANAGER_H_ */
