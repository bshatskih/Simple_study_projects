#pragma once

#include <QDialog>
#include <QDebug>
#include <QAbstractButton>

QT_BEGIN_NAMESPACE
namespace Ui { class multiple_unsaved_files; }
QT_END_NAMESPACE

class multiple_unsaved_files : public QDialog {
Q_OBJECT

public:
    explicit multiple_unsaved_files(const QVector<QPair<QString, QString>> &unsaved, QWidget *parent = nullptr);

    QPair<bool, QVector<bool>> execute();

    ~multiple_unsaved_files() override;

public slots:

    void onButtonClick(QAbstractButton *);

private:
    QStringList unsaved;
    Ui::multiple_unsaved_files *ui;
};