#ifndef TABS_H
#define TABS_H

#include <QWidget>
#include <QTabWidget>
#include <console.h>
#include <directory.h>
#include <QHBoxLayout>
#include <QSplitter>
#include <QList>
#include <QDebug>
#include <QFont>

class Tabs : public QWidget {

    Q_OBJECT
public:
    explicit Tabs(QWidget *parent = nullptr);

    QHBoxLayout *layout = new QHBoxLayout(this);
    QTabWidget *tab = new QTabWidget;
    console *our_console = new console;
    QFont *font = new QFont;
    Directory *dir_view = new Directory(this, "C:");
    QHBoxLayout *tab_layout = new QHBoxLayout;
    QHBoxLayout *search_layout = new QHBoxLayout; // not used at the moment


signals:

public slots:
    void showDirectory();

//private slots:
    //void tab_close_requested(int index);

};

#endif // TABS_H
