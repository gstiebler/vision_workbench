#include <QApplication>

#include "Windows/MainWindow.h"

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::string initialImage;
    if(argc > 1)
    {
    	initialImage = argv[1];
    }
    MainWindow *mainWindow = new MainWindow(initialImage);
    mainWindow->show();
    return app.exec();
}
