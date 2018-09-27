#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialog.h>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <codeeditor.h>
#include <content.h>
#include <QDebug>
#include <QAction>
#include <QShortcut>
#include <iostream>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QProcess>
#include <console.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    bool state;

    QShortcut *close_tabs = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this);
    QShortcut *run_file = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F10), this);

    QObject::connect(run_file, &QShortcut::activated, this, &MainWindow::on_actionRun_triggered);
    QObject::connect(close_tabs, &QShortcut::activated, this, &MainWindow::close_current_tab);

    setCentralWidget(ui->tabWidget); //Set this to a Tabs class which should inherit from a QWidget

}

MainWindow::~MainWindow() {

    delete ui;
}

void MainWindow::on_actionNew_file_triggered() {

    CodeEditor *tab = new CodeEditor(this, "", "Untitled_file.py", "Untitled_file.py");
    int index = ui->tabWidget->addTab(tab, tab->baseName);

    QObject::connect(tab, &CodeEditor::textChanged, this, &MainWindow::changeName);
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
    QString file_name;
    int list_length;

    list_length = our_file.length();
    if (list_length > 0) { //This is to prevent any runtime errors when closing the file opening dialog

        file_name = our_file[0];
        QFileInfo base_file_name(file_name);
        QFile file(file_name);
        QString base_name = base_file_name.completeBaseName();
        QString suffix = base_file_name.suffix();

        base_name = base_name + "." + suffix; //base_name = main.py, content.cpp, etc

        file.open(QIODevice::ReadOnly);

        QString cont; // contents of the file
        cont.append(file.readAll());
        CodeEditor *editor= new CodeEditor(this, cont, file_name, base_name);
        QObject::connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::changeName);
        int index = ui->tabWidget->addTab(editor, editor->baseName);
        ui->tabWidget->setCurrentIndex(index);

    } else {
        qDebug() << "No file selected";
    }
}

void MainWindow::on_actionSave_triggered() {

    QWidget *current = ui->tabWidget->currentWidget();
    int current_index = ui->tabWidget->currentIndex();

    if (current != nullptr) {
        CodeEditor *content_object = dynamic_cast<CodeEditor*>(current);

        QString text = content_object->toPlainText();
        QString current_file = content_object->fileName;

        ui->tabWidget->setTabText(current_index, content_object->baseName);

        QFile file(current_file);
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << text << endl;
        file.close();

    } else {
        qDebug() << "Can't save to an empty file";
    }
}

void MainWindow::on_actionRun_triggered() {

    QWidget *current = ui->tabWidget->currentWidget();
    Content *content_object = dynamic_cast<Content*>(current);
    QString file_name = content_object->fileName;
    console *con = new console;


    qDebug() << file_name;

}

void MainWindow::testFunction() {
    std::cout << "testing" << std::endl;
}
void MainWindow::changeName() {
    QWidget *current = ui->tabWidget->currentWidget();
    int current_index = ui->tabWidget->currentIndex();

    if (current != nullptr) {
        CodeEditor *content_object = dynamic_cast<CodeEditor*>(current);
        QString current_file = content_object->baseName;

        ui->tabWidget->setTabText(current_index, current_file + "*");
    }
}

