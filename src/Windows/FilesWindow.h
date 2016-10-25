/*
 * FilesWindow.h
 *
 *  Created on: 23 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_FILESWINDOW_H_
#define SRC_FILESWINDOW_H_

#include <QFileDialog>
#include "ui_Files.h"
#include <QFileSystemModel>

class WindowImagesInterface;

class FilesWindow : public QDialog, private Ui::FilesWindow
{
    Q_OBJECT

public:
	FilesWindow(QWidget *parent, WindowImagesInterface &windowImages);
	virtual ~FilesWindow();

private slots:

	void currentChanged(const QModelIndex &current, const QModelIndex &previous);

private:

	WindowImagesInterface &_windowImages;
	QFileSystemModel _model;

	void expandPath(const QString &path);
};

#endif /* SRC_FILESWINDOW_H_ */
