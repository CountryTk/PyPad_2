#ifndef NUMBERBAR_H
#define NUMBERBAR_H
#include <codeeditor.h>
#include <QWidget>

class NumberBar : public QWidget {

    Q_OBJECT
public:
    NumberBar(CodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
            return QSize(codeEditor->lineNumberAreaWidth(), 0);
        }

signals:

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

public slots:

private:
    CodeEditor *codeEditor;
};

#endif // NUMBERBAR_H
