/*
 * MainWindow.h
 *
 *  Created on: 18/10/2014
 *      Author: Guilherme
 */

#ifndef VIDEO_WINDOW_H_
#define VIDEO_WINDOW_H_

#include <QDialog>
#include "ui_Video.h"
#include <string>
#include <opencv2/opencv.hpp>
#include <memory>

class WindowImagesInterface;

class VideoWindow : public QDialog, private Ui::Dialog
{
    Q_OBJECT

public:
    VideoWindow(WindowImagesInterface *windowImages, QWidget *parent);
    virtual ~VideoWindow();

signals:

private slots:

	void openFileClicked();
    void sliderMoved(int value);


private:
    WindowImagesInterface *_windowImages;
    std::shared_ptr<cv::VideoCapture> _cap;

};

#endif
