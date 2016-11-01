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

void RegionGrowthWindow::getParams(RegionsGrowthParams &params) {
	params.difHeightHistoryIndex = difIndexHeightSpin->value();
	params.minHeight = minHeightSpin->value();
	params.maxHeightFactor = maxHeightFactorSpin->value();
	params.maxLum = maxLumSpin->value();
}

void RegionGrowthWindow::execute()
{
	RegionsGrowthParams params;
	getParams(params);
	TimeMeasure tm;
	Mat srcGray;
	cvtColor( _srcImage, srcGray, CV_BGR2GRAY );
	printf("Debug point: (%d, %d)\n", _pointDebug.x, _pointDebug.y);
	RegionsManager regionsManager(_srcImage.cols, _srcImage.rows);
	regionsManager.shouldStopRegionFn = [this, params] (Region &region) {
		if((region.rectHistory.size() < params.difHeightHistoryIndex) ||
		   (region.limits.height() < params.minHeight))
		{
			return false;
		}
		Rectangle &currRect = region.rectHistory.back();
		Rectangle &oldRect = region.rectHistory[region.rectHistory.size() - params.difHeightHistoryIndex];
		double heightFactor = currRect.height() * 1.0 / oldRect.height();
		bool hasHeightFactor = heightFactor < params.maxHeightFactor;
		bool hasRightProportion = region.limits.height() > region.limits.width();

		if(region.limits.isInside(_pointDebug))
		{
			printf("id: %d, oldHeight: %d, newHeight: %d, numHeights: %ld, numPoints: %ld, xMin: %d, xMax: %d, yMin: %d, yMax: %d\n",
					region.id,
					oldRect.height(),
					currRect.height(),
					region.rectHistory.size(),
					region.points.size(),
					region.limits.xMin,
					region.limits.xMax,
					region.limits.yMin,
					region.limits.yMax);
		}

		return hasHeightFactor && hasRightProportion;
	};
	RegionGrowthLumOrdered regionGrowthLumOrdered( srcGray, regionsManager );
	RegionsAnalyzer regionsAnalyzer(_srcImage.rows);
	regionGrowthLumOrdered.exec(params.maxLum, nullptr);
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
