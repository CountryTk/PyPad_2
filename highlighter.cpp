#include "highlighter.h"
#include <QRegularExpression>
#include <QDebug>

highlighter::highlighter(QTextDocument *editor_file, QString extension)
    : QSyntaxHighlighter(editor_file) {

    HighlightingRule rule;
       file_extension = extension;
       QString class_pattern;
       QString quotation_pattern;
       QString function_pattern;
       QString single_line_comment;
       QString decorator_format;
       QString magic_format;
       QString quotation_pattern2;
       QString integer;
       if (file_extension == "py") {

              class_pattern = "\\bQ[A-Za-z]+\\b";
              quotation_pattern = "\".*\"";
              function_pattern = "[A-Za-z0-9_]+(?=\\()";
              single_line_comment = "#[^\n]*";
              decorator_format = "@[^\n]*";
              magic_format = "\\__[^']*\\__";
              quotation_pattern2 = "\"[^\"]*\"";
              integer = "[-+]?[0-9]+";

              QStringList keywordPatterns;

              keywordPatterns << "False" << "None" << "True" << "and" << "as" << "assert" << "async" << "await" << "break" << "class" <<
                      "continue" << "def" << "del" << "elif" <<"else" << "except" << "finally" << "for" <<"from" <<"global"<<
                      "if" <<"import" << "in" << "is" << "lambda" << "nonlocal" << "not" << "or"<< "pass"<< "raise" << "return" <<
                      "try" << "while" << "with" << "yield";
              keywordFormat.setForeground(Qt::darkBlue);
              keywordFormat.setFontWeight(QFont::Bold);

              foreach (const QString &pattern, keywordPatterns) {
                  rule.pattern = QRegularExpression("\\b" + pattern + "\\b");
                  rule.format = keywordFormat;
                  highlightingRules.append(rule);
              }

       } else if (file_extension == "cpp") {

           class_pattern = "\\bQ[A-Za-z]+\\b";
           quotation_pattern = "\".*\"";
           function_pattern = "\\b[A-Za-z0-9_]+(?=\\()";
           single_line_comment = "//[^\n]*";
           decorator_format = "@[^\n]*";
           magic_format = "\\__[^']*\\__";
           quotation_pattern2 = "\"[^\"]*\"";
           integer = "[-+]?[0-9]+";

           QStringList keywordPatterns;
           keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                           << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                           << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                           << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                           << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                           << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                           << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                           << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                           << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                           << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b";
           keywordFormat.setForeground(Qt::darkBlue);
           keywordFormat.setFontWeight(QFont::Bold);

           foreach (const QString &pattern, keywordPatterns) {
               rule.pattern = QRegularExpression(pattern);
               rule.format = keywordFormat;
               highlightingRules.append(rule);
           }
       }

       classFormat.setFontWeight(QFont::Bold);
       classFormat.setForeground(Qt::darkMagenta);
       rule.pattern = QRegularExpression(class_pattern);
       rule.format = classFormat;
       highlightingRules.append(rule);

       quotationFormat.setForeground(Qt::darkGreen);
       rule.pattern = QRegularExpression(quotation_pattern);
       rule.format = quotationFormat;
       highlightingRules.append(rule);

       functionFormat.setFontItalic(true);
       functionFormat.setForeground(Qt::blue);
       rule.pattern = QRegularExpression(function_pattern);
       rule.format = functionFormat;
       highlightingRules.append(rule);

       singleLineCommentFormat.setForeground(Qt::red);
       rule.pattern = QRegularExpression(single_line_comment);
       rule.format = singleLineCommentFormat;
       highlightingRules.append(rule);

       multiLineCommentFormat.setForeground(Qt::red);

       commentStartExpression = QRegularExpression("/\\*");
       commentEndExpression = QRegularExpression("\\*/");
    }

void highlighter::highlightBlock(const QString &text) {

    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);

        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = text.indexOf(commentStartExpression);

        while (startIndex >= 0) {
            QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
            int endIndex = match.capturedStart();
            int commentLength = 0;
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex
                                + match.capturedLength();
            }
            setFormat(startIndex, commentLength, multiLineCommentFormat);
            startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
        }
    }
