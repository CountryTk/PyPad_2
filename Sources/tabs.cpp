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

    tab_layout->addWidget(tab);
    tab->setTabsClosable(true);
    font->setFamily("Consolas");
    font->setPointSize(10);
    tab->tabBar()->setFont(*font);
    layout->addLayout(tab_layout);
    this->setLayout(layout);
}

void Tabs::showDirectory() {
    dir_view->setVisible(true);
    tab_layout->removeWidget(tab);
   // dir_view->show();
    tab_layout->addWidget(dir_view->view);

    qDebug() << dir_view;
    tab_layout->addWidget(tab);
    dir_view->hide();

}
