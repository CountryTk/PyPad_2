#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H
#include <QPlainTextEdit>
#include <find_all.h>

class PlainTextEdit : public QPlainTextEdit {

public:
    PlainTextEdit(QWidget *parent = nullptr);

    QWidget *parent;
    QFont *font;
    void move_cursor_back();
    int replace_tabs;
    int num = 0;
    QList<int> key_list;
    QString string_to_find;
    QList<int> result_list;
    bool match_found;
    find_all *searcher = new find_all(this);
    int pos;

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // PLAINTEXTEDIT_H
