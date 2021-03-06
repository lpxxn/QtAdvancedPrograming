#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ProxyModel(QObject *parent = 0);

    int minimumZipcode() const { return m_minimumZipcode; }
    int maximumZipcode() const { return m_maximumZipcode; }
    QString county() const { return m_county; }
    QString state() const { return m_state; }



signals:

public slots:
    void clearFilters();
    void setMinimumZipcode(int minimumZipcode);
    void setMaximumZipcode(int maximumZipcode);
    void setCounty(const QString &county);
    void setState(const QString &state);

private:
    int m_minimumZipcode;
    int m_maximumZipcode;
    QString m_county;
    QString m_state;

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // PROXYMODEL_H
