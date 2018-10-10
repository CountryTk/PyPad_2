#include "console.h"
#include <QProcess>
#include <QPlainTextEdit>
#include <QFont>
#include <iostream>
#include <QDebug>

console::console(QWidget *parent, QString file_name) : QWidget(parent) {

    QPlainTextEdit *editor = new QPlainTextEdit(this);
    editor->setReadOnly(true);

    QFont *font = new QFont;
    font->setFamily("Consolas");
    font->setPointSize(12);



    connect(process, &QProcess::readyReadStandardOutput, this, &console::onreadyReadStandardOutput);
    connect(process, &QProcess::readyReadStandardError, this, &console::onreadyReadStandardError);


    QString program = "cmd.exe";
    //process->start(program);
}

void console::onreadyReadStandardOutput() {
    QString result = process->readAllStandardOutput().data();
    qDebug() << result;
}

void console::onreadyReadStandardError() {
    QString error = process->readAllStandardError().data();
    qDebug() << error;
}

void console::run() {

}
