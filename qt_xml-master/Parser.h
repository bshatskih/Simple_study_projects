#pragma once
#include <QAbstractItemModel>
#include <QFile>
#include <QMessageBox>
#include <QModelIndex>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStack>
#include <QPersistentModelIndex>
#include <QMessageBox>
#include <QStandardItem>
#include <QVector>
#include <QVariant>
#include <QtXml/QDomDocument>

class Parser : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit Parser(QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& child) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    void append(const QModelIndex& index);

    void LoadFile(const QString& fileName);
    void closeAll();

private:
    QStandardItem* mainRoot;
    QPersistentModelIndex focused;
    void append(const QModelIndex& index, QStandardItem*);  
};





