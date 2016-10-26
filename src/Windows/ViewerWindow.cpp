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
}

ViewerWindow::~ViewerWindow()
{
}

void ViewerWindow::imageChanged(cv::Mat &image)
{
	QImage srcImage = QImage((const unsigned char*)(image.data),
			image.cols, image.rows,
			image.step, QImage::Format_RGB888).rgbSwapped();

	QPixmap pixmap = QPixmap::fromImage(srcImage);
	imageLabel->setPixmap(pixmap);
	imageLabel->show();
}
