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
#include "VideoWindow.h"
#include "ThresholdWindow.h"

using namespace std;
using namespace cv;

static void SetLabelImage(QLabel *label, QPixmap &pixmap, int height)
{
    pixmap = pixmap.scaledToHeight(height, Qt::SmoothTransformation);
    label->setPixmap(pixmap);
    label->show();
}

MainWindow::MainWindow(QWidget *parent)
{
    setupUi(this);

    connect( buttonExecute, SIGNAL( clicked() ), this, SLOT( executeClicked() ) );

    QObject::connect( videoWindowButton, &QPushButton::clicked, [this] () {
		VideoWindow *window = new VideoWindow(this, this);
		window->show();
	});

    QObject::connect( thresholdButton, &QPushButton::clicked, [this] () {
    	ThresholdWindow *window = new ThresholdWindow(this, *this);
		window->show();
	});


    //connect( btInputDirectory, SIGNAL( clicked() ), this, SLOT( selectFolder() ) );
	//connect( menuSobre, SIGNAL(aboutToShow()), this, SLOT(aboutClicked()) );
}

MainWindow::~MainWindow()
{
}

void MainWindow::executeClicked()
{
	QFileDialog dialog(NULL);
	if ( dialog.exec() ) 
	{
		printf("teste: %s\n", dialog.selectedFiles()[0].toLatin1().data());

		_srcImage = imread( dialog.selectedFiles()[0].toLatin1().data(), 1 );
		if ( !_srcImage.data )
		{
			printf("No image data \n");
			return;
		}
		setSrcImage(_srcImage);
	}
}

void MainWindow::setSrcImage(Mat &image)
{
	QImage srcImage = QImage((const unsigned char*)(image.data),
							image.cols, image.rows,
							image.step, QImage::Format_RGB888).rgbSwapped();

	QPixmap pixmap = QPixmap::fromImage(srcImage);
	SetLabelImage(srcImageLabel, pixmap, srcImageLabel->minimumHeight());
}

void MainWindow::setDstImage(Mat &image)
{
	QImage dstImage = QImage((const unsigned char*)(image.data),
							image.cols, image.rows,
							image.step, QImage::Format_RGB888).rgbSwapped();

	QPixmap pixmap = QPixmap::fromImage(dstImage);
	SetLabelImage(dstImageLabel, pixmap, dstImageLabel->minimumHeight());
}

cv::Mat& MainWindow::getSrcImage()
{
	return _srcImage;
}
