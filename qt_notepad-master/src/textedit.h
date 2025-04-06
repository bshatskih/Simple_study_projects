#pragma once

#include <QDebug>
#include <QTextEdit>

class textEdit : public QTextEdit {
Q_OBJECT

public:
    explicit textEdit(QWidget *parent = nullptr);

    textEdit(const QString &path, QWidget *parent = nullptr);

    const QString &getFilepath() const;

    void setFilepath(const QString &filepath);

    int getFirstVisibleBlockId();

    void lineNumberAreaPaintEvent(QPaintEvent *event);

    int lineNumberAreaWidth();

public slots:

    void resizeEvent(QResizeEvent *e);

private slots:

    void updateLineNumberAreaWidth(int);

    void updateLineNumberArea(QRectF /*rect_f*/);

    void updateLineNumberArea(int /*slider_pos*/);

    void updateLineNumberArea();

private:
    QString filepath;
    bool changesSaved = true;
    QWidget *lineNumberArea;
    QColor currentLineColor = QColor(80, 255, 53);
    QColor otherLinesColor = QColor(247, 235, 232);
    QColor backgroundLinesColor = QColor(29, 32, 29);

public:
    bool isChangesSaved() const;

    void setChangesSaved(bool changesSaved);

    void saveChanges();

    bool saveAs();

    void initLineNumberArea();
};

