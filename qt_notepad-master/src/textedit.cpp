#include "textedit.h"
#include <QFile>
#include <QScrollBar>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include "linenumberarea.h"
#include "Custom.h"


textEdit::textEdit(QWidget *parent) :
        QTextEdit(parent) {
    initLineNumberArea();
}

void textEdit::initLineNumberArea() {
    lineNumberArea = new LineNumberArea(this);
    connect(document(), SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateLineNumberArea(int)));
    connect(this, SIGNAL(textChanged()), this, SLOT(updateLineNumberArea()));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(updateLineNumberArea()));
    updateLineNumberAreaWidth(0);
}

bool textEdit::isChangesSaved() const {
    return changesSaved;
}

void textEdit::setChangesSaved(bool changesSaved) {
    textEdit::changesSaved = changesSaved;
}

textEdit::textEdit(const QString &path, QWidget *parent) : QTextEdit(parent), filepath(path) {
    initLineNumberArea();
    qDebug() << "opening file" << path;
    QFile f(path);
    if (not f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        CustomMessageBoxes::Error("Ошибка открытия файла '" + path + "'");
        qDebug() << "error with opening file" << path;
        return;
    }
    setText(f.readAll());
}

void textEdit::saveChanges() {
    if (isChangesSaved()) {
        qDebug() << "file already saved";
        return;
    }
    if (filepath.isEmpty()) {
        qDebug() << "filepath is empty";
        return;
    }
    QFile f(filepath);
    if (not f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        CustomMessageBoxes::Error("Ошибка записи файла '" + filepath + "'");
        qDebug() << "error with saving" << filepath;
        return;
    }
    f.write(toPlainText().toStdString().c_str());
    qDebug() << "saved" << filepath << "successfully";
    setChangesSaved(true);
}

bool textEdit::saveAs() {
    filepath = CustomDialogs::getFilepathToSave();
    if (filepath.isEmpty()) {
        CustomMessageBoxes::Warning("Файл не выбран");
        qDebug() << "no filepath specified";
        return false;
    }
    saveChanges();
    return true;
}

const QString &textEdit::getFilepath() const {
    return filepath;
}

void textEdit::setFilepath(const QString &path) {
    filepath = path;
}

int textEdit::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, this->document()->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
//    int space = 13 +  fontMetrics().width(QLatin1Char('9')) * (digits);
    int space = 13 + fontMetrics().averageCharWidth() * (digits);

    return space;
}

void textEdit::updateLineNumberAreaWidth(int newBlockCount) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void textEdit::updateLineNumberArea(QRectF) {
    textEdit::updateLineNumberArea();
}

void textEdit::updateLineNumberArea(int) {
    textEdit::updateLineNumberArea();
}

void textEdit::updateLineNumberArea() {
    this->verticalScrollBar()->setSliderPosition(this->verticalScrollBar()->sliderPosition());

    QRect rect = this->contentsRect();
    lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    updateLineNumberAreaWidth(0);

    int dy = this->verticalScrollBar()->sliderPosition();
    if (dy > -1) {
        lineNumberArea->scroll(0, dy);
    }

    // Addjust slider to alway see the number of the currently being edited line...
    int first_block_id = getFirstVisibleBlockId();
    if (first_block_id == 0 || this->textCursor().block().blockNumber() == first_block_id - 1)
        this->verticalScrollBar()->setSliderPosition(dy - this->document()->documentMargin());

}

void textEdit::resizeEvent(QResizeEvent *e) {
    QTextEdit::resizeEvent(e);

    QRect cr = this->contentsRect();
    auto left = cr.left();
    auto top = cr.top();
    auto areaWidth = lineNumberAreaWidth();
    auto height = cr.height();
    lineNumberArea->setGeometry(left, top, areaWidth, height);
}

int textEdit::getFirstVisibleBlockId() {
    QTextCursor curs = QTextCursor(this->document());
    curs.movePosition(QTextCursor::Start);
    for (int i = 0; i < this->document()->blockCount(); ++i) {
        QTextBlock block = curs.block();

        QRect r1 = this->viewport()->geometry();
        QRect r2 = this->document()->documentLayout()->blockBoundingRect(block).translated(
                this->viewport()->geometry().x(), this->viewport()->geometry().y() - (
                        this->verticalScrollBar()->sliderPosition()
                )).toRect();

        if (r1.contains(r2, true)) { return i; }

        curs.movePosition(QTextCursor::NextBlock);
    }

    return 0;
}

void textEdit::lineNumberAreaPaintEvent(QPaintEvent *event) {
    this->verticalScrollBar()->setSliderPosition(this->verticalScrollBar()->sliderPosition());

    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), backgroundLinesColor);
    int blockNumber = this->getFirstVisibleBlockId();

    QTextBlock block = this->document()->findBlockByNumber(blockNumber);
    QTextBlock prev_block = (blockNumber > 0) ? this->document()->findBlockByNumber(blockNumber - 1) : block;
    int translate_y = (blockNumber > 0) ? -this->verticalScrollBar()->sliderPosition() : 0;

    int top = this->viewport()->geometry().top();

    int additional_margin;
    if (blockNumber == 0)
        additional_margin = (int) this->document()->documentMargin() - 1 - this->verticalScrollBar()->sliderPosition();
    else
        additional_margin = (int) this->document()->documentLayout()->blockBoundingRect(prev_block)
                .translated(0, translate_y).intersected(this->viewport()->geometry()).height();

    top += additional_margin;

    int bottom = top + (int) this->document()->documentLayout()->blockBoundingRect(block).height();

    // Draw the numbers (displaying the current line number in green)
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen((this->textCursor().blockNumber() == blockNumber) ? currentLineColor : otherLinesColor);
            painter.drawText(-5, top,
                             lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) this->document()->documentLayout()->blockBoundingRect(block).height();
        ++blockNumber;
    }
}
