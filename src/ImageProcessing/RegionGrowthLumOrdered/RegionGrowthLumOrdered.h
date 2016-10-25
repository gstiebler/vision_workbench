/*
 * RegionGrowthLumOrdered.h
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_H_
#define SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_H_

#include <opencv2/opencv.hpp>
#include <vector>

void execRegionGrowthLumOrdered(cv::Mat &srcImg);

class RegionGrowthLumOrdered
{
public:
	RegionGrowthLumOrdered(cv::Mat &srcImg);
	virtual ~RegionGrowthLumOrdered();
	void exec();

private:
	cv::Mat &_srcImg;
	std::vector<cv::Point> _lums[256];

	void initLums(cv::Mat &srcImg);
	static void initDirections(char vX[8], char vY[8]);
};

#endif /* SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_H_ */
