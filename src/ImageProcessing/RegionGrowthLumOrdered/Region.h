/*
 * Region.h
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGION_H_
#define SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGION_H_

#include <opencv2/opencv.hpp>
#include <vector>

class RegionsManager;

class Region
{
public:

	/**
	 * Constructor
	 * @param[in,out] regionsManager The unique and only regions manager
	 */
	Region( RegionsManager *regionsManager, int id );

	/**
	 * Adds a point to the region
	 * @param[in] point The point to be added
	 */
	void addPoint( const cv::Point &point );

	void merge( Region *other );

	Region* finalRegion();

	int length() const;

	int _xMin, _xMax;

	int _id;

private:

	/** The points of the region */
	std::vector<cv::Point> _points;

	/** The unique and only regions manager */
	RegionsManager *_regionsManager;

	Region *_mergedRegion;
};

#endif /* SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGION_H_ */
