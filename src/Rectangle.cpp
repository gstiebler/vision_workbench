/*
 * Rectangle.cpp
 *
 *  Created on: 27 de out de 2016
 *      Author: gstiebler
 */

#include "Rectangle.h"
#include <algorithm>

using namespace std;
using namespace cv;

void Rectangle::merge(const Rectangle &other)
{
	xMin = min(other.xMin, xMin);
	xMax = max(other.xMax, xMax);
	yMin = min(other.yMin, yMin);
	yMax = max(other.yMax, yMax);
}

void Rectangle::addPoint(const cv::Point &point)
{
	xMin = min(point.x, xMin);
	xMax = max(point.x, xMax);
	yMin = min(point.y, yMin);
	yMax = max(point.y, yMax);
}

int Rectangle::width() const
{
	return xMax - xMin + 1;
}

int Rectangle::height() const
{
	return yMax - yMin + 1;
}

bool Rectangle::isInside(const cv::Point &point) const
{
	return (point.x >= xMin) &&
	   (point.x <= xMax) &&
	   (point.y >= yMin) &&
	   (point.y <= yMax);
}

std::string Rectangle::toString()
{
	char result[100];
	sprintf(result, "(%d, %d), (%d, %d)", xMin, xMax, yMin, yMax);
	return result;
}
