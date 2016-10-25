/*
 * MainWindow.h
 *
 *  Created on: 18/10/2014
 *      Author: Guilherme
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include "ui_MainWindow.h"
#include <string>
#include <opencv2/opencv.hpp>

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

private slots:

	void executeClicked();

private:

	cv::Mat _srcImage;

};

#endif /* MAINWINDOW_H_ */
