#pragma once

#include <QMainWindow>
#include <QStringList>
#include <QLabel>
#include <QDebug>
#include <QFileSystemModel>


//!!! Код ниже лишний. Все должно быть программно.

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE






class mainwindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);

    ~mainwindow() override;

protected:
    virtual void closeEvent(QCloseEvent *event) override;

public slots:

    void goToParentDirectory();

    void onFilesystemDoubleClicked(const QModelIndex &index);

    // Новый (Создание нового документа)
    void newDocument();

    // Открыть (Открытие существующего документа на основе QFileDialog)
    void openDocument();

    // Сохранить (Сохранение документа из активной вкладки)
    void saveDocument();

    // Сохранить как… (Сохранение в заданном формате на основе QFileDialog)
    void saveDocumentAs();

    // Сохранить все (Сохранить все открытые документы)
    void saveAllDocuments();

    // Закрыть (Закрыть текущий документ)
    void closeDocument();

    // Закрыть все (Закрытие всех открытых документов)
    bool closeAllDocuments();

    // Выход (Закрыть редактор с диалогом сохранения несохраненных документов)
    bool quit();

    void changeTheme(bool status);

    // Правка:
    // Вырезать
    void cut();

    // Копировать
    void copy();

    // Вставить
    void paste();

    // Удалить
//    void remove();

    // Выделить все *
    void selectAll();

    // Вид:
    // Показать проводник (Создание обозревателя каталогов с использованием QDockWidget и QFileSystemModel. При выборе документа в обозревателе открывать документ в новой вкладке.)
//    void showFilesystemExplorer();

    // Показать обозреватель открытых документов (Создание обозревателя открытых документов на основе QDockWidget и QStringListModel. При щелчке по имени документа должна становиться активной его вкладка.)
//    void showOpenedFilesExplorer();

    void onTabChanged(int);

    void onCursorPositionChanged(int, int);

    void updateExplorerStates();

private:
    Ui::mainwindow *ui;
    QFileSystemModel *fileSystemModel;
    QStringList openedFiles;
    QLabel *caretPosition;

    void updateOpenedFilesList();

    static bool validateFile(const QString &path);
};