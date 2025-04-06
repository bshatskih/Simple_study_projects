#include "Parser.h"
#include <QMessageBox>
#include <QAbstractItemModel>
#include <QFile>
#include <QXmlStreamReader>
#include <QStack>
#include <qfileinfo.h>

Parser::Parser(QObject* parent) : QAbstractItemModel(parent),
                                  focused() {
    mainRoot = new QStandardItem();
}

QVariant Parser::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return {};
    }
    if (role != Qt::DisplayRole) {
        return {};
    }
    auto* item = static_cast<QStandardItem*>(index.internalPointer());
    return item->data(index.column());
};


QModelIndex Parser::index(int row, int column, const QModelIndex& parent) const {
    QStandardItem* parentItem;
    if (!parent.isValid()) {
        parentItem = mainRoot;
    }
    else {
        parentItem = static_cast<QStandardItem*>(parent.internalPointer());
    }
    QStandardItem* descendantItem = parentItem->child(row);
    if (descendantItem) {
        return createIndex(row, column, descendantItem);
    }
    return {};
}

QModelIndex Parser::parent(const QModelIndex& descendant) const {
    if (!descendant.isValid()) {
        return QModelIndex{};
    }
    auto* descendantItem = static_cast<QStandardItem*>(descendant.internalPointer());
    QStandardItem* parentItem = descendantItem->parent();
    if (parentItem == mainRoot || descendantItem == mainRoot) {
        return {};
    }
    return createIndex(parentItem->row(), 0, parentItem);
}

int Parser::rowCount(const QModelIndex& parent) const {
    QStandardItem* parentItem;
    if (parent.column() > 0) {
        return 0;
    }
    if (!parent.isValid()) {
        parentItem = mainRoot;
    }
    else {
        parentItem = static_cast<QStandardItem*>(parent.internalPointer());
    }
    return parentItem->rowCount();

}

int Parser::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return static_cast<QStandardItem*>(parent.internalPointer())->columnCount();
    }
    return mainRoot->columnCount();
}


void Parser::LoadFile(const QString& fileName) {
    auto* xmlReader = new QXmlStreamReader;
    QFile file{ fileName };
    QFileInfo f(fileName);
    QStack<int> counterStack;
    QStack<int> layerStack;


    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox message(QMessageBox::Critical, tr("ERROR!"), tr("Fail to open file!"), QMessageBox::Ok);
        message.exec();
    }

    xmlReader->setDevice(&file);

    auto fileNode = new QStandardItem(f.fileName());
    mainRoot->appendRow(fileNode);
    QStandardItem* currentNode = fileNode;

    int currentLayer = 0;
    while (!xmlReader->atEnd() && !xmlReader->hasError()) {
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        if (token == QXmlStreamReader::StartElement) {
            ++currentLayer;
            auto text = xmlReader->name().toString();

            if (text == "array") {
                if (layerStack.isEmpty() || currentLayer != layerStack.top()) {
                    counterStack.append(0);
                    layerStack.append(currentLayer);
                }
                text = QString("Element %1").arg(counterStack.top() + 1);
                ++counterStack.top();
            }

            auto node = new QStandardItem(text);
            currentNode->appendRow(node);
            currentNode = node;
        }

        if (token == QXmlStreamReader::Characters) {
            auto node = new QStandardItem{xmlReader->text().toString()};
            currentNode->appendRow(node);
        }

        if (token == QXmlStreamReader::EndElement) {
            --currentLayer;
            currentNode = currentNode->parent();
            auto text = xmlReader->name().toString();
            if (text == "array" && currentLayer + 1 != layerStack.top()) {
                counterStack.pop();
                layerStack.pop();
            }
        }
    }

    if (xmlReader->hasError()) {
        QMessageBox message(QMessageBox::Critical, tr("Parsing error!"), tr("This XML document cannot be displayed!"), QMessageBox::Ok);
        message.exec();

    }
    file.close();
}

bool Parser::removeRows(int row, int count, const QModelIndex& parent) {
    QModelIndex correctParent;
    if (parent.isValid())
        correctParent = parent;
    else
        correctParent = QModelIndex();
    auto start = row;
    auto stop = start + count - 1;
    beginRemoveRows(correctParent, start, stop);
    mainRoot->removeRows(start, count);
    endRemoveRows();
    return true;
}

void Parser::append(const QModelIndex& index) {
    if (not index.isValid())
        return;
    beginResetModel();
    auto* clonedItem = static_cast<QStandardItem*>(index.internalPointer())->clone();
    mainRoot->appendRow(clonedItem);
    append(index, clonedItem);
    endResetModel();
}

void Parser::append(const QModelIndex& sourceIndex, QStandardItem* item) {
    if (not sourceIndex.isValid())
        return;
    for (int i = 0; i < rowCount(sourceIndex); ++i) {
        auto child = sourceIndex.model()->index(i, 0, sourceIndex);
        auto* clonedItem = static_cast<QStandardItem*>(child.internalPointer())->clone();
        item->appendRow(clonedItem);
        append(child, clonedItem);
    }
}

void Parser::closeAll() {
    removeRows(0, mainRoot->rowCount(), createIndex(-1, -1, nullptr));
}




//On check
