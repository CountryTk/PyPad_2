#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H
#include <QPlainTextEdit>

class PlainTextEdit : public QPlainTextEdit {

public:
    PlainTextEdit(QWidget *parent = nullptr);
    QFont *font;
    void move_cursor_back();
    int replace_tabs;
    QList<int> key_list;
    QTextCursor cursor;
    int pos;

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // PLAINTEXTEDIT_H
