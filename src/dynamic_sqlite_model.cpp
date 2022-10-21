#include "dynamic_sqlite_model.h"

#include <QDebug>

DynamicSQLiteModel::DynamicSQLiteModel(QString tableName, QObject* parent)
    : QAbstractTableModel { parent }
    , _tableName { tableName }
    , _db_instance("../test/test.db") // <TODO pass instance instead of constructing
    , _db_table(_db_instance, "TEST_TABLE")
    , _cache(&_db_table, SelectQuery(_db_table.tableName()))
{
    _db_instance.connect();
    connect(&_cache, &CacheController::cacheCompleted, this, &DynamicSQLiteModel::cacheCompleted);
}

int DynamicSQLiteModel::columnCount(const QModelIndex& parent) const
{
    return _db_table.columnCount();
}

int DynamicSQLiteModel::rowCount(const QModelIndex& parent) const
{
    return _db_table.rowCount();
}

QVariant DynamicSQLiteModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        return _cache.get(index.row())[index.column()];
    } else {
        return QVariant();
    }
}

QVariant DynamicSQLiteModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            QVariantList headers { "ID", "Name", "Code" };
            return headers[section];
        } else {
            return section + 1;
        }
    } else {
        return QVariant();
    }
}

void DynamicSQLiteModel::cacheCompleted(CacheWindow window){
    // TODO
}

