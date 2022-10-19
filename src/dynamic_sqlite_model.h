#pragma once

#include <QAbstractTableModel>

class DynamicSQLiteModel final : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DynamicSQLiteModel(QObject *parent = nullptr);
    virtual ~DynamicSQLiteModel() { }

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const final;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const final;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const final;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const final;

};
