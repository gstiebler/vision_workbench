/*
 * RegionGrowthWindow.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#include "RegionGrowthWindow.h"
#include "MainWindow.h"

RegionGrowthWindow::RegionGrowthWindow(QWidget *parent, WindowImagesInterface &windowImages) :
	QDialog(parent),
	_windowImages(windowImages),
	_srcImage(windowImages.getSrcImage())
{
	setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );

}

RegionGrowthWindow::~RegionGrowthWindow()
{
}

