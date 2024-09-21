#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("QtLanguage_" + QLocale::system().name());
    qApp->installTranslator(&qtTranslator);

    MainWindow w;
    w.show();
    return a.exec();
}
