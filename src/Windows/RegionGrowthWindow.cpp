/*
 * RegionGrowthWindow.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#include "RegionGrowthWindow.h"
#include "MainWindow.h"
#include "ImageProcessing/RegionGrowthLumOrdered/RegionGrowthLumOrdered.h"

RegionGrowthWindow::RegionGrowthWindow(QWidget *parent, WindowImagesInterface &windowImages) :
	QDialog(parent),
	_windowImages(windowImages),
	_srcImage(windowImages.getSrcImage())
{
	setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );

    connect( executeButton, &QPushButton::clicked, this, &RegionGrowthWindow::executeClicked );

}

RegionGrowthWindow::~RegionGrowthWindow()
{
}

void RegionGrowthWindow::executeClicked()
{
	execRegionGrowthLumOrdered(_srcImage);
}
