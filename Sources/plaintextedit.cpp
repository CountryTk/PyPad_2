#include "plaintextedit.h"
#include <QFont>
#include <QDebug>
#include <iostream>

PlainTextEdit::PlainTextEdit(QWidget *parent) {

    font = new QFont;


    font->setFamily("Consolas");
    font->setPointSize(12);

    replace_tabs = 4;
    key_list = {16777217, 16777219, 16777220};
    this->setTabStopWidth(40);
    this->createStandardContextMenu();
    this->setWordWrapMode(QTextOption::NoWrap);
}

void PlainTextEdit::move_cursor_back() {

    QTextCursor text_cursor = this->textCursor();
    int text_cursor_pos = text_cursor.position();

    text_cursor.setPosition(text_cursor_pos -1);
    this->setTextCursor(text_cursor);
}

void PlainTextEdit::keyPressEvent(QKeyEvent *e) {

    QTextCursor text_cursor = this->textCursor();
    int key = e->key();

    if (key == Qt::Key_QuoteDbl) {
        this->insertPlainText("\"");
        move_cursor_back();
    }

    if (e->modifiers() == Qt::ControlModifier && key == 61) {

        this->font->setPointSize(font->pointSize() + 1);
        this->setFont(*font);
    }

    if (e->modifiers() == Qt::ControlModifier && key == 45) {

        this->font->setPointSize(font->pointSize() - 1);
        this->setFont(*font);
    }

    if (e->modifiers() == Qt::ControlModifier && key == Qt::Key_L) {

        cursor = this->textCursor();
        pos = cursor.position();

        cursor.setPosition(pos + 1);
        this->setTextCursor(cursor);
    }

    if (e->modifiers() == Qt::ControlModifier && key == Qt::Key_J) {

        cursor = this->textCursor();
        pos = cursor.position();

        cursor.setPosition(pos - 1);
        this->setTextCursor(cursor);
    }

    if (e->modifiers() == Qt::ControlModifier && key == Qt::Key_I) {

        cursor = this->textCursor();
        pos = cursor.position();

        cursor.movePosition(cursor.Up);
        this->setTextCursor(cursor);
    }

    if (e->modifiers() == Qt::ControlModifier && key == Qt::Key_M) {

        cursor = this->textCursor();
        pos = cursor.position();

        cursor.movePosition(cursor.Down);
        this->setTextCursor(cursor);
    }
    if (key == 39) {

        this->insertPlainText("'");
        move_cursor_back();
    }

    if (key == Qt::Key_BraceLeft) {

        this->insertPlainText("}");
        move_cursor_back();
    }

    if (key == Qt::Key_BracketLeft) {

        this->insertPlainText("]");
        move_cursor_back();
    }

    if (key == Qt::Key_ParenLeft) {

        this->insertPlainText(")");
        move_cursor_back();
    }

    if (!key_list.contains(key)) {
        QPlainTextEdit::keyPressEvent(e);
        return;
    }

   // e->accept();
    qDebug() << this->textCursor().selectionStart();
    qDebug() << this->textCursor().selectionEnd();
    qDebug() << key;
    qDebug() << this->textCursor().positionInBlock();

    if (key == 16777217 && replace_tabs) {
        int amount = 4 - this->textCursor().positionInBlock() % 4;
        QString str = " ";
        qDebug() << "more than 1 character deleted";
        this->insertPlainText(str.repeated(amount));

    } else if (key == 16777219 && this->textCursor().selectionStart() == this->textCursor().selectionEnd() && replace_tabs && this->textCursor().positionInBlock()) {
        //this always evaluates to true if we only delete one character
        int position = this->textCursor().positionInBlock();
        int end = this->textCursor().position();
        int start = end - (position % 4);

        if (start == end && position >= 4) {

            start -= 4;
        }
        QString string = this->toPlainText().mid(start, end);
        QString stripped_string = string.trimmed();
        if (!stripped_string.length()) {

            for (int i = 0; i < end - start; i++) {
                this->textCursor().deletePreviousChar();

            }
        } else {
            QPlainTextEdit::keyPressEvent(e);
        }

    } else if (key == 16777220) {
        int end = this->textCursor().position();
        int start = end - this->textCursor().positionInBlock();
        QString line = this->toPlainText().mid(start, end);
        int indentation = line.length() - line.trimmed().length();

        QString chars = "\t";

        if (replace_tabs) {
            chars = "    ";
            indentation /= replace_tabs;
           // QPlainTextEdit::keyPressEvent(e);
        }

        if (line.endsWith(":")) {
            qDebug() << line.endsWith(":");
            if (replace_tabs) {
                indentation += 1;
            }

            QPlainTextEdit::keyPressEvent(e);
            this->insertPlainText(chars.repeated(indentation));

        } else {
            QPlainTextEdit::keyPressEvent(e);
            this->insertPlainText(chars.repeated(indentation));
        }
    } else {
        QPlainTextEdit::keyPressEvent(e);
    }
}
