#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialog.h>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <content.h>
#include <QDebug>
#include <QAction>
#include <iostream>

void lol(int index) {

    std::cout << "nigger" << std::endl;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *close_tab = new QAction;

    close_tab->setShortcut(Qt::Key_W | Qt::CTRL);
    connect(close_tab, SIGNAL(triggered()), this, SLOT(close())); //fix this to close a tab later
    this->addAction(close_tab);
    setCentralWidget(ui->tabWidget); //Set this to a Tabs class which should inherit from a QWidget

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_file_triggered() {
    Content *lol = new Content(this, "", "Untitled_file.py", "Untitled_file.py");
    int index = ui->tabWidget->addTab(lol, lol->fileName);
    qDebug() << index;
    ui->tabWidget->setCurrentIndex(index);

}

void MainWindow::on_actionCustomize_triggered() { /*get's triggered when Customize act is triggered*/
    Dialog *customize_dialog = new Dialog;
    customize_dialog->show();

}

void MainWindow::on_tabWidget_tabCloseRequested(int index) {
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionQuit_triggered() {
    qApp->quit();
}
