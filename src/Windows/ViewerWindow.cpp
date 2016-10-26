/*
 * ViewerWindow.cpp
 *
 *  Created on: 26 de out de 2016
 *      Author: gstiebler
 */

#include "ViewerWindow.h"

#include "MainWindow.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

ViewerWindow::ViewerWindow(QWidget *parent, WindowImagesInterface &windowImages) :
	QDialog(parent),
	_windowImages(windowImages),
	_srcImage(windowImages.getSrcImage())
{
    setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );

	QImage srcImage = QImage((const unsigned char*)(_srcImage.data),
			_srcImage.cols, _srcImage.rows,
			_srcImage.step, QImage::Format_RGB888).rgbSwapped();

	QPixmap pixmap = QPixmap::fromImage(srcImage);
	imageLabel->setPixmap(pixmap);
	imageLabel->show();
}

ViewerWindow::~ViewerWindow()
{
}

