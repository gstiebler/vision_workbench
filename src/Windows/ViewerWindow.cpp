/*
 * ViewerWindow.cpp
 *
 *  Created on: 26 de out de 2016
 *      Author: gstiebler
 */

#include "ViewerWindow.h"

using namespace std;
using namespace cv;

ViewerWindow::ViewerWindow(QWidget *parent) :
	QDialog(parent)
{
    setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );

	/*int originalWidth = imageLabel->width();
	int originalHeight = imageLabel->height();*/

    QObject::connect( zoomSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=] (int value) {
    	showImage();
	});
}

ViewerWindow::~ViewerWindow()
{
}

void ViewerWindow::showImage()
{
	Mat dstImg;
	int zoomFactor = zoomSpinBox->value();
	cv::resize(_srcImage, dstImg, Size(), (double)zoomFactor, (double)zoomFactor, INTER_NEAREST);
	QImage srcImage = QImage((const unsigned char*)(dstImg.data),
			dstImg.cols, dstImg.rows,
			dstImg.step, QImage::Format_RGB888).rgbSwapped();

	QPixmap pixmap = QPixmap::fromImage(srcImage);
	imageLabel->setPixmap(pixmap);
	imageLabel->show();
}

void ViewerWindow::imageChanged(cv::Mat &image)
{
	_srcImage = image;
	showImage();
}
