/*
 * MainWindow.cpp
 *
 *  Created on: 18/10/2014
 *      Author: Guilherme
 */

#include "MainWindow.h"
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMessageBox>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
{
    setupUi(this);

    //connect( buttonExecute, SIGNAL( clicked() ), this, SIGNAL( executeButtonClicked() ) );
    //connect( btInputDirectory, SIGNAL( clicked() ), this, SLOT( selectFolder() ) );
	//connect( menuSobre, SIGNAL(aboutToShow()), this, SLOT(aboutClicked()) );
}

MainWindow::~MainWindow()
{
}

void MainWindow::aboutClicked()
{
	QMessageBox msgBox;
	msgBox.setText("Propriedade intelectual de Guilherme Stiebler");
	msgBox.exec();
}