#ifndef UNIQUEPROXYMODEL_H
#define UNIQUEPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QSet>
class UniqueProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit UniqueProxyModel(int column,QObject * parent = 0);
    void setSourceModel(QAbstractItemModel *sourceModel);

signals:

public slots:
    void clearCache(){ cache.clear();}



    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    int Column;
    mutable QSet<QString> cache;
};

#endif // UNIQUEPROXYMODEL_H
