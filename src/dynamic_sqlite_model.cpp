#include "dynamic_sqlite_model.h"

#include <QDebug>

DynamicSQLiteModel::DynamicSQLiteModel(QString tableName, QObject* parent)
    : QAbstractTableModel { parent }
    , _tableName { tableName }
    , _db_instance("../test/test.db") // <TODO pass instance instead of constructing
    , _db_table(_db_instance, "TEST_TABLE")
    , _cache(&_db_table, SelectQuery(_db_table.tableName())),
      _filters(_db_table.columnCount())
{
    qRegisterMetaType<TableRow>("TableRow");
    qRegisterMetaType<std::vector<TableRow>>("std::vector<TableRow>");

    _db_instance.connect();
    _rowCount = _db_table.rowCount(LikeQuery(_db_table.columnNames()).addFilters(_filters));

    connect(&_cache, &CacheController::cacheCompleted, this, &DynamicSQLiteModel::cacheCompleted);
}

int DynamicSQLiteModel::columnCount(const QModelIndex& parent) const
{
    return _db_table.columnCount();
}

int DynamicSQLiteModel::rowCount(const QModelIndex& parent) const
{
    return _rowCount;
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
    emit dataChanged(
        index(window.left(), 0),
        index(window.right() - 1, _db_table.columnCount() - 1),
        { Qt::DisplayRole });
}

void DynamicSQLiteModel::changeFilter(QString const& text, int column){
    qDebug() << "CHANGE FILTER " << text << " " << column;
    beginResetModel();
    _filters[column] = text.toStdString();
    _rowCount = _db_table.rowCount(LikeQuery(_db_table.columnNames()).addFilters(_filters));
    _cache.query(
        SelectQuery(_db_table.tableName())
            .like(LikeQuery(_db_table.columnNames())
                      .addFilters(_filters)));
    endResetModel();
}


