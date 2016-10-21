/*
 * ThresholdWindow.cpp
 *
 *  Created on: 20 de out de 2016
 *      Author: gstiebler
 */

#include "ThresholdWindow.h"

ThresholdWindow::ThresholdWindow(QWidget *parent) :
	QDialog(parent)
{
    setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );

    QObject::connect( slider, &QSlider::valueChanged, [this] (int value) {
    	valueLabel->setText(QString::number(value));
	});
}

ThresholdWindow::~ThresholdWindow()
{
	// TODO Auto-generated destructor stub
}

