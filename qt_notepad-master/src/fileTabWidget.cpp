#include <QFile>
#include <QFileInfo>
#include "textedit.h"
#include "fileTabWidget.h"
#include "Custom.h"

FileTabWidget::FileTabWidget(QWidget *parent) : QTabWidget(parent) {
    createWelcomeTab();
    setTabsClosable(true);
    highlighter = new Highlighter;
    highlighter->setParent(this);
    QObject::connect(this, SIGNAL(currentChanged(int)),
                     this, SLOT(onCurrentChanged(int)));
}

void FileTabWidget::createWelcomeTab() {
    QString welcomeText = "Здравствуйте!\n"
                          "\n\n"
                          "Ctrl+O - Открыть файл\n"
                          "Ctrl+S - Сохранить\n"
                          "Ctrl+Shift+S - Сохранить всё\n"
                          "А опция 'Сохранить как' доступна в меню\n"
                          "Ctrl+W - Закрыть файл\n"
                          "Ctrl+Shift+W - Закрыть все файлы\n"
                          "Ctrl+N - Открыть новый файл\n"
                          "Ctrl+Q - Выйти из приложения\n"
                          "\n\n"
                          "Ctrl+C - Копировать\n"
                          "Ctrl+V - Вставить\n"
                          "Ctrl+X - Вырезать\n"
                          "Ctrl+D - Удалить файл";
    auto *t = new textEdit;
    t->setText(welcomeText);
    auto f = t->font();
    f.setBold(true);
    t->setFont(f);
    t->setChangesSaved(true);
    addTab(t, "Welcome");
    setCurrentWidget(t);
    t->setReadOnly(true);
}

bool FileTabWidget::closeByIndex(int index) {
    if (tabText(index) == "Welcome") {
        removeTab(index);
        return true;
    }
    auto *w = dynamic_cast<textEdit *>(widget(index));
    if (not w) return false;
    if (not w->isChangesSaved()) {
        switch (CustomMessageBoxes::CloseUnsavedFileChoice(tabText(index).remove('*'))) {
            case QMessageBox::Discard:
                // не сохранять и закрыть файл
                break;
            case QMessageBox::Yes:
                // сохранить и закрыть
                save(index);
                break;
            case QMessageBox::Close:
                // не сохранять, не закрывать
                return false;
            default:
                break;
        }
    }
    CustomMessages::print("Closing %1 which is %2", tabText(index), (w->isChangesSaved() ? "saved" : "not saved"));
    removeTab(index);
    return true;
}

bool FileTabWidget::closeAll() {
    int i = count();
    bool success = true;
    while (i-- > 0) {
        success &= closeByIndex(0);
    }
    return success;
}

void FileTabWidget::openFile(const QString &filepath) {
    for (int i = 0; i < count(); ++i) {
        if (tabText(i) == filepath or dynamic_cast<textEdit *>(widget(i))->getFilepath() == filepath) {
            setCurrentIndex(i);
            return;
        }
    }
    auto *t = new textEdit(filepath, this);
    QObject::connect(t, SIGNAL(cursorPositionChanged()),
                     this, SLOT(onCursorPositionChanged()));
    QFileInfo i(filepath);
    auto tabId = addTab(t, i.fileName());
    setTabToolTip(tabId, filepath);
    setCurrentWidget(t);
//    highlighter->setDocument(t->document());
//    highlighter->updateExtension(filepath);
//    highlighter->rehighlight(); // Без этого все открытые файлы сразу, почему-то отмечаются как измененные.
//    QObject::connect(t, SIGNAL(textChanged()),
//                     this, SLOT(onTextChanged()));
}

void FileTabWidget::onTextChanged() {
    auto *editor = dynamic_cast<textEdit *>(sender());
    auto changedIndex = indexOf(editor);
    CustomMessages::print("%1 changed", tabText(changedIndex));

    if (editor->isChangesSaved()) {
        editor->setChangesSaved(false);
        setTabText(changedIndex, tabText(changedIndex) + "*");
    }
}

void FileTabWidget::openNewUntitled() {
    auto *t = new textEdit;
    QObject::connect(t, SIGNAL(cursorPositionChanged()),
                     this, SLOT(onCursorPositionChanged()));
    addTab(t, "untitled*");
    setCurrentWidget(t);
    t->setChangesSaved(false);
    highlighter->setDocument(t->document());
    highlighter->updateExtension();
//    QObject::connect(t, SIGNAL(textChanged()),
//                     this, SLOT(onTextChanged()));
}

bool FileTabWidget::saveCurrent() {
    int index = currentIndex();
    if (index == -1) {
        CustomMessageBoxes::Info("Сохранять нечего. Файл не выбран.");
        return false;
    }
    if (tabText(index) == "Welcome") return false;
    return save(index);
}

bool FileTabWidget::save(int index) {
    auto *toSave = dynamic_cast<textEdit *>(widget(index));
    if (not toSave) {
        CustomMessageBoxes::Error("Ошибка сохранения файла");
        CustomMessages::print("invalid index to save [%1]", index);
        return false;
    }
    if (toSave->getFilepath().isEmpty() and tabText(index) != "Welcome") {
        qDebug() << "save -> saveAS" << tabText(index);
        if (not saveCurrentAs()) return false;
        if (closeByIndex(currentIndex()))
            openFile(toSave->getFilepath());
        else
            CustomMessageBoxes::Error("Ошибка закрытия файла");
    } else {
        qDebug() << "save";
        toSave->saveChanges();
    }
    if (tabText(index).contains('*'))
        setTabText(index, tabText(index).remove('*'));
    return true;
}

bool FileTabWidget::saveCurrentAs() {
    if (tabText(currentIndex()) == "Welcome") return false;
    auto *toSave = dynamic_cast<textEdit *>(currentWidget());
    if (not toSave) {
        CustomMessageBoxes::Info("Сохранять нечего. Файл не выбран.");
        return false;
    }
    qDebug() << "save current as";
    return toSave->saveAs();
}

void FileTabWidget::cut() {
    auto *w = dynamic_cast<textEdit *>(currentWidget());
    if (not w) return;
    w->cut();
}

void FileTabWidget::copy() {
    auto *w = dynamic_cast<textEdit *>(currentWidget());
    if (not w) return;
    w->copy();
}

void FileTabWidget::paste() {
    auto *w = dynamic_cast<textEdit *>(currentWidget());
    if (not w) return;
    w->paste();
}

void FileTabWidget::selectAll() {
    auto *w = dynamic_cast<textEdit *>(currentWidget());
    if (not w) return;
    w->selectAll();
}

void FileTabWidget::onCurrentChanged(int index) {
    CustomMessages::print("current changed to %1 from %2", index, currentTabIndex);
    auto *w = dynamic_cast<textEdit *>(currentWidget());
    if (not w) return;
    if (currentTabIndex != -1) {
        auto *previous = dynamic_cast<textEdit *>(widget(currentTabIndex));
        if (previous)
            QObject::disconnect(previous, SIGNAL(textChanged()),
                                this, SLOT(onTextChanged()));
    }
    highlighter->setDocument(w->document());
    highlighter->updateExtension(tabText(index));
    highlighter->rehighlight();
    currentTabIndex = index;
    QObject::connect(w, SIGNAL(textChanged()),
                     this, SLOT(onTextChanged()));
}

void FileTabWidget::onCursorPositionChanged() {
    auto *w = dynamic_cast<textEdit *>(sender());
    QTextCursor cursor;
    if (w)
        cursor = w->textCursor();
    else
        cursor = dynamic_cast<textEdit *>(currentWidget())->textCursor();
    auto pos1 = cursor.position();
    cursor.movePosition(QTextCursor::StartOfLine);
    auto col = pos1 - cursor.position() + 1;
    int line = 1;
    while (cursor.positionInBlock() > 0) {
        cursor.movePosition(QTextCursor::Up);
        line++;
    }
    QTextBlock block = cursor.block().previous();

    while (block.isValid()) {
        line += block.lineCount();
        block = block.previous();
    }
    emit cursorPositionChanged(line, col);
}

