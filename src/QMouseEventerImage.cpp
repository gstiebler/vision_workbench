/*
 * QMouseEventerImage.cpp
 *
 *  Created on: 26 de out de 2016
 *      Author: gstiebler
 */

#include "QMouseEventerImage.h"


QMouseEventerImage::QMouseEventerImage(QWidget *parent) :
	QLabel(parent)
{
	setMouseTracking(true);
}

void QMouseEventerImage::mousePressEvent(QMouseEvent *event)
{
	emit mousePressed(event);
}

void QMouseEventerImage::mouseMoveEvent(QMouseEvent *event)
{
	emit mouseMoved(event);
}

