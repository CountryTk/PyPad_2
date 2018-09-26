#include "content.h"
#include <QPlainTextEdit> //replace this with PlainTextEdit later, a class made by me with auto completion
#include <QHBoxLayout>
#include "numberbar.h"
#include <QFont>
#include <highlighter.h>
#include <QFileInfo>
#include <QDebug>

Content::Content(QWidget *parent, QString text , QString filename, QString basename) : QWidget(parent) {

    content = text;
    fileName = filename;
    baseName = basename;

    NumberBar *numbers = new NumberBar;
    QFont *font = new QFont;
    QHBoxLayout *layout = new QHBoxLayout;
    QPlainTextEdit *editor = new QPlainTextEdit;
    QString filenames = QFileInfo(fileName).completeSuffix();

    if (filenames == "py") {
        highlighter *syntax = new highlighter(editor->document(), "py");

    } else if (filenames =="cpp" || filenames == "h") {
         highlighter *syntax = new highlighter(editor->document(), "cpp");
    }


    font->setFamily("Consolas");
    font->setPointSize(12);

    layout->addWidget(numbers);
    layout->addWidget(editor);
    editor->setPlainText(text);

    this->setFont(*font);
    this->setLayout(layout);

}
