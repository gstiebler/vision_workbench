/*
 * PlateLocationWindow.cpp
 *
 *  Created on: 31 de out de 2016
 *      Author: gstiebler
 */

#include "PlateLocationWindow.h"
#include "MainWindow.h"
#include "ImageProcessing/PlateLocation.h"
#include "TimeMeasure.h"

using namespace std;
using namespace cv;

PlateLocationWindow::PlateLocationWindow(QWidget *parent, WindowImagesInterface &windowImages) :
	QDialog(parent),
	_windowImages(windowImages),
	_srcImage(windowImages.getSrcImage())
{
	setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );

    connect( executeFloatButton, &QPushButton::clicked, this, &PlateLocationWindow::executeFloat );
    connect( executeBoolButton, &QPushButton::clicked, this, &PlateLocationWindow::executeBool );
    connect( executeSumButton, &QPushButton::clicked, this, &PlateLocationWindow::executeSum );
}

PlateLocationWindow::~PlateLocationWindow() {
}

void PlateLocationWindow::getParams(PlateLocationParams &params) {
	params.xOffset = xOffsetSpin->value();
	params.minDifX = minDifSpin->value();
	params.maxDifLateralsProp = maxDifLateralsProp->value();
	params.plateWidth = plateWidthSpin->value();
	params.plateHeight = plateHeightSpin->value();
}

void PlateLocationWindow::executeFloat() {
	PlateLocationParams params;
	getParams(params);

	Mat inputGray;
	cvtColor( _srcImage, inputGray, CV_BGR2GRAY );
	Mat outGrayImg(_srcImage.rows, _srcImage.cols, CV_8UC1);
	platePointsFloat(inputGray, outGrayImg, params);
	Mat ones(_srcImage.rows, _srcImage.cols, CV_8UC1, 255);
	outGrayImg = ones - outGrayImg;
	Mat colorImg;
	cvtColor( outGrayImg, colorImg, CV_GRAY2BGR );
	_windowImages.setDstImage(colorImg);
}

void PlateLocationWindow::executeBool() {
	PlateLocationParams params;
	getParams(params);

	Mat inputGray;
	cvtColor( _srcImage, inputGray, CV_BGR2GRAY );
	Mat outGrayImg(_srcImage.rows, _srcImage.cols, CV_8UC1);
	platePointsBool(inputGray, outGrayImg, params);
	outGrayImg *= 255;

	Mat colorImg;
	cvtColor( outGrayImg, colorImg, CV_GRAY2BGR );
	_windowImages.setDstImage(colorImg);
}

void PlateLocationWindow::executeSum() {
	PlateLocationParams params;
	getParams(params);

	Mat inputGray;
	cvtColor( _srcImage, inputGray, CV_BGR2GRAY );
	Mat platePointsImg(_srcImage.rows, _srcImage.cols, CV_8UC1);
	TimeMeasure tm;
	platePointsBool(inputGray, platePointsImg, params);

	Mat sumMat(_srcImage.rows, _srcImage.cols, CV_32SC1, Scalar(0));
	subSum(platePointsImg, sumMat, params);
	_windowImages.setStatus(tm.getTime());
	double maxValue;
	minMaxLoc(sumMat, 0, &maxValue);

	Mat outGrayImg;
	sumMat.convertTo(outGrayImg, CV_8UC1, 255.0 / maxValue);

	Mat colorImg;
	applyColorMap(outGrayImg, colorImg, COLORMAP_JET);
	_windowImages.setDstImage(colorImg);
}
