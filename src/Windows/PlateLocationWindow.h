/*
 * PlateLocationWindow.h
 *
 *  Created on: 31 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_WINDOWS_PLATELOCATIONWINDOW_H_
#define SRC_WINDOWS_PLATELOCATIONWINDOW_H_

#include <QFileDialog>
#include "ui_PlateLocation.h"
#include <opencv2/opencv.hpp>
class WindowImagesInterface;

class PlateLocationWindow : public QDialog, private Ui::PlateLocationWindow {
    Q_OBJECT

public:
	PlateLocationWindow(QWidget *parent, WindowImagesInterface &windowImages);
	virtual ~PlateLocationWindow();

private:

	WindowImagesInterface &_windowImages;
	cv::Mat &_srcImage;

	void execute();
};

#endif /* SRC_WINDOWS_PLATELOCATIONWINDOW_H_ */
