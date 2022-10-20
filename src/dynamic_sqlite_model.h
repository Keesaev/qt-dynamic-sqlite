#pragma once

#include <QAbstractTableModel>

#include "db/db_test_table.h"

class DynamicSQLiteModel final : public QAbstractTableModel {
    Q_OBJECT

    const QString _tableName;

    DbInstance _db_instance;
    DbTestTable _db_table;

public:
    explicit DynamicSQLiteModel(QString tableName, QObject* parent = nullptr);
    virtual ~DynamicSQLiteModel() { }

    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const final;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const final;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const final;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const final;
};
