/*
 * ViewerWindow.h
 *
 *  Created on: 26 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_WINDOWS_VIEWERWINDOW_H_
#define SRC_WINDOWS_VIEWERWINDOW_H_

#include <QFileDialog>
#include "ui_Viewer.h"
#include <opencv2/opencv.hpp>

class WindowImagesInterface;

class ViewerWindow : public QDialog, private Ui::ViewerWindow
{
    Q_OBJECT

public:
	ViewerWindow(QWidget *parent, WindowImagesInterface &windowImages);
	virtual ~ViewerWindow();

private:

	WindowImagesInterface &_windowImages;
	cv::Mat &_srcImage;
};

#endif /* SRC_WINDOWS_VIEWERWINDOW_H_ */
