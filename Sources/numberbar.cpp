#include "numberbar.h"
#include <QLabel>
#include <QVBoxLayout>

NumberBar::NumberBar(QWidget *parent) : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel;
    layout->addWidget(label);
    label->setText("1");
    this->setLayout(layout);

}
