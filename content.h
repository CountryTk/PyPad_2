#ifndef CONTENT_H
#define CONTENT_H

#include <QWidget>

class Content : public QWidget
{
    Q_OBJECT

public:
    explicit Content(QWidget *parent = nullptr, QString text = QString() ,QString fileName = QString(), QString baseName = QString());
    QString content;
    QString fileName;
    QString baseName;

signals:

public slots:
};

#endif // CONTENT_H
