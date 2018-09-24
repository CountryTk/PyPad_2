#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase database;
    QTextStream out(stdout); /* out << qstring object here >> endl to print out strings*/

    MainWindow *main_window = new MainWindow;

    /*qDebug() << database.families(); returns all available fonts*/
    main_window->show();
    return a.exec();
}
