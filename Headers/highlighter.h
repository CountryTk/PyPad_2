#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QRegularExpression>

class highlighter : public QSyntaxHighlighter {

public:
    highlighter(QTextDocument *editor_file = nullptr, QString extension = QString());
    QString file_extension;
protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule {

        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat magicFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat decoratorFormat;
    QTextCharFormat quotation2Format;
    QTextCharFormat integer;
    QTextCharFormat functionFormat;
};

#endif // HIGHLIGHTER_H
