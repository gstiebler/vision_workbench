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

class RegionGrowthWindow : public QDialog, private Ui::RegionGrowthWindow
{
    Q_OBJECT

public:
	RegionGrowthWindow(QWidget *parent, WindowImagesInterface &windowImages);
	virtual ~RegionGrowthWindow();

private:
	WindowImagesInterface &_windowImages;
	cv::Mat &_srcImage;

	void executeClicked();
};

#endif /* SRC_WINDOWS_REGIONGROWTHWINDOW_H_ */
