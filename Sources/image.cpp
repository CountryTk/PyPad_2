#include "image.h"
#include <QString>
#include <QLabel>
#include <QPixmap>

image::image(QWidget *parent, QString file, QString base) : QWidget(parent) {

    base_name = base;
    file_name = file;
    QPixmap *image = new QPixmap(file_name);
    QLabel *image_label = new QLabel(this);
    image_label->setPixmap(*image);

}
