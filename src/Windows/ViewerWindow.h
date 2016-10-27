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
#include "QMouseEventerImage.h"

class ViewerWindow : public QDialog, private Ui::ViewerWindow
{
    Q_OBJECT

public:
	ViewerWindow(QWidget *parent);
	virtual ~ViewerWindow();

public slots:
	void imageChanged(cv::Mat &image);

signals:
	void mousePressed(cv::Point &point);

private:
	void showImage();
	void initializeImageWidget();
	cv::Point windowToImage(const cv::Point &input);
	QMouseEventerImage *imageLabel;
	cv::Mat _srcImage;
};

#endif /* SRC_WINDOWS_VIEWERWINDOW_H_ */
