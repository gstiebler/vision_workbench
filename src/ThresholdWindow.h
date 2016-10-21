/*
 * ThresholdWindow.h
 *
 *  Created on: 20 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_THRESHOLDWINDOW_H_
#define SRC_THRESHOLDWINDOW_H_

#include <QFileDialog>

class ThresholdWindow : public QDialog
{
public:
	ThresholdWindow(QWidget *parent);
	virtual ~ThresholdWindow();
};

#endif /* SRC_THRESHOLDWINDOW_H_ */
