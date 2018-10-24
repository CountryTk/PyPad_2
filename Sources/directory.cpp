#include "directory.h"
#include <QFont>
#include <QHBoxLayout>
#include <QDir>
#include <QTreeView>
#include <QDebug>

Directory::Directory(QWidget *parent, QString callback) {

    QFont *font = new QFont;
    QString open_callback = callback;
    QList<int> list = {200, 600};
    QDir *rootdir = new QDir;

    font->setFamily("Consolas");
    font->setPointSize(12);

    model->setRootPath(rootdir->rootPath());

    view->setMaximumWidth(300);
    view->setIndentation(10);
    view->setAnimated(true);
    view->setSortingEnabled(true);
    view->setModel(model);
    view->setRootIndex(model->index(callback));
    view->hideColumn(1);
    view->hideColumn(2);
    view->hideColumn(3);

    this->setFont(*font);
    this->setVisible(false);
}

void Directory::open_directory(QString path) {
    view->setRootIndex(model->index(path));
}

void Directory::keyPressEvent(QKeyEvent *e) {

    qDebug() << e;
}

