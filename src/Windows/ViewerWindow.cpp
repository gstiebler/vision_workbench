/*
 * ViewerWindow.cpp
 *
 *  Created on: 26 de out de 2016
 *      Author: gstiebler
 */

#include "ViewerWindow.h"
#include <QMouseEvent>

using namespace std;
using namespace cv;

ViewerWindow::ViewerWindow(QWidget *parent) :
	QDialog(parent)
{
    setupUi(this);
    initializeImageWidget();
	setAttribute( Qt::WA_DeleteOnClose );

    QObject::connect( zoomSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=] (int value) {
    	showImage();
	});

    QObject::connect( imageLabel, &QMouseEventerImage::mouseMoved, [this] (QMouseEvent *event) {
    	auto point = windowToImage(Point(event->pos().x(), event->pos().y()));
    	auto text = QString().sprintf("Coords: (%d, %d)", point.x, point.y);
    	coordsLabel->setText(text);

    	auto pixel = _srcImage.at<Vec3b>(point.y, point.x);
    	rgbLabel->setText(QString().sprintf("RGB: (%d, %d, %d)", pixel[2], pixel[1], pixel[0]));
	});

    QObject::connect( imageLabel, &QMouseEventerImage::mousePressed, [=] (QMouseEvent *event) {
    	auto point = windowToImage(Point(event->pos().x(), event->pos().y()));
    	emit mousePressed(point);
    });
}

ViewerWindow::~ViewerWindow()
{
}

void ViewerWindow::initializeImageWidget()
{
    imageLabel = new QMouseEventerImage(scrollAreaWidgetContents);
    imageLabel->setObjectName(QStringLiteral("imageLabel"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
    imageLabel->setSizePolicy(sizePolicy);
    imageLabel->setMinimumSize(QSize(0, 0));

    verticalLayout_3->addWidget(imageLabel);
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

Point ViewerWindow::windowToImage(const Point &input)
{
	int zoomFactor = zoomSpinBox->value();
	int imgX = input.x / zoomFactor;
	int imgY = input.y / zoomFactor;
	return Point(imgX, imgY);
}
