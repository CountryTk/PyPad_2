#include "content.h"
#include <QPlainTextEdit> //replace this with PlainTextEdit later, a class made by me with auto completion
#include <QHBoxLayout>
#include "numberbar.h"

Content::Content(QWidget *parent, QString text , QString filename, QString basename) : QWidget(parent) {

    content = text;
    fileName = filename;
    baseName = basename;

    NumberBar *numbers = new NumberBar;

    QHBoxLayout *layout = new QHBoxLayout;

    QPlainTextEdit *editor = new QPlainTextEdit;

    layout->addWidget(numbers);
    layout->addWidget(editor);
    editor->setPlainText(text);

    this->setLayout(layout);

}
