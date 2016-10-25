/*
 * RegionGrowthLumOrdered.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#include "RegionGrowthLumOrdered.h"
#include <set>
#include "Region.h"

using namespace std;
using namespace cv;

void execRegionGrowthLumOrdered(Mat &srcImg)
{
	RegionGrowthLumOrdered regionGrowthLumOrdered( srcImg );
	regionGrowthLumOrdered.exec();
}

RegionGrowthLumOrdered::~RegionGrowthLumOrdered()
{
}

RegionGrowthLumOrdered::RegionGrowthLumOrdered(Mat &srcImg) :
		_srcImg(srcImg),
		_regionsManager( _srcImg.cols, _srcImg.rows )
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

void RegionGrowthLumOrdered::exec()
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
	}
}

void RegionGrowthLumOrdered::processPoint(const cv::Point &point)
{
	set<Region*> nRegions;

	for(int k(0); k < 8; ++k)
	{
		Point nPoint(point.x + _vX[k], point.y + _vY[k]);
		Region* region = _regionsManager.getRegion( nPoint );
		if( region )
		{
			nRegions.insert( region );
		}
	}

	if( nRegions.size() == 0 )
		_regionsManager.createRegion( point );
	else if ( nRegions.size() == 1 )
		(*(nRegions.begin()))->addPoint( point );
	else
	{
		for( auto &regionL1 : nRegions )
		{
			for( auto &regionL2 : nRegions )
			{
				if(regionL1 == regionL2)
					continue;

				_regionsManager.mergeRegions( regionL1, regionL2, point );
			}
		}
	}
}

