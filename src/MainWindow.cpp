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

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent)
{
    setupUi(this);

    connect( buttonExecute, SIGNAL( clicked() ), this, SLOT( executeClicked() ) );
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

		Mat image;
		image = imread( dialog.selectedFiles()[0].toLatin1().data(), 1 );
		if ( !image.data )
		{
			printf("No image data \n");
			return;
		}
		setSrcImage(image);
	}
}

void MainWindow::setSrcImage(Mat &image)
{
	QImage srcImage = QImage((const unsigned char*)(image.data),
							image.cols, image.rows,
							image.step, QImage::Format_RGB888).rgbSwapped();

	srcImageLabel->setPixmap(QPixmap::fromImage(srcImage));
	srcImageLabel->show();
}