/*
 * PlateLocationWindow.cpp
 *
 *  Created on: 31 de out de 2016
 *      Author: gstiebler
 */

#include "PlateLocationWindow.h"
#include "MainWindow.h"
#include "ImageProcessing/PlateLocation.h"

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
}

PlateLocationWindow::~PlateLocationWindow() {
}

void PlateLocationWindow::getParams(PlateLocationParams &params) {
	params.xOffset = xOffsetSpin->value();
	params.minDifX = minDifSpin->value();
	params.maxDifLateralsProp = maxDifLateralsProp->value();
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
	Mat colorImg;
	cvtColor( outGrayImg, colorImg, CV_GRAY2BGR );
	_windowImages.setDstImage(colorImg);
}
