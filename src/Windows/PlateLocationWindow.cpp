/*
 * PlateLocationWindow.cpp
 *
 *  Created on: 31 de out de 2016
 *      Author: gstiebler
 */

#include "PlateLocationWindow.h"
#include "MainWindow.h"

PlateLocationWindow::PlateLocationWindow(QWidget *parent, WindowImagesInterface &windowImages) :
	QDialog(parent),
	_windowImages(windowImages),
	_srcImage(windowImages.getSrcImage())
{
	setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );
}

PlateLocationWindow::~PlateLocationWindow() {
}

