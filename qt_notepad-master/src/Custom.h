#pragma once

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

namespace CustomDialogs {
    QString getFilepathToOpen();

    QString getFilepathToSave();
}

namespace CustomMessages {
    void print(const QString &format);

    template<typename... Args, typename T>
    void print(const QString &format, T first, Args... args) {
        print(format.arg(first), args...);
    }

    template<typename T>
    void print(const QString &format, T first) {
        qDebug() << format.arg(first);
    }
}

namespace CustomMessageBoxes {
    void Error(const QString &msg);

    void Warning(const QString &msg);

    void Info(const QString &msg);

    int CloseUnsavedFileChoice(const QString &path);

    bool AcceptMessage(const QString &msg);
}