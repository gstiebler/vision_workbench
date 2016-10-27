/*
 * MainWindow.cpp
 *
 *  Created on: 18/10/2014
 *      Author: Guilherme
 */

#include "MainWindow.h"
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <QMouseEvent>
#include "VideoWindow.h"
#include "ThresholdWindow.h"
#include "FilesWindow.h"
#include "RegionGrowthWindow.h"
#include "ViewerWindow.h"

using namespace std;
using namespace cv;

static void SetLabelImage(QLabel *label, QPixmap &pixmap, int height)
{
    pixmap = pixmap.scaledToHeight(height, Qt::SmoothTransformation);
    label->setPixmap(pixmap);
    label->show();
}

MainWindow::MainWindow(string initialImage)
{
    setupUi(this);
    srcImageLabel = initializeImageWidget("srcImage", 0);
    dstImageLabel = initializeImageWidget("dstImage", 1);

    connect( buttonExecute, SIGNAL( clicked() ), this, SLOT( executeClicked() ) );

    QObject::connect( srcImageLabel, &QMouseEventerImage::mousePressed, [this] (QMouseEvent *event) {
    	ViewerWindow *window = new ViewerWindow(this);
        connect( this, &MainWindow::srcImageChanged, window, &ViewerWindow::imageChanged );
    	emit srcImageChanged(_srcImage);
		window->show();
	});

    QObject::connect( dstImageLabel, &QMouseEventerImage::mousePressed, [this] (QMouseEvent *event) {
    	ViewerWindow *window = new ViewerWindow(this);
        connect( this, &MainWindow::dstImageChanged, window, &ViewerWindow::imageChanged );
    	emit dstImageChanged(_dstImage);
		window->show();
	});

    QObject::connect( videoWindowButton, &QPushButton::clicked, [this] () {
		VideoWindow *window = new VideoWindow(this, this);
		window->show();
	});

    QObject::connect( thresholdButton, &QPushButton::clicked, [this] () {
    	ThresholdWindow *window = new ThresholdWindow(this, *this);
		window->show();
	});

    QObject::connect( filesWindowButton, &QPushButton::clicked, [this] () {
    	FilesWindow *window = new FilesWindow(this, *this);
		window->show();
	});

    QObject::connect( regionGrowthWindowButton, &QPushButton::clicked, [this] () {
    	RegionGrowthWindow *window = new RegionGrowthWindow(this, *this);
		window->show();
	});

    QObject::connect( colorMapButton, &QPushButton::clicked, [this] () {
    	Mat grayImage, dstImage;
    	Mat ones(_srcImage.rows, _srcImage.cols, CV_8UC1, Scalar(255));
    	cvtColor( _srcImage, grayImage, CV_BGR2GRAY );
    	grayImage = ones - grayImage;
    	applyColorMap(grayImage, dstImage, COLORMAP_JET);
    	setDstImage(dstImage);
	});

    if(initialImage != "")
    {
		Mat srcImage = imread( initialImage.c_str(), 1 );
		setSrcImage(srcImage);
    }
}

MainWindow::~MainWindow()
{
}

QMouseEventerImage* MainWindow::initializeImageWidget(QString name, int index)
{
	QMouseEventerImage *mei = new QMouseEventerImage(centralwidget);
	mei->setObjectName(name);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(mei->sizePolicy().hasHeightForWidth());
    mei->setSizePolicy(sizePolicy);
    mei->setMinimumSize(QSize(0, 400));
    mei->setScaledContents(false);
    verticalLayout->insertWidget(index, mei);
    return mei;
}

void MainWindow::executeClicked()
{
	QFileDialog dialog(NULL);
	if ( dialog.exec() ) 
	{
		Mat srcImage = imread( dialog.selectedFiles()[0].toLatin1().data(), 1 );
		if ( !srcImage.data )
		{
			printf("No image data \n");
			return;
		}
		setSrcImage(srcImage);
	}
}

void MainWindow::setSrcImage(Mat &image)
{
	_srcImage = image;
	QImage srcImage = QImage((const unsigned char*)(image.data),
							image.cols, image.rows,
							image.step, QImage::Format_RGB888).rgbSwapped();

	QPixmap pixmap = QPixmap::fromImage(srcImage);
	SetLabelImage(srcImageLabel, pixmap, srcImageLabel->minimumHeight());
	char status[100];
	sprintf(status, "%d x %d", image.rows, image.cols);
	setStatus(status);
	emit srcImageChanged(_srcImage);
}

void MainWindow::setDstImage(Mat &image)
{
	QImage dstImage = QImage((const unsigned char*)(image.data),
							image.cols, image.rows,
							image.step, QImage::Format_RGB888).rgbSwapped();

	QPixmap pixmap = QPixmap::fromImage(dstImage);
	SetLabelImage(dstImageLabel, pixmap, dstImageLabel->minimumHeight());
	emit dstImageChanged(image);
	_dstImage = image;
}

cv::Mat& MainWindow::getSrcImage()
{
	return _srcImage;
}

void MainWindow::setStatus(std::string status)
{
	statusBar()->showMessage(tr(status.c_str()));
}
