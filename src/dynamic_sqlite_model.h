#pragma once

#include <QAbstractTableModel>

#include "db/db_test_table.h"

class DynamicSQLiteModel final : public QAbstractTableModel {
    Q_OBJECT

    db_instance _db_instance;
    db_test_table _db_table;

public:
    explicit DynamicSQLiteModel(QObject* parent = nullptr);
    virtual ~DynamicSQLiteModel() { }

    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const final;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const final;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const final;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const final;
};
