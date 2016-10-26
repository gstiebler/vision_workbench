/*
 * RegionsPainter.cpp
 *
 *  Created on: 26 de out de 2016
 *      Author: gstiebler
 */

#include "RegionsPainter.h"
#include "Region.h"

using namespace std;
using namespace cv;

void paintByHeight(vector<Region*> &regions, Mat &dstImg)
{
	Mat tempGray(dstImg.rows, dstImg.cols, CV_8UC1, Scalar(0));
	for(auto &region : regions)
	{
		vector<Point> points;
		region->getPoints(points);
		double factor = region->height() * 1.0 / dstImg.rows;
		uchar p = factor * 255;
		for(auto &point : points)
		{
			tempGray.at<uchar>(point.y, point.x) = p;
		}
	}
	applyColorMap(tempGray, dstImg, COLORMAP_JET);
}
