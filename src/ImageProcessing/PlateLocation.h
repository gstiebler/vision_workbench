/*
 * PlateLocation.h
 *
 *  Created on: 31 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_IMAGEPROCESSING_PLATELOCATION_H_
#define SRC_IMAGEPROCESSING_PLATELOCATION_H_

#include <opencv2/opencv.hpp>
#include <functional>

struct PlateLocationParams {
	int difX;
	int minDif;
};

typedef std::function<float(uchar difLeft, uchar difRight, uchar difLaterals)> plFunc;


void platePointsFloat(cv::Mat &inputGrayImg, cv::Mat &outputImg, PlateLocationParams &params);
void platePoints(cv::Mat &inputGrayImg, cv::Mat &outputImg, PlateLocationParams &params, plFunc func);

#endif /* SRC_IMAGEPROCESSING_PLATELOCATION_H_ */
