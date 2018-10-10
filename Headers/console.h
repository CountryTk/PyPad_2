#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>
#include <QProcess>

class console : public QWidget {

    Q_OBJECT
public:
    explicit console(QWidget *parent = nullptr, QString file_name = QString());
    QString file_name;
    QProcess *process = new QProcess;

signals:

public slots:
    void onreadyReadStandardOutput();
    void onreadyReadStandardError();
    void run();
};

#endif // CONSOLE_H
