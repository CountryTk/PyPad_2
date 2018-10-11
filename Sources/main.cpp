#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <iostream>
#include <QDebug>
#include <QPalette>
#include <QColor>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase database;
    QTextStream out(stdout); /* out << qstring object here >> endl to print out strings*/

    QPalette *palette = new QPalette;

    MainWindow *main_window = new MainWindow;

   // qDebug() << database.families(); //returns all available fonts
    palette->setColor(QPalette::Window, QColor("#303030"));
    palette->setColor(QPalette::WindowText, QColor("#FFFFFF"));
    palette->setColor(QPalette::Base, QColor("#303030"));
    palette->setColor(QPalette::AlternateBase, QColor("#FFFFFF"));
    palette->setColor(QPalette::ToolTipBase, QColor("#FFFFFF"));
    palette->setColor(QPalette::Text, QColor("#e3e6fc"));
    palette->setColor(QPalette::Button, QColor("#353535"));
    palette->setColor(QPalette::ButtonText, QColor("#FFFFFF"));
    palette->setColor(QPalette::Highlight, QColor("#4DD2FF"));
    palette->setColor(QPalette::HighlightedText, QColor("#000000"));

    a.setStyle("Fusion");
    a.setPalette(*palette);

    main_window->show();
    main_window->setWindowTitle("PyPad");
    return a.exec();

}
