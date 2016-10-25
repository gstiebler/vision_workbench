/*
 * ThresholdWindow.cpp
 *
 *  Created on: 20 de out de 2016
 *      Author: gstiebler
 */

#include "ThresholdWindow.h"
#include "MainWindow.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "TimeMeasure.h"

using namespace std;
using namespace cv;

ThresholdWindow::ThresholdWindow(QWidget *parent, WindowImagesInterface &windowImages) :
	QDialog(parent),
	_windowImages(windowImages),
	_srcImage(windowImages.getSrcImage())
{
    setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );

    QObject::connect( slider, &QSlider::valueChanged, [this] (int value) {
    	valueLabel->setText(QString::number(value));
    	execute(value);
	});
}

ThresholdWindow::~ThresholdWindow()
{
}

void ThresholdWindow::execute(int thresholdValue) {
	TimeMeasure tm;

	int threshold_type = 0;
	Mat srcGray, dstGray, dstColor;
	cvtColor( _srcImage, srcGray, CV_BGR2GRAY );
	threshold( srcGray, dstGray, thresholdValue, 255, threshold_type );

	vector<Mat> bgr(3);
	//split(_srcImage, bgr);//split source
	bgr[0] = srcGray;
	bgr[1] = dstGray;
	bgr[2] = dstGray;
	merge(bgr, dstColor);

	_windowImages.setStatus(tm.getTime());

	_windowImages.setDstImage(dstColor);
}
