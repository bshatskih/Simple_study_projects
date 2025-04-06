#pragma once

#include <QWidget>
#include <QTextEdit>
#include <QDebug>

class LineNumberArea : public QWidget {
Q_OBJECT

public:
    LineNumberArea(QTextEdit *editor);

    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QTextEdit *codeEditor;
};