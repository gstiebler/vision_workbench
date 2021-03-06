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
#include "Rectangle.h"

class RegionsManager;

class Region
{
public:

	/**
	 * Constructor
	 * @param[in,out] regionsManager The unique and only regions manager
	 */
	Region( RegionsManager *regionsManager, int id );

	~Region();

	/**
	 * Adds a point to the region
	 * @param[in] point The point to be added
	 */
	void addPoint( const cv::Point &point );

	void merge( Region *other );

	Region* finalRegion();

	bool wasMergedIntoAnotherRegion() const;
	void getPoints(std::vector<cv::Point> &points) const;
	void stop();
	bool isStopped() const;
	int getStoppedWidth() const;

	Rectangle limits;
	int id;
	std::vector<Rectangle> rectHistory;

	/** The points of the region */
	std::vector<cv::Point> points;

private:

	void replaceId(int newId);
	void mergeHistory(std::vector<Rectangle> &other);

	/** The unique and only regions manager */
	RegionsManager *_regionsManager;

	Region *_destMergedRegion;

	std::vector<Region*> _srcMergedRegions;

	bool _stopped;

	// the width the region have when it is stopped
	int _stoppedWidth;
};

#endif /* SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGION_H_ */
