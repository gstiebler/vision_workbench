/*
 * RegionGrowthLumOrdered.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#include "RegionGrowthLumOrdered.h"
#include <set>
#include "Region.h"
#include "RegionsManager.h"

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

void RegionGrowthLumOrdered::exec()
{
	initLums(_srcImg);
	char vX[8], vY[8];
	initDirections(vX, vY);
	RegionsManager regionsManager( _srcImg.cols, _srcImg.rows );

	for(int lum(0); lum < 255; ++lum)
	{
		vector<Point> &currentLums = _lums[lum];
		int size = (int) currentLums.size();
		for(int n(0); n < size; ++n)
		{
			Point &point = currentLums[n];
			set<Region*> nRegions;

			bool hadRegionOnLast = false;
			for(int k(0); k < 8; ++k)
			{
				Point nPoint(point.x + vX[k], point.y + vY[k]);
				Region* region = regionsManager.getRegion( nPoint );
				if( region != nullptr )
				{
					if( !hadRegionOnLast )
					{
						nRegions.insert( region );
					}
					hadRegionOnLast = true;
				}
				else
					hadRegionOnLast = false;
			}

			if( nRegions.size() == 0 )
				regionsManager.createRegion( point );
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

						regionsManager.mergeRegions( regionL1, regionL2, point );
					}
				}
			}
		}
	}
}

