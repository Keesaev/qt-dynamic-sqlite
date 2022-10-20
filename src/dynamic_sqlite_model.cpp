#include "dynamic_sqlite_model.h"

#include <QDebug>

DynamicSQLiteModel::DynamicSQLiteModel(QObject* parent)
    : QAbstractTableModel { parent }
    , _db_instance("../test/test.db")
    , _db_table(_db_instance, "TEST_TABLE")
{
    _db_instance.connect();
}

int DynamicSQLiteModel::columnCount(const QModelIndex& parent) const
{
    return _db_table.column_count();
}

int DynamicSQLiteModel::rowCount(const QModelIndex& parent) const
{
    return _db_table.row_count();
}

QVariant DynamicSQLiteModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        auto row = _db_table.select(select_query(_db_table.table_name(), 1, index.row()));
        return row[0][index.column()];
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
            return section;
        }
    } else {
        return QVariant();
    }
}
