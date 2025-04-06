#pragma once

#include <QTabWidget>
#include "textedit.h"
#include "Highlighter.h"
#include <QDebug>

class FileTabWidget : public QTabWidget {
Q_OBJECT

public:
    explicit FileTabWidget(QWidget *parent);

    bool closeAll();

    bool saveCurrent();

    bool save(int index = -1);

    bool saveCurrentAs();

    void openFile(const QString &);

    void openNewUntitled();

    void cut();

    void copy();

    void paste();

//    void remove();

    void selectAll();

signals:

    void cursorPositionChanged(int, int);

public slots:

    void onCurrentChanged(int);

    bool closeByIndex(int);

    void onTextChanged();

    void onCursorPositionChanged();


private:
    int currentTabIndex = 0;

    Highlighter *highlighter;

    void createWelcomeTab();
};
