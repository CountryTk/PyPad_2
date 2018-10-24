#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <QTreeView>
#include <QWidget>
#include <QFileSystemModel>

class Directory : public QWidget {

public:
    Directory(QWidget *parent = nullptr, QString callback = QString());

    QTreeView *view = new QTreeView;
    QFileSystemModel *model = new QFileSystemModel;
    QString file_name;

    void open_directory(QString path);

protected:
    void keyPressEvent(QKeyEvent *event) override;

};
#endif // DIRECTORY_H

