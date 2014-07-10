#include <QFile>
#include <QDataStream>
#include <QList>
#include <QFontMetrics>
#include <QStyleOptionComboBox>
#include <qDebug>
#include "tablemodel.h"
#include "global.h"

const qint32 MagicNumber = 0x5A697043;
const qint16 FormatNumber = 100;
const int MaxColumns = 4;

QDataStream &operator <<(QDataStream &out ,const ZipcodeItem & item)
{
    out << static_cast<quint16>(item.zipcode) << item.postOffice
        << item.county << item.state;
    return out;
}

QDataStream &operator>>(QDataStream &in, ZipcodeItem &item)
{
    quint16 zipcode;
    in >> zipcode >> item.postOffice >> item.county >> item.state;
    item.zipcode = static_cast<int>(zipcode);
    return in;
}

TableModel::TableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

/*!
* \brief TableModel::flags
* 返回指定项(索引index)是否可用、是否有复选框、是否可编辑等
* \param index
* \return
*/
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractTableModel::flags(index);
    if(index.isValid()) {
        theFlags |= Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
    }
    return theFlags;
}


/*!
 * \brief TableModel::data
 * 返回指定的项(index)的角色(role)所对应的QVariant类型的值
 * \param index
 * \param role
 * \return
 */
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()
            ||index.row()<0
            ||index.row()>zipcodes.count()
            ||index.column()<0
            ||index.column()>=MaxColumns)
        return QVariant();

    const ZipcodeItem &item = zipcodes.at(index.row());
    if (role == Qt::SizeHintRole) {
        QStyleOptionComboBox option;
        switch (index.column()) {
            case Zipcode: {
                option.currentText = QString::number(MaxZipcode);
                const QString header = headerData(Zipcode,
                        Qt::Horizontal, Qt::DisplayRole).toString();
                if (header.length() > option.currentText.length())
                    option.currentText = header;
                break;
            }
            case PostOffice: option.currentText = item.postOffice;
                             break;
            case County: option.currentText = item.county; break;
            case State: option.currentText = item.state; break;
            default: Q_ASSERT(false);
        }
        QFontMetrics fontMetrics(data(index, Qt::FontRole)
                                 .value<QFont>());
        option.fontMetrics = fontMetrics;
        QSize size(fontMetrics.width(option.currentText),
                   fontMetrics.height());
        //return qApp->style()->sizeFromContents(QStyle::CT_ComboBox,
        //                                       &option, size);
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case Zipcode: return item.zipcode;
            case PostOffice: return item.postOffice;
            case County: return item.county;
            case State: return item.state;
            default: Q_ASSERT(false);
        }
    }
    return QVariant();

}

/*!
 * \brief TableModel::headerData
 * 返回由section所指的行(当orientation为Qt::Vetical时)或列(当orientation为Qt::Horizontal时)
 * 所在的角色role对应的QVariant值
 * \param section
 * \param orientation
 * \param role
 * \return
 */
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case Zipcode: return tr("Zipcode");
            case PostOffice: return tr("Post Office");
            case County: return tr("County");
            case State: return tr("State");
            default: Q_ASSERT(false);
        }
    }
    return section + 1;
}
/*!
 * \brief TableModel::rowCount
 *
 * 返回以给定的index parent为父项的那些项的行数
 * \param parent
 * \return
 */
int TableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : zipcodes.count();
}

/*!
 * \brief TableModel::columnCount
 *
 * 返回指定的index parent为父项的那些项的列数(通常对于整个模型来说是常量)
 * 表格和树
 * \param parent
 * \return
 */
int TableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : MaxColumns;
}


/*!
 * \brief TableModel::setData
 * 设置指定项(索引为index)的指定角色(role)对应的值value
 * 如果正确则返回true 并触发 dataChange信号
 * \param index
 * \param value
 * \param role
 * \return
 */
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole ||
        index.row() < 0 || index.row() >= zipcodes.count() ||
        index.column() < 0 || index.column() >= MaxColumns)
        return false;
    ZipcodeItem &item = zipcodes[index.row()];
    switch (index.column()) {
        case Zipcode: {
            bool ok;
            int zipcode = value.toInt(&ok);
            if (!ok || zipcode < MinZipcode || zipcode > MaxZipcode)
                return false;
            item.zipcode = zipcode;
            break;
        }
        case PostOffice: item.postOffice = value.toString(); break;
        case County: item.county = value.toString(); break;
        case State: item.state = value.toString(); break;
        default: Q_ASSERT(false);
    }
    emit dataChanged(index, index);
    return true;
}

/*!
 * \brief TableModel::insertRows
 * 在指定项(索引为parent)的子项中，在索引为row的行之前插入count行;重新实现时
 * 必须调用beginInsertRows()和endInserRows()
 * \param row
 * \param count
 * \param parent
 * \return
 */
bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row+count-1);
    for (int i = 0; i < count; ++i)
        zipcodes.insert(row, ZipcodeItem());
    endInsertRows();
    return true;
}
/*!
 * \brief TableModel::removeRows
 * 在指定项(索引为parent)的子项中，在索引为row的行开始删除count行;重新实现时
 * 必须调用beginRemoveRows()和endRemoveRows()
 * \param row
 * \param count
 * \param parent
 * \return
 */
bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i)
        zipcodes.removeAt(row);
    endRemoveRows();
    return true;
}

/*!
 * \brief TableModel::setHeaderData
 * 设置由section所指向的行(当orientation为Qt::Vetical时)或列(当orientation为Qt::Horizontal时)
 * 所在的角色role对应的QVariant值 如果设置成功则返回true 并调用 headerDataChanged()信号
 * \param section
 * \param orientation
 * \param value
 * \param role
 * \return
 */
bool TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    return false;
}

void TableModel::load(const QString &filename)
{
    if (!filename.isEmpty())
        m_filename = filename;
    if (m_filename.isEmpty())
        qDebug()<< "m_filename isempty";
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly))
        qDebug()<< "open false";

    QDataStream in(&file);
    qint32 magicNumber;
    in >> magicNumber;
    if (magicNumber != MagicNumber) {
        qDebug()<< "magicNumber error";
    }
    qint16 formatVersionNumber;
    in >> formatVersionNumber;
    if (formatVersionNumber > FormatNumber) {
        qDebug()<< "formatVersionNumber error";
    }
    in.setVersion(QDataStream::Qt_5_3);

    beginResetModel();
    zipcodes.clear();

    ZipcodeItem item;
    while (!in.atEnd()) {
        in >> item;
        zipcodes << item;
    }

    qSort(zipcodes);
    endResetModel();
}

void TableModel::save(const QString &filename)
{
    if (!filename.isEmpty())
        m_filename = filename;
    if (m_filename.isEmpty())
        qDebug()<< "m_filename isempty";
    QFile file(m_filename);
    if (!file.open(QIODevice::WriteOnly))
        qDebug()<< "open false";

    QDataStream out(&file);
    out << MagicNumber << FormatNumber;
    out.setVersion(QDataStream::Qt_4_5);
    QListIterator<ZipcodeItem> i(zipcodes);
    while (i.hasNext())
        out << i.next();
}
