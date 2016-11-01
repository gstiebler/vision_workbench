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
#include "RegionsManager.h"

class RegionsAnalyzer;

struct RegionsGrowthParams {
	int difHeightHistoryIndex;
	int minHeight;
	double maxHeightFactor;
	int maxLum;
	double maxWidthFactor;
};

void execRegionGrowthLumOrdered(cv::Mat &srcImg, RegionsManager &regionsManager);

class RegionGrowthLumOrdered
{
public:
	RegionGrowthLumOrdered(cv::Mat &srcImg, RegionsManager &regionsManager);
	virtual ~RegionGrowthLumOrdered();
	void exec(uchar maxLum, RegionsAnalyzer *regionsAnalyzer);

	RegionsManager &_regionsManager;

private:
	void initLums(cv::Mat &srcImg);
	static void initDirections(char vX[8], char vY[8]);
	void processPoint(const cv::Point &point);

	cv::Mat &_srcImg;
	std::vector<cv::Point> _lums[256];
	char _vX[8], _vY[8];
};

#endif /* SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_H_ */
