#include "directory.h"
#include <QFont>
#include <QHBoxLayout>
#include <QDir>
#include <QTreeView>
#include <QDebug>
#include <QList>

Directory::Directory(QWidget *parent, QString callback) {

    QFont *font = new QFont;
    QString open_callback = callback;
    QHBoxLayout *layout = new QHBoxLayout;
    QList<int> list = {200, 600};

    font->setFamily("Consolas");
    font->setPointSize(12);
    //dir->rootPath()
    model->setRootPath("C:");

    view->setMaximumWidth(300);
    view->setIndentation(10);
    view->setAnimated(true);
    view->setSortingEnabled(true);
    view->setModel(model);
    view->setRootIndex(model->index(callback));
    view->hideColumn(1);
    view->hideColumn(2);
    view->hideColumn(3);
    //layout->addWidget(view);
    //this->setLayout(layout);
    this->setFont(*font);
    qDebug() << view;
    qDebug() << view->maximumWidth();
    //QObject::connect(view, &QTreeView::doubleClicked, this, &Directory::open_file);
    this->setVisible(false);
    qDebug() << "wtf";
}

void Directory::open_file(QModelIndex signal) {
    file_name = model->filePath(signal);
    qDebug() << file_name;
}
