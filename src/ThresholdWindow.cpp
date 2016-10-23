/*
 * ThresholdWindow.cpp
 *
 *  Created on: 20 de out de 2016
 *      Author: gstiebler
 */

#include "ThresholdWindow.h"
#include "MainWindow.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

ThresholdWindow::ThresholdWindow(QWidget *parent, WindowImagesInterface &windowImages) :
	QDialog(parent),
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

void ThresholdWindow::execute(int threshold) {
	Mat srcGray;
	cvtColor( _srcImage, srcGray, CV_BGR2GRAY );
}
