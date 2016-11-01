/*
 * RegionsPainter.cpp
 *
 *  Created on: 26 de out de 2016
 *      Author: gstiebler
 */

#include "RegionsPainter.h"
#include "Region.h"
#include <algorithm>

using namespace std;
using namespace cv;

void paintByHeight(vector<Region*> &regions, Mat &dstImg)
{
	Mat tempGray(dstImg.rows, dstImg.cols, CV_8UC1, Scalar(0));

	int maxHeight = 0;
	int minHeight = dstImg.rows;
	for(auto &region : regions)
	{
		if(!region->isStopped()) continue;
		minHeight = min(minHeight, region->limits.height());
		maxHeight = max(maxHeight, region->limits.height());
	}
	for(auto &region : regions)
	{
		if(!region->isStopped()) continue;
		vector<Point> points;
		region->getPoints(points);
		double factor = 1.0 - ((region->limits.height() - minHeight) * 1.0 / maxHeight) * 0.8;
		uchar p = factor * 255;
		for(auto &point : points)
		{
			tempGray.at<uchar>(point.y, point.x) = p;
		}
	}
	applyColorMap(tempGray, dstImg, COLORMAP_JET);
}
