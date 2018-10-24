#ifndef FIND_ALL_H
#define FIND_ALL_H

#include <QWidget>
#include <QList>
class find_all : public QWidget {

    Q_OBJECT
public:
    explicit find_all(QWidget *parent = nullptr);

QList<int> find_all_words(QString contents, QString string_to_find);
signals:

public slots:
};

#endif // FIND_ALL_H
