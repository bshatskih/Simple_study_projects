#include <QFile>
#include <QFileInfo>
#include <QtXml/QDomDocument>
#include "Highlighter.h"
#include "Custom.h"

Highlighter::Highlighter(QTextDocument *parent)
        : QSyntaxHighlighter(parent) {
    readRules();
}

void Highlighter::highlightBlock(const QString &text) {
    if (not canHighlight) return;

    for (const HighlightingRule &rule: qAsConst(currentHighlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    if (not multilineCommentSupport) return;
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1) {
        startIndex = text.indexOf(multilineCommentHighlightingRule.begin_pattern);
    }

    while (startIndex >= 0) {
        QRegularExpressionMatch match = multilineCommentHighlightingRule.end_pattern.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multilineCommentHighlightingRule.format);
        startIndex = text.indexOf(multilineCommentHighlightingRule.begin_pattern, startIndex + commentLength);
    }
}

void Highlighter::readRules() {
    QFile f(":/rules.xml");
    QDomDocument doc;
    if (not f.open(QIODevice::ReadOnly)) {
        CustomMessageBoxes::Error("Ошибка модуля подсветки синтаксиса\nПодсветка синтаксиса будет недоступна");
        qDebug() << "failed to open 'rules.xml'";
        return;
    }
    doc.setContent(&f);
    auto syntaxes = doc.documentElement().firstChild().childNodes();
    for (int i = 0; i < syntaxes.count(); ++i) {
        auto syntax = syntaxes.at(i).toElement();
        auto ext_list = syntax.attribute("ext_list").split(' ');
        auto rules = syntax.childNodes();
        QVector<HighlightingRule> syntaxRuleList;
        for (int j = 0; j < rules.count(); ++j) {
            HighlightingRule rule;
            auto ruleElement = rules.at(j).toElement();
            if (ruleElement.hasAttribute("comment")) {
                MultilineCommentHighlightingRule mlcRule;
                mlcRule.begin_pattern = QRegularExpression(
                        ruleElement.elementsByTagName("begin_pattern").at(0).toElement().attribute("value"));
                mlcRule.end_pattern = QRegularExpression(
                        ruleElement.elementsByTagName("end_pattern").at(0).toElement().attribute("value"));
                mlcRule.format.setFontWeight(
                        ruleElement.elementsByTagName("format").at(0).toElement().attribute("font_weight").toInt());
                mlcRule.format.setForeground(
                        QColor(ruleElement.elementsByTagName("format").at(0).toElement().attribute("foreground")));
                multilineCommentHighlightingRulesMap[ext_list] = mlcRule;
            } else {
                auto format = ruleElement.elementsByTagName("format").at(0);
                rule.format.setFontWeight(format.toElement().attribute("font_weight").toInt());
                rule.format.setForeground(QColor(format.toElement().attribute("foreground")));
                auto patterns = ruleElement.elementsByTagName("pattern");
                for (int k = 0; k < patterns.count(); ++k) {
                    auto pattern = patterns.at(k);
                    rule.pattern = QRegularExpression(pattern.toElement().attribute("value"));
                    syntaxRuleList.append(rule);
                }
            }
        }
        highlightingRulesMap[ext_list] = syntaxRuleList;
    }
}

void Highlighter::updateExtension(const QString &newDocName) {
    auto a = newDocName;
    QFileInfo i(a.remove('*'));
    auto extension = i.completeSuffix();
    const QList<QStringList> &keys = highlightingRulesMap.keys();
    auto result = std::find_if(keys.begin(), keys.end(), [&](const QStringList &item) {
        return item.contains(extension);
    });
    if (result != keys.end()) {
        CustomMessages::print("Extension '%1' supported!", extension);
        currentHighlightingRules = highlightingRulesMap[*result];
        if (multilineCommentHighlightingRulesMap.contains(*result)) {
            multilineCommentSupport = true;
            multilineCommentHighlightingRule = multilineCommentHighlightingRulesMap[*result];
        }
        canHighlight = true;
    } else {
        CustomMessages::print("Extension '%1' NOT supported!", extension);
        canHighlight = false;
        multilineCommentSupport = false;
    }
}
