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

class ViewerWindow : public QDialog, private Ui::ViewerWindow
{
    Q_OBJECT

public:
	ViewerWindow(QWidget *parent);
	virtual ~ViewerWindow();

public slots:
	void imageChanged(cv::Mat &image);
};

#endif /* SRC_WINDOWS_VIEWERWINDOW_H_ */
