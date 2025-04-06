#include <QVBoxLayout>
#include <QLabel>
#include "Custom.h"

QString CustomDialogs::getFilepathToOpen() {
    return QFileDialog::getOpenFileName(nullptr, "Выберите файл");
}

QString CustomDialogs::getFilepathToSave() {
    return QFileDialog::getSaveFileName(nullptr, "Сохранение файла");
}

void CustomMessageBoxes::Error(const QString &msg) {
    QMessageBox box(QMessageBox::Icon::Critical, "Ошибка",
                    msg,
                    QMessageBox::Close);
    box.exec();
    CustomMessages::print("[ERROR] %1", msg);
}

void CustomMessageBoxes::Warning(const QString &msg) {
    QMessageBox box(QMessageBox::Icon::Warning, "Предупреждение",
                    msg,
                    QMessageBox::Close);
    box.exec();
    CustomMessages::print("[WARNING] %1", msg);
}

void CustomMessageBoxes::Info(const QString &msg) {
    QMessageBox box(QMessageBox::Icon::Information, "Информация",
                    msg,
                    QMessageBox::Close);
    box.exec();
    CustomMessages::print("[Info] %1", msg);
}

int CustomMessageBoxes::CloseUnsavedFileChoice(const QString &path) {
    QMessageBox box(QMessageBox::Icon::Question, "Файл не сохранен",
                    QString("Вы хотите закрыть несохраненный файл '%1'\nСохранить изменения?").arg(path),
                    QMessageBox::Discard | QMessageBox::Yes | QMessageBox::Close);
    return box.exec();
}

bool CustomMessageBoxes::AcceptMessage(const QString &msg) {
    QMessageBox box(QMessageBox::Icon::Question, "Подтверждение",
                    QString("Вы действительно хотите %1?").arg(msg),
                    QMessageBox::Yes | QMessageBox::No);
    return box.exec() == QMessageBox::Yes;
}

void CustomMessages::print(const QString &format) {
    qDebug() << format;
}
