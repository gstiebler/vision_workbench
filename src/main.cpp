#include <QApplication>

#include "MainWindow.h"

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow *mainWindow = new MainWindow(0);
    mainWindow->show();
    return app.exec();
}
