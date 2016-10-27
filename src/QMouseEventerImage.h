/*
 * QMouseEventerImage.h
 *
 *  Created on: 26 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_QMOUSEEVENTERIMAGE_H_
#define SRC_QMOUSEEVENTERIMAGE_H_

#include <QLabel>
#include <QString>

class QMouseEvent;

class QMouseEventerImage : public QLabel
{
    Q_OBJECT

public:
	QMouseEventerImage(QWidget *parent = 0);

signals:
	void mousePressed(QMouseEvent *event);
	void mouseMoved(QMouseEvent *event);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};


#endif /* SRC_QMOUSEEVENTERIMAGE_H_ */
