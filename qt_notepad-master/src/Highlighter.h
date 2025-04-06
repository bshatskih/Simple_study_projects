#pragma once

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QDebug>

class Highlighter : public QSyntaxHighlighter {
Q_OBJECT

public:
    Highlighter(QTextDocument *parent = nullptr);

public slots:

    void updateExtension(const QString &newDocName = QString());

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    struct MultilineCommentHighlightingRule {
        QRegularExpression begin_pattern;
        QRegularExpression end_pattern;
        QTextCharFormat format;
    };
    QMap<QStringList, QVector<HighlightingRule>> highlightingRulesMap;
    QMap<QStringList, MultilineCommentHighlightingRule> multilineCommentHighlightingRulesMap;

    bool canHighlight = false;
    bool multilineCommentSupport = false;
    QVector<HighlightingRule> currentHighlightingRules;
    MultilineCommentHighlightingRule multilineCommentHighlightingRule;

    void readRules();

};