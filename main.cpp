#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("theme-icons-browser");
    QCoreApplication::setOrganizationDomain("theme-icons-browser.github.io");
    QCoreApplication::setApplicationName("Theme icon browser");

    MainWindow w;
    w.show();

    return a.exec();
}
