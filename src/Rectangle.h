/*
 * Rectangle.h
 *
 *  Created on: 27 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_RECTANGLE_H_
#define SRC_RECTANGLE_H_

#include <opencv2/opencv.hpp>

struct Rectangle
{
	int xMin, xMax, yMin, yMax;

	void merge(const Rectangle &other);
	void addPoint(const cv::Point &point);
	int width() const;
	int height() const;
	bool isInside(const cv::Point &point) const;
	std::string toString();
};

#endif /* SRC_RECTANGLE_H_ */
