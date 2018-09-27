#include <QtWidgets>
#include <QFont>
#include "codeeditor.h"
#include <QColor>
#include <iostream>
#include <QFileInfo>
#include <highlighter.h>

CodeEditor::CodeEditor(QWidget *parent, QString text, QString filename, QString basename) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);
    content = text;
    fileName = filename;
    baseName = basename;

    QFont *font = new QFont;

    connect(this, &QPlainTextEdit::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &QPlainTextEdit::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    QString filenames = QFileInfo(fileName).completeSuffix();
    if (filenames == "py") {
        highlighter *syntax = new highlighter(this->document(), "py");

    } else if (filenames =="cpp" || filenames == "h") {
         highlighter *syntax = new highlighter(this->document(), "cpp");
    }

    font->setFamily("Consolas");
    font->setPointSize(12);
    this->setFont(*font);
    this->setPlainText(text);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int CodeEditor::lineNumberAreaWidth() {

    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}



void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */) {

    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}



void CodeEditor::updateLineNumberArea(const QRect &rect, int dy) {

    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}



void CodeEditor::resizeEvent(QResizeEvent *e) {

    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}



void CodeEditor::highlightCurrentLine() {

    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(QColor(53, 53, 53));

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}



void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event) {

    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor("#303030"));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    //int top = (int) ;
    //int top = static_cast<int>(blockBoundingGeometry(block).translated(contentOffset()).top());
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();

    //int bottom = static_cast<int>(blockBoundingRect(block).height());
    int bottom = top + (int) blockBoundingRect(block).height(); // using old style casts because new ones misalign the number with the text

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);

            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        //bottom = top + static_cast<int>(blockBoundingRect(block).height());
        bottom = top + (int) blockBoundingRect(block).height(); // see line 107
        ++blockNumber;
    }
}
