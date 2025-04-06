#include "linenumberarea.h"
#include "textedit.h"

LineNumberArea::LineNumberArea(QTextEdit *editor) : QWidget(editor) {
    codeEditor = editor;
}

QSize LineNumberArea::sizeHint() const {

    //!!! C-style cast использовать не надо. Для Qt есть qobject_cast с проверкой правильности приведения.

    return {qobject_cast<textEdit *>(codeEditor)->lineNumberAreaWidth(), 0};
}

void LineNumberArea::paintEvent(QPaintEvent *event) {
    ((textEdit *) codeEditor)->lineNumberAreaPaintEvent(event);
}