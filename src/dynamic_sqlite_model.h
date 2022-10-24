#pragma once

#include <QAbstractTableModel>

#include "db/db_test_table.h"

#include "db/cache/cache_controller.h"

class DynamicSQLiteModel final : public QAbstractTableModel {
    Q_OBJECT

    const QString _tableName;

    DbInstance &_db_instance;
    DbTestTable _db_table;
    mutable CacheController _cache; // gets updated from const data() method

    std::vector<std::string> _filters;

    int _rowCount { -1 }; // cached row count

private slots:
    void cacheCompleted(CacheWindow window);

public:
    explicit DynamicSQLiteModel(DbInstance &instance, QString tableName, QObject* parent = nullptr);
    virtual ~DynamicSQLiteModel() { }

    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const final;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const final;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const final;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const final;

public slots:
    void changeFilter(QString const& text, int column);

};
