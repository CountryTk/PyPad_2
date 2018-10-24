#include "find_all.h"
#include <QDebug>
#include <QPlainTextEdit>
#include <QList>
#include <iostream>
#include <QSet>

find_all::find_all(QWidget *parent) : QWidget(parent) {
    qDebug() << "lol";
}

QList<int> find_all::find_all_words(QString contents, QString string_to_find) {
    int start = 0;
    int i = 0;
    QSet<int> results;

    for (int x = 0; x < contents.length(); x++) {
        start = contents.indexOf(string_to_find, i);
        i++;
        if (start == -1) {
            break;
        } else {
            results.insert(start);
        }

    }
    return results.toList();
}
