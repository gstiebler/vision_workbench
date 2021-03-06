/*
 * RegionGrowthWindow.h
 *
 *  Created on: 25 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_WINDOWS_REGIONGROWTHWINDOW_H_
#define SRC_WINDOWS_REGIONGROWTHWINDOW_H_

#include <QFileDialog>
#include "ui_RegionGrowth.h"
#include <opencv2/opencv.hpp>

class WindowImagesInterface;
class Region;
struct RegionsGrowthParams;

class RegionGrowthWindow : public QDialog, private Ui::RegionGrowthWindow
{
    Q_OBJECT

public:
	RegionGrowthWindow(QWidget *parent, WindowImagesInterface &windowImages);
	virtual ~RegionGrowthWindow();

public slots:
	void mousePressed(cv::Point &point);

private:
	WindowImagesInterface &_windowImages;
	cv::Mat &_srcImage;
	cv::Point _pointDebug;

	void getParams(RegionsGrowthParams &params);
	void execute();
	void execWidth();
};

bool shouldStopRegion(RegionsGrowthParams &params, cv::Point &pointDebug, Region &region);
bool mergeRegionsIfNotBig(RegionsGrowthParams &params, cv::Point &pointDebug, std::vector<Region*> &regions);

#endif /* SRC_WINDOWS_REGIONGROWTHWINDOW_H_ */
