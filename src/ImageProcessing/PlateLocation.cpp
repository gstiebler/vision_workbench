/*
 * PlateLocation.cpp
 *
 *  Created on: 31 de out de 2016
 *      Author: gstiebler
 */

#include "PlateLocation.h"
#include <algorithm>
#include "Rectangle.h"

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
		return 1;
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

void subSum(Mat &inputGrayImg, Mat &outputImg, PlateLocationParams &params) {
	Mat rowSum(inputGrayImg.rows, inputGrayImg.cols - params.plateWidth + 1, CV_32SC1, Scalar(0));
	for(int y(0); y < inputGrayImg.rows; ++y) {
		int sum = 0;
		for(int x(0); x < params.plateWidth; ++x) {
			sum += inputGrayImg.at<uchar>(y, x);
		}
		rowSum.at<uint>(y, 0) = sum;

		for(int x(params.plateWidth); x < inputGrayImg.cols; ++x) {
			sum -= inputGrayImg.at<uchar>(y, x - params.plateWidth);
			sum += inputGrayImg.at<uchar>(y, x);
			rowSum.at<uint>(y, x - params.plateWidth + 1) = sum;
		}
	}

	outputImg.resize(rowSum.rows - params.plateHeight + 1, rowSum.cols);
	//Mat colSum(rowSum.rows - params.plateHeight + 1, rowSum.cols, CV_32SC1, Scalar(0));
	for(int x(0); x < rowSum.cols; ++x) {
		int sum = 0;
		for(int y(0); y < params.plateHeight; ++y) {
			sum += rowSum.at<uint>(y, x);
		}
		outputImg.at<uint>(0, x) = sum;

		for(int y(params.plateHeight); y < outputImg.rows; ++y) {
			sum -= rowSum.at<uint>(y - params.plateHeight, x);
			sum += rowSum.at<uint>(y, x);
			outputImg.at<uint>(y - params.plateHeight / 2 + 1, x + params.plateWidth / 2) = sum;
		}
	}
}

void regions(cv::Mat &sumMat, std::vector<cv::Rect> &plateLocations, PlateLocationParams &params) {
	for(int n(0); n < params.numRegions; ++n) {
		Point maxLoc;
		minMaxLoc(sumMat, nullptr, nullptr, nullptr, &maxLoc);
		Rect region(maxLoc.x - params.plateWidth / 2, maxLoc.y - params.plateHeight / 2, params.plateWidth, params.plateHeight);
		plateLocations.push_back(region);

		Rectangle extRegion({maxLoc.x - params.plateWidth, maxLoc.x + params.plateWidth, maxLoc.y - params.plateHeight, maxLoc.y + params.plateHeight});
		extRegion.xMin = max(extRegion.xMin, 0);
		extRegion.yMin = max(extRegion.yMin, 0);
		extRegion.xMax = min(extRegion.xMax, sumMat.rows - 1);
		extRegion.yMax = min(extRegion.yMax, sumMat.cols - 1);
		Mat pRoi = sumMat(Rect(extRegion.xMin, extRegion.yMin, extRegion.width(), extRegion.height()));
		pRoi.setTo(cv::Scalar(0));
	}
}
