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
#include "ImageProcessing/RegionGrowthLumOrdered/RegionsPainter.h"
#include "TimeMeasure.h"
#include <QMouseEvent>

using namespace cv;

RegionGrowthWindow::RegionGrowthWindow(QWidget *parent, WindowImagesInterface &windowImages) :
	QDialog(parent),
	_windowImages(windowImages),
	_srcImage(windowImages.getSrcImage()),
	_pointDebug(-1, -1)
{
	setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );

    connect( executeButton, &QPushButton::clicked, this, &RegionGrowthWindow::execute );

}

RegionGrowthWindow::~RegionGrowthWindow()
{
}

void RegionGrowthWindow::execute()
{
	TimeMeasure tm;
	const int DIF_HEIGHT_HISTORY_INDEX = difIndexHeightSpin->value();
	const int MIN_HEIGHT = minHeightSpin->value();
	const double MAX_HEIGHT_FACTOR = maxHeightFactorSpin->value();
	const int MAX_LUM = maxLumSpin->value();
	Mat srcGray;
	cvtColor( _srcImage, srcGray, CV_BGR2GRAY );
	printf("Debug point: (%d, %d)\n", _pointDebug.x, _pointDebug.y);
	RegionsManager regionsManager(_srcImage.cols, _srcImage.rows);
	regionsManager.shouldStopRegionFn = [this, DIF_HEIGHT_HISTORY_INDEX, MIN_HEIGHT, MAX_HEIGHT_FACTOR, MAX_LUM] (Region &region) {
		if((region.heightHistory.size() < DIF_HEIGHT_HISTORY_INDEX) ||
		   (region.height() < MIN_HEIGHT))
		{
			return false;
		}
		int currHeight = region.heightHistory.back();
		int oldHeight = region.heightHistory[region.heightHistory.size() - DIF_HEIGHT_HISTORY_INDEX];
		double heightFactor = currHeight * 1.0 / oldHeight;
		bool hasHeightFactor = heightFactor < MAX_HEIGHT_FACTOR;
		bool hasRightProportion = region.height() > region.width();


		if((_pointDebug.x >= region.xMin) &&
		   (_pointDebug.x <= region.xMax) &&
		   (_pointDebug.y >= region.yMin) &&
		   (_pointDebug.y <= region.yMax))
		{
			printf("id: %d, heightFactor: %lf, numHeights: %ld, numPoints: %ld, xMin: %d, xMax: %d, yMin: %d, yMax: %d\n", region.id, heightFactor,
					region.heightHistory.size(),
					region.points.size(),
					region.xMin,
					region.xMax,
					region.yMin,
					region.yMax);
		}

		return hasHeightFactor && hasRightProportion;
	};
	RegionGrowthLumOrdered regionGrowthLumOrdered( srcGray, regionsManager );
	RegionsAnalyzer regionsAnalyzer(_srcImage.rows);
	regionGrowthLumOrdered.exec(MAX_LUM, nullptr);
	_windowImages.setStatus(tm.getTime());

	Mat dstColor(_srcImage.rows, _srcImage.cols, CV_8UC3, Scalar(0, 0, 0));
	paintByHeight(regionsManager.stoppedRegions, dstColor);

	_windowImages.setDstImage(dstColor);
}

void RegionGrowthWindow::mousePressed(cv::Point &point)
{
	_pointDebug = point;
	execute();
}
