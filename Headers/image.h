#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>

class image : public QWidget {

    Q_OBJECT
public:
    explicit image(QWidget *parent = nullptr, QString file_name = QString(), QString base_name = QString());
    QString file_name;
    QString base_name;

signals:

public slots:
};

#endif // IMAGE_H
