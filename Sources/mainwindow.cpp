#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialog.h>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <codeeditor.h>
#include <QDebug>
#include <QAction>
#include <QShortcut>
#include <iostream>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QProcess>
#include <console.h>
#include <directory.h>
#include <tabs.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    tab_class = new Tabs;
    ui->setupUi(this);
    QShortcut *close_tabs = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this);
    QShortcut *run_file = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F10), this);

    QShortcut *test = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F4), this);

    QObject::connect(run_file, &QShortcut::activated, this, &MainWindow::on_actionRun_triggered);
    QObject::connect(close_tabs, &QShortcut::activated, this, &MainWindow::close_current_tab);
    QObject::connect(test, &QShortcut::activated, tab_class, &Tabs::showDirectory);
    QObject::connect(tab_class->dir_view->view, &QTreeView::doubleClicked, this, &MainWindow::open_file_from_menu);

    setCentralWidget(tab_class);

}

MainWindow::~MainWindow() {

    delete ui;
}

void MainWindow::on_actionNew_file_triggered() {

    CodeEditor *tab = new CodeEditor(this, "", "Untitled_file.py", "Untitled_file.py");
    int index = tab_class->tab->addTab(tab, tab->baseName);

    QObject::connect(tab, &CodeEditor::textChanged, this, &MainWindow::changeName);
    tab_class->tab->setCurrentIndex(index);
}

void MainWindow::on_actionCustomize_triggered() { /*get's triggered when Customize act is triggered*/

    Dialog *customize_dialog = new Dialog;
    customize_dialog->show();

}

void MainWindow::on_actionQuit_triggered() {

    qApp->quit();
}

void MainWindow::close_current_tab() {

    int current_widget = tab_class->tab->currentIndex();
    tab_class->tab->removeTab(current_widget);
}

void MainWindow::on_actionOpen_triggered() {

    QTextStream out(stdout);
    QFileDialog *file_dialog = new QFileDialog;
    QStringList our_file = file_dialog->getOpenFileNames();
    QString file_name;
    int list_length;
    file_name = our_file[0];

    list_length = our_file.length();
    if (list_length > 0) { //This is to prevent any runtime errors when closing the file opening dialog

        open_file_universal(file_name);

    } else {
        qDebug() << "No file selected";
    }
}

void MainWindow::on_actionSave_triggered() {

    QWidget *current = tab_class->tab->currentWidget();
    int current_index = tab_class->tab->currentIndex();

    if (current != nullptr) {
        CodeEditor *content_object = dynamic_cast<CodeEditor*>(current);

        QString text = content_object->toPlainText();
        QString current_file = content_object->fileName;

        tab_class->tab->setTabText(current_index, content_object->baseName);

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

    QWidget *current = tab_class->tab->currentWidget();
    CodeEditor *content_object = dynamic_cast<CodeEditor*>(current);
    QString file_name = content_object->fileName;
    console *con = new console;
    qDebug() << file_name;

}

void MainWindow::testFunction() {
    //Directory *test = new Directory(this, "C:");
}

void MainWindow::changeName() {

    QWidget *current = tab_class->tab->currentWidget();
    int current_index = tab_class->tab->currentIndex();

    if (current != nullptr) {
        CodeEditor *content_object = dynamic_cast<CodeEditor*>(current);
        QString current_file = content_object->baseName;

        tab_class->tab->setTabText(current_index, current_file + "*");
    }
}

void MainWindow::on_actionSave_as_triggered() {

    QFileDialog *file_dialog = new QFileDialog;

    QString our_file = file_dialog->getSaveFileName();
    QWidget *current = tab_class->tab->currentWidget();
    int current_index = tab_class->tab->currentIndex();

    if (our_file != "") {
        CodeEditor *content_object = dynamic_cast<CodeEditor*>(current);

        QString text = content_object->toPlainText();
        QString current_file = content_object->fileName;

        //ui->tabWidget->setTabText(current_index, content_object->baseName);

        QFile file(our_file);
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << text << endl;
        file.close();

        tab_class->tab->removeTab(current_index); // remove the current tab and open a new tab

        QFileInfo base_file_name(our_file);
        QFile files(our_file);
        QString base_name = base_file_name.completeBaseName();
        QString suffix = base_file_name.suffix();

        base_name = base_name + "." + suffix; //base_name = main.py, content.cpp, etc

        files.open(QIODevice::ReadOnly);

        QString cont; // contents of the file
        cont.append(files.readAll());
        CodeEditor *editor= new CodeEditor(this, cont, our_file, base_name);
        QObject::connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::changeName);
        int index = tab_class->tab->addTab(editor, editor->baseName);
        tab_class->tab->setCurrentIndex(index);

    } else {
        qDebug() << "Can't save to an empty file";
    }

}
void MainWindow::open_file_from_menu(QModelIndex signal) {

    QString lol = "ni";
    QString file = tab_class->dir_view->model->filePath(signal);
    open_file_universal(file);

}

void MainWindow::open_file_universal(QString file_name) {

    QFileInfo file_info(file_name);
    QFile file(file_name);
    QString base_name = file_info.completeBaseName();
    QString suffix = file_info.suffix();
    base_name = base_name + "." + suffix; //base_name = main.py, content.cpp, etc

    if (!file_info.isDir() || !file_info.isExecutable()) { // if the file that is trying to be opened isn't a dir or an exe file
        file.open(QIODevice::ReadOnly);

        QString cont; // contents of the file
        cont.append(file.readAll());
        CodeEditor *editor= new CodeEditor(this, cont, file_name, base_name);
        QObject::connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::changeName);
        int index = tab_class->tab->addTab(editor, editor->baseName);
        tab_class->tab->setCurrentIndex(index);

    } else {
        qDebug() << "Directory";
    }
}

bool MainWindow::open_project() {

    QFileDialog *file_dialog = new QFileDialog;

    QString dir = file_dialog->getExistingDirectory(nullptr, "Select a folder:","", QFileDialog::ShowDirsOnly);
    if (dir == "") {
        qDebug() << "FIle dialog closed";
        return false;
    } else {
        tab_class->dir_view->open_directory(dir);
        return true;
    }
}

void MainWindow::on_actionOpen_project_triggered() {
    if (open_project() == true) {
        tab_class->showDirectory();
    } else {
        qDebug() << "No directory selected";
 }
}

