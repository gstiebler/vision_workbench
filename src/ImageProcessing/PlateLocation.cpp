/*
 * PlateLocation.cpp
 *
 *  Created on: 31 de out de 2016
 *      Author: gstiebler
 */

#include "PlateLocation.h"
#include <algorithm>

using namespace std;
using namespace cv;

void platePoints(Mat &inputGrayImg, Mat &outputImg, PlateLocationParams &params) {
	outputImg.resize(inputGrayImg.rows, inputGrayImg.cols - params.difX * 2);

	for(int y(0); y < outputImg.rows; ++y) {
		for(int x(0); x < outputImg.cols; ++x) {
			if(x == 520 && y == 980) {
				int x = 5;
			}
			int xInput = x + params.difX;
			uchar inputCenter = inputGrayImg.at<uchar>(y, xInput);
			uchar inputLeft = inputGrayImg.at<uchar>(y, xInput - params.difX);
			uchar inputRight = inputGrayImg.at<uchar>(y, xInput + params.difX);
			int difLeft = inputLeft - inputCenter;
			difLeft = max(difLeft, 0);
			int difRight = inputRight - inputCenter;
			difRight = max(difRight, 0);
			int minDifCenterToLaterals = min(difLeft, difRight);
			int difLaterals = abs((int)inputLeft - inputRight);
			int output = minDifCenterToLaterals - difLaterals;
			output = max(output, 0);
			outputImg.at<uchar>(y, x) = output;
		}
	}
}
