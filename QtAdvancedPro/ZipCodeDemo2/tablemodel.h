#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include "zpcodeitem.h"
class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0);

    // QAbstractItemModel interface
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);

    QString filename() const {return m_filename;}

    void load(const QString &filename=QString());
    void save(const QString &filename=QString());

signals:

public slots:

private:
    QString m_filename;

    QList<ZipcodeItem> zipcodes;


};

#endif // TABLEMODEL_H
