#include "MainWindow.h"
#include <qxmlstream.h>
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto myMenu = new QMenu{tr("Menu") };
    auto openFileAction = new QAction{tr("Open file"), this };
    myMenu->addAction(openFileAction);
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(on_open_file_menu()));

    auto closeAllFilesAction = new QAction{tr("Close all files"), this };
    myMenu->addAction(closeAllFilesAction);
    connect(closeAllFilesAction, SIGNAL(triggered()), this, SLOT(on_close_all_files()));

    auto exitAction = new QAction{tr("Exit"), this };
    myMenu->addAction(exitAction);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(on_exit()));

    menuBar()->addMenu(myMenu);

    cw = new QWidget(this);

    layout = new QVBoxLayout(cw);


    auto searchWidget = new QWidget(cw);
    layout->addWidget(searchWidget);

    auto searchVlayout = new QVBoxLayout(searchWidget);
    auto searchBoxWidget = new QWidget();

    searchVlayout->addWidget(searchBoxWidget);

    searchResultLabel = new QLabel(searchWidget);

    searchVlayout->addWidget(searchResultLabel);

    auto searchLayout = new QHBoxLayout(searchWidget);
    searchBoxWidget->setLayout(searchLayout);
    searchWidget->setLayout(searchVlayout);

    searchBox = new QLineEdit(searchWidget);
    auto searchButton = new QPushButton("Search", searchWidget);
    auto prevButton = new QPushButton("<--", searchWidget);
    auto nextButton = new QPushButton("-->", searchWidget);

    searchLayout->addWidget(prevButton);
    searchLayout->addWidget(nextButton);

    connect(searchButton, SIGNAL(clicked()), this, SLOT(search_button_clicked()));
    connect(prevButton, SIGNAL(clicked()), this, SLOT(prev_button_clicked()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next_button_clicked()));



    searchLayout->addWidget(searchBox);
    searchLayout->addWidget(searchButton);



    tabs = new QTabWidget(cw);
    view = new QTreeView(tabs);
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    view->setHeaderHidden(true);

    parser = new Parser(view);

    view->setModel(parser);

    connect(view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_open_context_menu(QPoint)));

    tabs->addTab(view, "Tab 1");
    tabs->setCurrentIndex(tabs->indexOf(view));

    layout->addWidget(tabs);

    cw->setLayout(layout);
    setCentralWidget(cw);
}

MainWindow::~MainWindow() {
    delete parser;
    delete view;
}

void MainWindow::on_open_file_menu() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a file to open"), QDir::homePath(), tr("XML ����� (*.xml)"));
    parser->LoadFile(fileName);


  view->reset();
}

void MainWindow::on_close_all_files() {
    parser->closeAll();
    view->reset();
}

void MainWindow::on_exit() {
    close();
}

void MainWindow::on_close_file() {
    auto* currentTreeView = qobject_cast<QTreeView*>(tabs->currentWidget());
    auto* currentModel = qobject_cast<Parser*>(currentTreeView->model());
    auto currentIndex = currentTreeView->currentIndex();
    currentModel->removeRow(currentIndex.row());
    view->reset();
}

void MainWindow::on_open_in_new_tab() {
    auto* currentTreeView = qobject_cast<QTreeView*>(tabs->currentWidget());
    auto* currentModel = qobject_cast<Parser*>(currentTreeView->model());
    auto currentIndex = currentTreeView->currentIndex();

    auto* newTreeView = createNewTab("Tab ");
    auto* newModel = qobject_cast<Parser*>(newTreeView->model());;
    newModel->append(currentIndex);

    currentModel->removeRow(currentIndex.row());
}

QTreeView* MainWindow::createNewTab(const QString& title) {
    auto* tv = new QTreeView(tabs);
    tv->setHeaderHidden(true);
    auto* model = new Parser(tv);
    tv->setModel(model);
    static int i = 1;
    tabs->addTab(tv, title + QString::number(++i));
    tabs->setCurrentIndex(tabs->indexOf(tv));
    return tv;
}

void MainWindow::on_open_context_menu(const QPoint& pos) {
    if (view->currentIndex().parent() == view->rootIndex()) {
        QMenu* menu = new QMenu(this);
        auto actionActive = new QAction{ tr("Close"), this };
        menu->addAction(actionActive);
        connect(actionActive, &QAction::triggered,this, &MainWindow::on_close_file);
        if (parser->rowCount() >=2 ) {
            auto newtab = new QAction{ tr("Open in new tab"), this };
            menu->addAction(newtab);
            connect(newtab, &QAction::triggered, this, &MainWindow::on_open_in_new_tab);
        }
        menu->popup(view->viewport()->mapToGlobal(pos));
    }

}
void MainWindow::next_button_clicked() {
  if(searchResult.empty())
    return;
  if(currentSearchIndex+1 < searchResult.size()){
    currentSearchIndex++;
  }
  else{
    currentSearchIndex = 0;
  }
  view->setCurrentIndex(searchResult.at(currentSearchIndex));
}
void MainWindow::search_button_clicked() {
  searchResult = parser->match(parser->index(0,0), Qt::DisplayRole, QVariant::fromValue(searchBox->text()),-1, Qt::MatchRecursive | Qt::MatchContains);
  if(!searchResult.empty()){
    currentSearchIndex = 0;
    view->setCurrentIndex(searchResult.at(currentSearchIndex));
  }
  QString resultString = "Результатов запроса: " + QString::number(searchResult.size());
  searchResultLabel->setText(resultString);
}
void MainWindow::prev_button_clicked() {
  if(searchResult.empty())
    return;
  if (currentSearchIndex - 1 >= 0) {
    currentSearchIndex--;
  } else
    currentSearchIndex = searchResult.size() - 1;

  view->setCurrentIndex(searchResult.at(currentSearchIndex));
}





