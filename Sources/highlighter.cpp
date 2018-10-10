#include "highlighter.h"
#include <QRegularExpression>
#include <QDebug>
#include <iostream>
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

       QColor keyword_color;
       QColor class_color;
       QColor quotation_color;
       QColor function_color;
       QColor single_line_comment_color;
       QColor decorator_color;
       QColor magic_color;
       QColor quotation2_color;

       if (file_extension == "py") {
              //patterns
              class_pattern = "\\bQ[A-Za-z]+\\b";
              quotation_pattern = "\".*\"";
              function_pattern = "[A-Za-z0-9_]+(?=\\()";
              single_line_comment = "#[^\n]*";
              decorator_format = "@[^\n]*";
              magic_format = "\\__[^']*\\__";
              quotation_pattern2 = "\"[^\"]*\"";
              integer = "[-+]?[0-9]+";
              //colors
              keyword_color = "#F6DC74";
              class_color = "#74F6C3";
              quotation_color = "#63ff00";
              function_color = "#FF6666";
              single_line_comment_color = "#6B6E6C";
              decorator_color = "#FF00E7";
              magic_color = "#FF6666";
              quotation2_color = quotation_color;

              QStringList keywordPatterns;

              keywordPatterns << "False" << "None" << "True" << "and" << "as" << "assert" << "async" << "await" << "break" << "class" <<
                      "continue" << "def" << "del" << "elif" <<"else" << "except" << "finally" << "for" <<"from" <<"global"<<
                      "if" <<"import" << "in" << "is" << "lambda" << "nonlocal" << "not" << "or"<< "pass"<< "raise" << "return" <<
                      "try" << "while" << "with" << "yield";
              keywordFormat.setForeground(keyword_color);
              keywordFormat.setFontWeight(QFont::Bold);

              foreach (const QString &pattern, keywordPatterns) {
                  rule.pattern = QRegularExpression("\\b" + pattern + "\\b");
                  rule.format = keywordFormat;
                  highlightingRules.append(rule);
              }

       } else if (file_extension == "cpp") {
           //patterns
           class_pattern = "\\bQ[A-Za-z]+\\b";
           quotation_pattern = "\".*\"";
           function_pattern = "\\b[A-Za-z0-9_]+(?=\\()";
           single_line_comment = "//[^\n]*";
           integer = "[-+]?[0-9]+";
           //colors
           keyword_color = "#0099FF";
           class_color = "#548A9C";
           quotation_color = "#63ff00";
           function_color = "#FF9500";
           single_line_comment_color = "6B6E6C";

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
           keywordFormat.setForeground(keyword_color);
           keywordFormat.setFontWeight(QFont::Bold);

           foreach (const QString &pattern, keywordPatterns) {
               rule.pattern = QRegularExpression(pattern);
               rule.format = keywordFormat;
               highlightingRules.append(rule);
           }
       }

       classFormat.setFontWeight(QFont::Bold);
       classFormat.setForeground(class_color);
       rule.pattern = QRegularExpression(class_pattern);
       rule.format = classFormat;
       highlightingRules.append(rule);

       functionFormat.setFontItalic(true);
       functionFormat.setForeground(function_color);
       rule.pattern = QRegularExpression(function_pattern);
       rule.format = functionFormat;
       highlightingRules.append(rule);

       if (magic_format != "") { // If this exists, we are dealing with a python file

           magicFormat.setFontItalic(true);
           magicFormat.setForeground(magic_color);
           rule.pattern = QRegularExpression(magic_format);
           rule.format = magicFormat;
           highlightingRules.append(rule);

           decoratorFormat.setForeground(decorator_color);
           rule.pattern = QRegularExpression(decorator_format);
           rule.format = decoratorFormat;
           highlightingRules.append(rule);

           quotation2Format.setForeground(quotation2_color);
           rule.pattern = QRegularExpression(quotation_pattern2);
           rule.format = quotation2Format;
           highlightingRules.append(rule);

           singleLineCommentFormat.setForeground(single_line_comment_color);
           rule.pattern = QRegularExpression(single_line_comment);
           rule.format = singleLineCommentFormat;
           highlightingRules.append(rule);

       }

       singleLineCommentFormat.setForeground(single_line_comment_color);
       rule.pattern = QRegularExpression(single_line_comment);
       rule.format = singleLineCommentFormat;
       highlightingRules.append(rule);

       quotationFormat.setForeground(Qt::darkGreen);
       rule.pattern = QRegularExpression(quotation_pattern);
       rule.format = quotationFormat;
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
