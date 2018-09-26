#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialog.h>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <content.h>
#include <QDebug>
#include <QAction>
#include <QShortcut>
#include <iostream>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    QShortcut *close_tabs = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this);

    QObject::connect(close_tabs, &QShortcut::activated, this, &MainWindow::close_current_tab);

    setCentralWidget(ui->tabWidget); //Set this to a Tabs class which should inherit from a QWidget

}

MainWindow::~MainWindow() {

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

void MainWindow::close_current_tab() {
    int current_widget = ui->tabWidget->currentIndex();
    ui->tabWidget->removeTab(current_widget);

}

void MainWindow::on_actionOpen_triggered() {

    QTextStream out(stdout);
    QFileDialog *file_dialog = new QFileDialog;
    QStringList our_file = file_dialog->getOpenFileNames();
    QString file_name = our_file[0];

    QFile file(file_name);
    file.open(QIODevice::ReadOnly);

    QString cont;
    cont.append(file.readAll());

    Content *editor= new Content(this, cont, file_name, file_name);
    int index = ui->tabWidget->addTab(editor, editor->baseName);
    ui->tabWidget->setCurrentIndex(index);

}
