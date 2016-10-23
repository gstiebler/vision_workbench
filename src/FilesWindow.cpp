/*
 * FilesWindow.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: gstiebler
 */

#include "FilesWindow.h"
#include <opencv2/opencv.hpp>
#include "MainWindow.h"

using namespace std;
using namespace cv;

FilesWindow::FilesWindow(QWidget *parent, WindowImagesInterface &windowImages) :
	QDialog(parent),
	_windowImages(windowImages)
{
	setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );

	QString path = "/";
	_model.setRootPath(path);
    tree->setModel(&_model);
    tree->setRootIndex(_model.index(path));
    tree->hideColumn(1);
    tree->hideColumn(2);
    tree->hideColumn(3);
    expandPath(QDir::currentPath());

    connect( tree, &QAbstractItemView::clicked, this, &FilesWindow::clicked );
}

FilesWindow::~FilesWindow()
{
}

void FilesWindow::expandPath(const QString &path)
{
    auto list = path.split("/");
    QString base("");
    for(auto item : list)
    {
    	base += "/" + item;
        tree->setExpanded(_model.index(base), true);
    }
}

void FilesWindow::clicked(const QModelIndex &index)
{
	auto fileName = _model.filePath(index);
	Mat srcImage = imread( fileName.toLatin1().data(), 1 );
	_windowImages.setSrcImage(srcImage);
}

