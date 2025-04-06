#pragma once

#include <QtWidgets/QMainWindow>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeView>
#include <QAction>
#include <QVBoxLayout>
#include "Parser.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_file_menu();
    void on_close_all_files();
    void on_exit();
    void on_open_context_menu(const QPoint& pos);
    void on_close_file();
    void on_open_in_new_tab();

    void search_button_clicked();
    void next_button_clicked();
    void prev_button_clicked();

private:

    QVBoxLayout *layout;
    QWidget *cw;
    QLineEdit *searchBox;
    QLabel *searchResultLabel;
    QModelIndexList searchResult;
    int currentSearchIndex = 0;
    Parser* parser;
    QTreeView* view;
    QTabWidget* tabs;
    QTreeView* createNewTab(const QString& title);
};
