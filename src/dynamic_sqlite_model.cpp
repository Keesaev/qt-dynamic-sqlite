#include "dynamic_sqlite_model.h"

#include <QDebug>

DynamicSQLiteModel::DynamicSQLiteModel(QObject *parent)
    : QAbstractTableModel{parent}
{

}

int DynamicSQLiteModel::columnCount(const QModelIndex &parent) const {
    return 3; // TODO
}

int DynamicSQLiteModel::rowCount(const QModelIndex &parent) const {
    return 100; // TODO
}

QVariant DynamicSQLiteModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole){
        return "SOME DATA";
    }
    else{
        return QVariant();
    }
}

QVariant DynamicSQLiteModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole){
        if (orientation == Qt::Horizontal) {
            QVariantList headers { "ID", "Name", "Code" };
            return headers[section];
        } else {
            return section;
        }
    }
    else{
        return QVariant();
    }
}
