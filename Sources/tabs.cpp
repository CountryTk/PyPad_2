#include "tabs.h"
#include <QTabWidget>
#include <QFont>
#include <QHBoxLayout>
#include <directory.h>
#include <console.h>
#include <QSplitter>
#include <QList>
#include <QDebug>
#include <QShortcut>
#include <QKeySequence>
#include <QMainWindow>

Tabs::Tabs(QWidget *parent) : QWidget(parent) {
   // qDebug() << "wtdsadsadsadsadf";
    tab_layout->addWidget(tab);
   // qDebug() << "wtdsadf";
    tab->setTabsClosable(true);
    font->setFamily("Consolas");
    font->setPointSize(10);
    tab->tabBar()->setFont(*font);
    QObject::connect(tab, &QTabWidget::tabCloseRequested, this, &Tabs::tab_close_requested);
   // qDebug() << "wtf";
    layout->addLayout(tab_layout);
    //qDebug() << "wtfs";
    this->setLayout(layout);
   // qDebug() << "wtfdsa";
}

void Tabs::tab_close_requested(int index) {

    tab->removeTab(index);
}
void Tabs::showDirectory() {
    dir_view->setVisible(true);
    tab_layout->removeWidget(tab);
    tab_layout->addWidget(dir_view->view);
    tab_layout->addWidget(tab);
    dir_view->hide();


   // auto p = dynamic_cast<QMainWindow*>(parent());
}
