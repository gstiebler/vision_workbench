/*
 * RegionGrowthWindow.cpp
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#include "RegionGrowthWindow.h"
#include "MainWindow.h"
#include "ImageProcessing/RegionGrowthLumOrdered/RegionGrowthLumOrdered.h"
#include "ImageProcessing/RegionGrowthLumOrdered/RegionsAnalyzer.h"
#include "ImageProcessing/RegionGrowthLumOrdered/Region.h"
#include "TimeMeasure.h"

using namespace cv;

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
	TimeMeasure tm;
	const int DIF_HEIGHT_HISTORY_INDEX = difIndexHeightSpin->value();
	const int MIN_HEIGHT = minHeightSpin->value();
	const double MAX_HEIGHT_FACTOR = maxHeightFactorSpin->value();
	Mat srcGray;
	cvtColor( _srcImage, srcGray, CV_BGR2GRAY );
	RegionsManager regionsManager(_srcImage.cols, _srcImage.rows);
	regionsManager.shouldStopRegionFn = [DIF_HEIGHT_HISTORY_INDEX, MIN_HEIGHT, MAX_HEIGHT_FACTOR] (Region &region) {
		if((region.heightHistory.size() < DIF_HEIGHT_HISTORY_INDEX) ||
		   (region.height() < MIN_HEIGHT))
		{
			return false;
		}
		int currHeight = region.heightHistory.back();
		int oldHeight = region.heightHistory[region.heightHistory.size() - DIF_HEIGHT_HISTORY_INDEX];
		double heighFactor = currHeight * 1.0 / oldHeight;
		return heighFactor < MAX_HEIGHT_FACTOR;
	};
	RegionGrowthLumOrdered regionGrowthLumOrdered( srcGray, regionsManager );
	RegionsAnalyzer regionsAnalyzer(_srcImage.rows);
	regionGrowthLumOrdered.exec(nullptr);
	_windowImages.setStatus(tm.getTime());
}
