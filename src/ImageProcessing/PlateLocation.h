/*
 * PlateLocation.h
 *
 *  Created on: 31 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_IMAGEPROCESSING_PLATELOCATION_H_
#define SRC_IMAGEPROCESSING_PLATELOCATION_H_

#include <opencv2/opencv.hpp>

struct PlateLocationParams {
	int difX;
	int minDif;
};

void platePoints(cv::Mat &inputGrayImg, cv::Mat &outputImg, PlateLocationParams &params);

#endif /* SRC_IMAGEPROCESSING_PLATELOCATION_H_ */
