/*
 * MainWindow.h
 *
 *  Created on: 18/10/2014
 *      Author: Guilherme
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <QString>
#include "ui_MainWindow.h"
#include <string>
#include <opencv2/opencv.hpp>
#include "QMouseEventerImage.h"

class WindowImagesInterface
{
public:
	virtual void setSrcImage(cv::Mat &image) = 0;
	virtual void setDstImage(cv::Mat &image) = 0;
	virtual cv::Mat& getSrcImage() = 0;
	virtual void setStatus(std::string status) = 0;
};

class MainWindow : public QMainWindow, private Ui::MainWindow, public WindowImagesInterface
{
    Q_OBJECT

public:
    MainWindow(std::string initialImage);
    virtual ~MainWindow();

	void setSrcImage(cv::Mat &image);
	void setDstImage(cv::Mat &image);
	cv::Mat& getSrcImage();
	void setStatus(std::string status);

signals:
	void srcImageChanged(cv::Mat &image);
	void dstImageChanged(cv::Mat &image);
	void mousePressedOnViewerWindow(cv::Point &point);

private slots:

	void executeClicked();

private:
	QMouseEventerImage* initializeImageWidget(QString name, int index);
	QMouseEventerImage *srcImageLabel;
	QMouseEventerImage *dstImageLabel;
	cv::Mat _srcImage;
	cv::Mat _dstImage;

};

#endif /* MAINWINDOW_H_ */
