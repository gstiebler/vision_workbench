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

void platePointsFloat(Mat &inputGrayImg, Mat &outputImg, PlateLocationParams &params) {
	plFunc func = [] (uchar difLeft, uchar difRight, uchar difLaterals) {
		int minDifCenterToLaterals = min(difLeft, difRight);
		int output = minDifCenterToLaterals - difLaterals;
		output = max(output, 0);
		return output;
	};
	platePoints(inputGrayImg, outputImg, params, func);
}

void platePointsBool(Mat &inputGrayImg, Mat &outputImg, PlateLocationParams &params) {
	plFunc func = [params] (uchar difLeft, uchar difRight, uchar difLaterals) {
		int lowestDif = min(difLeft, difRight);
		if(lowestDif < params.minDifX) return 0;
		int maxDifLaterals = params.maxDifLateralsProp * lowestDif;
		if(difLaterals > maxDifLaterals) return 0;
		return 255;
	};
	platePoints(inputGrayImg, outputImg, params, func);
}

void platePoints(Mat &inputGrayImg, Mat &outputImg, PlateLocationParams &params, plFunc func) {
	outputImg.resize(inputGrayImg.rows, inputGrayImg.cols - params.xOffset * 2);

	for(int y(0); y < outputImg.rows; ++y) {
		for(int x(0); x < outputImg.cols; ++x) {
			int xInput = x + params.xOffset;
			uchar inputCenter = inputGrayImg.at<uchar>(y, xInput);
			uchar inputLeft = inputGrayImg.at<uchar>(y, xInput - params.xOffset);
			uchar inputRight = inputGrayImg.at<uchar>(y, xInput + params.xOffset);
			int difLeft = inputLeft - inputCenter;
			difLeft = max(difLeft, 0);
			int difRight = inputRight - inputCenter;
			difRight = max(difRight, 0);
			int difLaterals = abs((int)inputLeft - inputRight);
			int output = func(difLeft, difRight, difLaterals);
			outputImg.at<uchar>(y, x) = output;
		}
	}
}
