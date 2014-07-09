#include "standardtablemodel.h"

#include "global.h"
#include <QDataStream>
#include <QFile>
#include <QMap>
#include <QList>
#include <QDebug>

const qint32 MagicNumber = 0x5A697043;
const qint16 FormatNumber = 100;


StandardTableModel::StandardTableModel(QObject *parent) :
    QStandardItemModel(parent)
{
    initialize();
}

void StandardTableModel::initialize()
{
    setHorizontalHeaderLabels(QStringList()<<tr("Zipcode")
                              <<tr("Post office")<<tr("County")<<tr("State"));
}


QString StandardTableModel::filename() const { return m_filename; }

void StandardTableModel::clear()
{
    QStandardItemModel::clear();
    initialize();
}

void StandardTableModel::load(const QString &filename)
{
    qDebug()<<filename;
    if(!filename.isEmpty())
        m_filename = filename;
    if(m_filename.isEmpty())
        return;

    QFile file(m_filename);
    if(!file.open(QIODevice::ReadOnly))
        return;

    QDataStream in(&file);

    qint32 magincNumber;
    in >> magincNumber;
    if(magincNumber!=MagicNumber){}
        //return;
    qint16 formatVersionNumber;
    in >> formatVersionNumber;
    qDebug()<<"formatVersionNumber  "<<formatVersionNumber;
    if(formatVersionNumber > FormatNumber){}
            //return;
    in.setVersion(QDataStream::Qt_5_3);
    clear();

    quint16 zipcode;
    QString postOffice;
    QString county;
    QString state;

    QMap<quint16,QList<QStandardItem *> > itemsForZipcode;

    while (!in.atEnd()) {
        in >> zipcode >> postOffice >> county >> state;
        QList<QStandardItem*> items;
        QStandardItem *item = new QStandardItem;
        item->setData(zipcode, Qt::EditRole);
        items << item;
        foreach (const QString &text, QStringList() << postOffice
                                      << county << state)
            items << new QStandardItem(text);
        itemsForZipcode[zipcode] = items;
    }

    QMapIterator<quint16, QList<QStandardItem*> > i(itemsForZipcode);
    qDebug()<<"itemsForZipcode count"<<itemsForZipcode.count();
    while (i.hasNext())
        appendRow(i.next().value());
}

void StandardTableModel::save(const QString &filename)
{
    if(!filename.isEmpty())
        m_filename = ":/QtCode/QTCODEDEMO/build-ZipCodeDemo1-win32-Debug/a1.dat";//filename;
    if(m_filename.isEmpty()) {
        qDebug()<<"save false isempty";
        return;
    }

    QFile file(m_filename);

    if(!file.open((QIODevice::WriteOnly)))
        qDebug()<<"save false open";
    QDataStream out(&file);
    out<<MagicNumber<<FormatNumber;
    out.setVersion(QDataStream::Qt_5_3);

    for(int row=0;row<rowCount();++row) {
        out<<static_cast<quint16>(
                 item(row,Zipcode)->data(Qt::EditRole).toUInt())
             << item(row,PostOffice)->text()
             << item(row, County)->text() << item(row, State)->text();

        qDebug()<<static_cast<quint16>(
                 item(row,Zipcode)->data(Qt::EditRole).toUInt())
             << item(row,PostOffice)->text()
             << item(row, County)->text() << item(row, State)->text();
    }
}


