#include "plaintextedit.h"
#include <QFont>
#include <QDebug>
#include <iostream>
#include <QtAlgorithms>
#include <QList>
#include <QInputDialog>
#include <QErrorMessage>

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
    bool is_search = (e->modifiers() == Qt::ControlModifier && key == Qt::Key_F);

    if (is_search) {

        QString contents = this->toPlainText();
        QInputDialog *dialog = new QInputDialog;

        string_to_find = dialog->getText(this, "Find", "Find what: ");
        qDebug() << string_to_find;
        result_list = searcher->find_all_words(contents, string_to_find);

        if (result_list.length() == 0 || string_to_find.length() == 0) {
            match_found = false;
            QErrorMessage *message = new QErrorMessage;
            message->showMessage("0 results found for word: " + string_to_find);
        } else {
            match_found = true;
        }
    }

    if (key == Qt::Key_QuoteDbl) {
        this->insertPlainText("\"");
        move_cursor_back();
    }

    if (key == Qt::Key_F3) {

        qSort(result_list);
        if (num == result_list.length()) {
            num = 0;
        }
        if (match_found == true) {
            int location =  result_list[num];
            QTextCursor cursor = this->textCursor();
            cursor.setPosition(location);
            cursor.movePosition(cursor.Right, cursor.KeepAnchor, string_to_find.length());
            this->setTextCursor(cursor);

            num += 1;
        }
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

        QTextCursor cursor = this->textCursor();
        pos = cursor.position();

        cursor.setPosition(pos + 1);
        this->setTextCursor(cursor);
    }

    if (e->modifiers() == Qt::ControlModifier && key == Qt::Key_J) {

        QTextCursor cursor = this->textCursor();
        pos = cursor.position();

        cursor.setPosition(pos - 1);
        this->setTextCursor(cursor);
    }

    if (e->modifiers() == Qt::ControlModifier && key == Qt::Key_I) {

        QTextCursor cursor = this->textCursor();
        pos = cursor.position();

        cursor.movePosition(cursor.Up);
        this->setTextCursor(cursor);
    }

    if (e->modifiers() == Qt::ControlModifier && key == Qt::Key_M) {

        QTextCursor cursor = this->textCursor();
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
/*
    if (!key_list.contains(key)) {
        QPlainTextEdit::keyPressEvent(e);
        return;
    }

    e->accept();
    QTextCursor cursor = this->textCursor();

    if (key == 16777217 && replace_tabs) {
        int amount = 4 - this->textCursor().positionInBlock() % 4;
        QString str = " ";
        this->insertPlainText(str.repeated(amount));

    } else if (key == 16777219 && cursor.selectionStart() == cursor.selectionEnd() && replace_tabs && cursor.positionInBlock()) {
        //this always evaluates to true if we only delete one character
        int position = cursor.positionInBlock();
        int end = cursor.position();
        int start = end - (position % 4);

        if (start == end && position >= 4) {

            start -= 4;
        }
        QString string = this->toPlainText().mid(start, end);
        QString stripped_string = string.trimmed();
        if (!stripped_string.length()) {

            for (int i = 0; i < end - start; i++) {
                cursor.deletePreviousChar();

            }
        } else {
            QPlainTextEdit::keyPressEvent(e);
        }

    } else if (key == 16777220) {
        int end = cursor.position();
        int start = end - cursor.positionInBlock();
        QString line = this->toPlainText().mid(start, end);
        float indentation = line.length() - line.trimmed().length();
        qDebug() << "Indentation before replace_tab statement: " + QString::number(indentation);
        qDebug() << "Line before: " + line;
        qDebug() << "end is: " + QString::number(end);
        qDebug() << "start is: " + QString::number(start);

        QString chars = "\t";

        if (replace_tabs) {
            chars = "    ";
            indentation /= replace_tabs;
            qDebug() << "Indentation is: " + QString::number(indentation);
            qDebug()<< "Replace tabs value is: " + QString::number(replace_tabs);
            qDebug() << "\n";
        }

        if (line.endsWith(":")) {
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
*/
    QPlainTextEdit::keyPressEvent(e);
}
