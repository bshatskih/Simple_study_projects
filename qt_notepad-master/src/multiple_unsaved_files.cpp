#include "multiple_unsaved_files.h"
#include "ui_multiple_unsaved_files.h"
#include <QTableWidgetItem>
#include <QFile>


multiple_unsaved_files::multiple_unsaved_files(const QVector<QPair<QString, QString>> &unsaved, QWidget *parent) :
        QDialog(parent), ui(new Ui::multiple_unsaved_files) {
    ui->setupUi(this);
    ui->buttonBox->addButton("Выделить все", QDialogButtonBox::ButtonRole::ActionRole);
    ui->buttonBox->addButton("Убрать выделение", QDialogButtonBox::ButtonRole::ActionRole);
    ui->buttonBox->addButton("Отмена", QDialogButtonBox::ButtonRole::RejectRole);
    ui->buttonBox->addButton("Сохранить выделенные", QDialogButtonBox::ButtonRole::AcceptRole);
    ui->unsavedFilesTable->setRowCount(unsaved.count());
    ui->unsavedFilesTable->setColumnCount(2);
    ui->unsavedFilesTable->verticalHeader()->hide();
    ui->unsavedFilesTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    QStringList headerLabels;
    headerLabels << "Имя" << "Путь";
    ui->unsavedFilesTable->setHorizontalHeaderLabels(headerLabels);
    auto i{0};
    for (const auto &[file, path]: unsaved) {
        auto *file_item = new QTableWidgetItem();
        file_item->setData(Qt::DisplayRole, file);
        ui->unsavedFilesTable->setItem(i, 0, file_item);
        auto *path_item = new QTableWidgetItem();
        path_item->setData(Qt::DisplayRole, path);
        ui->unsavedFilesTable->setItem(i, 1, path_item);
        i++;
    }
    ui->unsavedFilesTable->resizeColumnsToContents();
    QFile stylesheet(":/Dark.qss");
    if (stylesheet.open(QIODevice::ReadOnly)) {
        auto s = stylesheet.readAll();
        setStyleSheet(s);
    }
}

multiple_unsaved_files::~multiple_unsaved_files() {
    delete ui;
}

QPair<bool, QVector<bool>> multiple_unsaved_files::execute() {
    auto res = exec();
    QVector<bool> result;

    if (res) {
        auto selection = ui->unsavedFilesTable->selectedItems();
        for (int i = 0; i < ui->unsavedFilesTable->rowCount(); ++i) {
            auto *name = ui->unsavedFilesTable->item(i, 0);
            auto *path = ui->unsavedFilesTable->item(i, 1);
            result << (selection.contains(name) or selection.contains(path));
        }
        return {true, result};
    } else {
        return {false, result};
    }
}

void multiple_unsaved_files::onButtonClick(QAbstractButton *button) {
    auto buttonText = button->property("text").toString();
    if (buttonText == "Выделить все") {
        qDebug() << "Yes to all";
        ui->unsavedFilesTable->selectAll();
    } else if (buttonText == "Убрать выделение") {
        qDebug() << "No to all";
        ui->unsavedFilesTable->clearSelection();
    } else if (buttonText == "Отмена") {
        qDebug() << "cancel";
        setResult(0);
        reject();
    } else if (buttonText == "Сохранить выделенные") {
        qDebug() << "apply";
        setResult(1);
        accept();
    } else {
        setResult(0);
        reject();
    }
}

//comment
