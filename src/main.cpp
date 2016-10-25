#include <QApplication>

#include "Windows/MainWindow.h"

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow *mainWindow = new MainWindow(nullptr);
    mainWindow->show();
    return app.exec();
}
