#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "multiple_unsaved_files.h"
#include "Custom.h"
#include <QToolBar>
#include <QStringListModel>


mainwindow::mainwindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);
    fileSystemModel = new QFileSystemModel(this);
    auto path = QDir::currentPath();
    fileSystemModel->setRootPath(path);

    ui->currentDirLabel->setText(QDir::toNativeSeparators(path).split(QDir::separator()).back());
    
    ui->fileSystem->setModel(fileSystemModel);
    ui->fileSystem->setRootIndex(fileSystemModel->index(QDir::currentPath()));
    ui->fileSystem->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // скрыть все колонки кроме имён файлов
    ui->fileSystem->hideColumn(1);
    ui->fileSystem->hideColumn(2);
    ui->fileSystem->hideColumn(3);

    auto *tb = new QToolBar("toolBar", this);
    tb->addAction(ui->newdoc);
    tb->addAction(ui->opendoc);
    tb->addAction(ui->savedoc);
    tb->addAction(ui->saveas);
    tb->addAction(ui->saveall);
    tb->addAction(ui->close);
    tb->addAction(ui->quit);
    tb->addAction(ui->cut);
    tb->addAction(ui->copy);
    tb->addAction(ui->paste);
    tb->addAction(ui->selectall);
    addToolBar(tb);

    showMaximized();
    setWindowTitle("Code editor");
    updateOpenedFilesList();

    caretPosition = new QLabel(this);
    statusBar()->addPermanentWidget(caretPosition);
    QObject::connect(ui->tabWidget, SIGNAL(currentChanged(int)),
                     this, SLOT(onTabChanged(int)));
    QObject::connect(ui->tabWidget, SIGNAL(cursorPositionChanged(int, int)),
                     this, SLOT(onCursorPositionChanged(int, int)));


    ui->closeall->setIcon(QIcon(":/close-all.png"));
    ui->close->setIcon(QIcon(":/close-document.png"));
    ui->copy->setIcon(QIcon(":/copy.png"));
    ui->cut->setIcon(QIcon(":/cut.png"));
    ui->quit->setIcon(QIcon(":/exit.png"));
    ui->newdoc->setIcon(QIcon(":/new-document.png"));
    ui->opendoc->setIcon(QIcon(":/open-document.png"));
    ui->paste->setIcon(QIcon(":/paste.png"));
    ui->savedoc->setIcon(QIcon(":/save.png"));
    ui->saveall->setIcon(QIcon(":/save-all.png"));
    ui->saveas->setIcon(QIcon(":/save-as.png"));
    ui->selectall->setIcon(QIcon(":/select-all.png"));
}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::changeTheme(bool status) {
  if(status){
    QFile stylesheet(":/Dark.qss");
    if (stylesheet.open(QIODevice::ReadOnly)) {
      auto s = stylesheet.readAll();
      setStyleSheet(s);
    }
  }
  else{
    setStyleSheet("");
  }
}

void mainwindow::onFilesystemDoubleClicked(const QModelIndex &index) {
    auto filepath = index.data(QFileSystemModel::FilePathRole).toString();
    if (filepath.isEmpty()) {
        // opened files list was clicked
        ui->tabWidget->setCurrentIndex(index.row());
        return;
    }
    if (not mainwindow::validateFile(filepath)) {
        QFile f(filepath);
        QFileInfo info(f);
        if (info.isDir()) {
            qDebug() << "set root" << filepath;
            ui->fileSystem->setRootIndex(index);
            ui->currentDirLabel->setText(QDir::toNativeSeparators(filepath).split(QDir::separator()).back());
        }
        return;
    }
    qDebug() << filepath;
    ui->tabWidget->openFile(filepath);
    updateOpenedFilesList();
    statusBar()->showMessage(tr("Открыт существующий файл %1").arg(filepath), 5000); //!!! Нужно использовать tr()
}

void mainwindow::newDocument() {
    qDebug() << "newDocument";
    ui->tabWidget->openNewUntitled();
    updateOpenedFilesList();
    statusBar()->showMessage(tr("Создан новый файл"), 5000); //!!! Нужно использовать tr()
}

void mainwindow::openDocument() {
    qDebug() << "openDocument";
    auto filepath = CustomDialogs::getFilepathToOpen();
    if (filepath.isEmpty()) {
        CustomMessageBoxes::Warning(tr("Файл не выбран")); //!!! Нужно использовать tr()
        qDebug() << "no filepath specified";
        return;
    }
    ui->tabWidget->openFile(filepath);
    updateOpenedFilesList();
    statusBar()->showMessage(tr("Открыт существующий файл %1").arg(filepath), 5000); //!!! Нужно использовать tr() и т.д.
}

void mainwindow::saveDocument() {
    qDebug() << "saveDocument";
    if (ui->tabWidget->saveCurrent()) {
        updateOpenedFilesList();
        statusBar()->showMessage(
                QString("Файл %1 успешно сохранен").arg(ui->tabWidget->tabText(ui->tabWidget->currentIndex())), 5000);
    }
}

void mainwindow::saveDocumentAs() {
    qDebug() << "saveDocumentAs";
    if (ui->tabWidget->saveCurrentAs()) {
        updateOpenedFilesList();
        statusBar()->showMessage(
                QString("Файл %1 успешно сохранен").arg(ui->tabWidget->tabText(ui->tabWidget->currentIndex())), 5000);
    }
}

void mainwindow::saveAllDocuments() {
    qDebug() << "saveAllDocuments";
    for (int i = 0; i < ui->tabWidget->count(); ++i) {
        ui->tabWidget->save(i);
    }
    updateOpenedFilesList();
    statusBar()->showMessage("Сохранение всех документов закончено", 5000);
}

void mainwindow::closeDocument() {
    qDebug() << "closeDocument";
    auto index = ui->tabWidget->currentIndex();
    if (index == -1) {
        CustomMessageBoxes::Info("Закрывать нечего. Файл не выбран.");
        return;
    } else {
        auto file = ui->tabWidget->tabText(index);
        ui->tabWidget->closeByIndex(index);
        updateOpenedFilesList();
        statusBar()->showMessage(QString("Файл %1 успешно закрыт").arg(file));
    }
}

bool mainwindow::closeAllDocuments() {
    qDebug() << "closeAllDocuments";
    QVector<QPair<QString, QString>> unsaved;
    for (int i = 0; i < ui->tabWidget->count(); ++i) {
        auto *w = dynamic_cast<textEdit *>(ui->tabWidget->widget(i));
        if (not w) continue;
        if (not w->isChangesSaved()) {
            auto name = ui->tabWidget->tabText(i);
            auto filepath = w->getFilepath();
            unsaved << qMakePair(name, filepath);
        }
    }
    if (unsaved.count() > 1) {
        auto dialog = multiple_unsaved_files(unsaved, this);
        auto [success, what_to_save] = dialog.execute();
        if (not success) return false;
        for (int i = 0; i < unsaved.count(); ++i) {
            CustomMessages::print("%1   %2", unsaved[i].first, (what_to_save[i] ? "true" : "false"));
            if (what_to_save[i])
                ui->tabWidget->save(i);
        }
        while (ui->tabWidget->count() > 0) {
            ui->tabWidget->removeTab(0);
        }
        updateOpenedFilesList();
        return true;
    }
    if (ui->tabWidget->closeAll()) {
        updateOpenedFilesList();
        statusBar()->showMessage("Закрытие всех документов закончено", 5000);
        return true;
    }
    return false;
}

bool mainwindow::quit() {
    qDebug() << "quit";
    if (closeAllDocuments()) {
        if (ui->tabWidget->count() != 0) {
            CustomMessageBoxes::Info("Не все файлы закрыты! Выйти невозможно.");
            return false;
        }
        if (CustomMessageBoxes::AcceptMessage("выйти")) {
            QApplication::closeAllWindows();
            QApplication::quit();
            return true;
        }
    }
    return false;
}

void mainwindow::cut() {
    qDebug() << "cut";
    ui->tabWidget->cut();
}

void mainwindow::copy() {
    qDebug() << "copy";
    ui->tabWidget->copy();
}

void mainwindow::paste() {
    qDebug() << "paste";
    ui->tabWidget->paste();
}

//void mainwindow::remove() {
//    qDebug() << "remove";
//    auto i = ui->tabWidget->currentIndex();
//    if (i == -1) {
//        qDebug() << "nothing to delete";
//        return;
//    }
//    auto text = ui->tabWidget->tabText(i);
//    ui->tabWidget->closeByIndex(i);
//    text = ui->tabWidget->tabText(i);
//    if (text == "untitled*" or text == "Welcome") return;
//    ui->tabWidget->remove();
//}

void mainwindow::selectAll() {
    qDebug() << "selectAll";
    ui->tabWidget->selectAll();
}

//void mainwindow::showFilesystemExplorer() {
//    qDebug() << "showFilesystemExplorer";
//}
//
//void mainwindow::showOpenedFilesExplorer() {
//    qDebug() << "showOpenedFilesExplorer";
//}

void mainwindow::updateOpenedFilesList() {
    QStringList files;
    for (int i = 0; i < ui->tabWidget->count(); ++i) {
//        auto filepath = dynamic_cast<textEdit *>(ui->tabWidget->widget(i))->getFilepath();
//        if (filepath.isEmpty())
        files << ui->tabWidget->tabText(i);
//        else
//            files << filepath;
    }
    auto *model = new QStringListModel(files, this);
    ui->openedFilesList->setModel(model);
    ui->openedFilesList->show();
}

void mainwindow::onTabChanged(int index) {
    if (index == -1) {
        caretPosition->setVisible(false);
    } else {
        caretPosition->setVisible(true);
        ui->tabWidget->onCursorPositionChanged();
    }
}

void mainwindow::onCursorPositionChanged(int line, int col) {
    auto text = QString("%1:%2").arg(line).arg(col);
    caretPosition->setText(text);
}

void mainwindow::updateExplorerStates() {
    ui->showfilesystem->setChecked(ui->fileSystemDock->isVisible());
    ui->showopened->setChecked(ui->openedFilesDock->isVisible());
}

void mainwindow::closeEvent(QCloseEvent *event) {
    if (quit()) {
        QWidget::closeEvent(event);
        event->accept();
    } else {
        event->ignore();
    }
}

bool mainwindow::validateFile(const QString &path) {
    QFile f(path);
    QFileInfo info(f);
    if (info.isDir()) {
        CustomMessages::print("Невозможно открыть '%1', так как это папка", path);
        return false;
    }
    if (not info.isFile()) {
        CustomMessageBoxes::Warning(QString("'%1' не является файлом").arg(info.fileName()));
        return false;
    }
    if (not info.isReadable()) {
        CustomMessageBoxes::Warning(QString("'%1' недоступен для чтения").arg(info.fileName()));
        return false;
    }
    if (not info.isWritable()) {
        CustomMessageBoxes::Warning(QString("'%1' недоступен для записи").arg(info.fileName()));
        return false;
    }
    if (info.isExecutable()) {
        CustomMessageBoxes::Warning(QString("'%1' - исполняемый файл").arg(info.fileName()));
        return false;
    }
    return true;
}

void mainwindow::goToParentDirectory() {
    QModelIndex currentRoot = ui->fileSystem->rootIndex();
    if (currentRoot.parent().isValid()) {
        ui->fileSystem->setRootIndex(currentRoot.parent());
        auto upDir = qvariant_cast<QString>(ui->fileSystem->rootIndex().data());
        CustomMessages::print("Switched to parent directory: %1", upDir);
        ui->currentDirLabel->setText(upDir);
    }
}
