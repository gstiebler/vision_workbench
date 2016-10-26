/*
 * RegionGrowthLumOrdered.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#include "RegionGrowthLumOrdered.h"
#include <set>
#include "Region.h"
#include "RegionsAnalyzer.h"

using namespace std;
using namespace cv;

void execRegionGrowthLumOrdered(Mat &srcImg)
{
	RegionsManager regionsManager(srcImg.cols, srcImg.rows);
	RegionGrowthLumOrdered regionGrowthLumOrdered( srcImg, regionsManager );
	RegionsAnalyzer regionsAnalyzer(srcImg.rows);
	regionGrowthLumOrdered.exec(&regionsAnalyzer);
}

RegionGrowthLumOrdered::~RegionGrowthLumOrdered()
{
}

RegionGrowthLumOrdered::RegionGrowthLumOrdered(Mat &srcImg, RegionsManager &regionsManager) :
		_regionsManager( regionsManager ),
		_srcImg(srcImg)
{
}

void RegionGrowthLumOrdered::initLums(cv::Mat &srcImg)
{
	int width = srcImg.cols;
	int height = srcImg.rows;
	uchar lum;

	for(int y(1); y < height - 1; ++y)
	{
		for(int x(1); x < width - 1; ++x)
		{
			lum = srcImg.at<uchar>(y, x);
			_lums[lum].push_back(Point(x, y));
		}
	}
}

void RegionGrowthLumOrdered::initDirections(char vX[8], char vY[8])
{
	vX[0] = 0;
    vX[1] = 1;
    vX[2] = 1;
    vX[3] = 1;
    vX[4] = 0;
    vX[5] = -1;
    vX[6] = -1;
    vX[7] = -1;

    vY[0] = -1;
    vY[1] = -1;
    vY[2] = 0;
    vY[3] = 1;
    vY[4] = 1;
    vY[5] = 1;
    vY[6] = 0;
    vY[7] = -1;
}

void RegionGrowthLumOrdered::exec(RegionsAnalyzer *regionsAnalyzer)
{
	initLums(_srcImg);
	initDirections(_vX, _vY);

	for(int lum(0); lum < 256; ++lum)
	{
		vector<Point> &currentLums = _lums[lum];
		int size = (int) currentLums.size();
		for(int n(0); n < size; ++n)
		{
			Point &point = currentLums[n];
			processPoint(point);
		}

		_regionsManager.processRegionsAfterLum();
		if(regionsAnalyzer)
		{
			regionsAnalyzer->analyze(_regionsManager);
		}
	}
}

void RegionGrowthLumOrdered::processPoint(const cv::Point &point)
{
	set<Region*> regionsSet;

	for(int k(0); k < 8; ++k)
	{
		Point nPoint(point.x + _vX[k], point.y + _vY[k]);
		Region* region = _regionsManager.getRegion( nPoint );
		if( region )
		{
			regionsSet.insert( region );
		}
	}

	if( regionsSet.size() == 0 )
		_regionsManager.createRegion( point );
	else if ( regionsSet.size() == 1 )
		(*(regionsSet.begin()))->addPoint( point );
	else
	{
		std::vector<Region*> regionsVec(regionsSet.begin(), regionsSet.end());
		for(size_t i(1); i < regionsVec.size(); ++i)
		{
			_regionsManager.mergeRegions( regionsVec[i], regionsVec[i - 1], point );
		}
	}
}

