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

    connect( executeButton, &QPushButton::clicked, this, &PlateLocationWindow::execute );
}

PlateLocationWindow::~PlateLocationWindow() {
}


void PlateLocationWindow::execute()
{
	PlateLocationParams params;
	params.difX = difXSpin->value();
	params.minDif = maxDifSpin->value();

	Mat inputGray;
	cvtColor( _srcImage, inputGray, CV_BGR2GRAY );
	Mat outGrayImg(_srcImage.rows, _srcImage.cols, CV_8UC1);
	platePoints(inputGray, outGrayImg, params);
	Mat ones(_srcImage.rows, _srcImage.cols, CV_8UC1, 255);
	outGrayImg = ones - outGrayImg;
	Mat colorImg;
	cvtColor( outGrayImg, colorImg, CV_GRAY2BGR );
	_windowImages.setDstImage(colorImg);
}
