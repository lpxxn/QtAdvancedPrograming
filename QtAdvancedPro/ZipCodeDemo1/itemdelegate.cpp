#include "itemdelegate.h"
#include "global.h"
#include <QPainter>
#include <QComboBox>
#include "zipcodespinbox.h"
#include <QDebug>
ItemDelegate::ItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}


void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == Zipcode) {
        QStyleOptionViewItemV4 opt(option);
        initStyleOption(&opt, index);
        QString text = QString("%1").arg(opt.text.toInt(),
                                         5, 10, QChar('0'));
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing|
                                QPainter::TextAntialiasing);

        if (opt.state & QStyle::State_Selected) {
            qDebug()<<"state  ..:"<<opt.state;
            painter->fillRect(opt.rect, opt.palette.highlight());
            painter->setPen(opt.palette.highlightedText().color());
        }
        else {
            //painter->setPen(opt.palette.windowText().color());
            painter->setPen(Qt::red);
        }
        //adjuested 是在原来的 Rect 坐标之上加上新给的数据 如原来是0,0,10,10 新给的是0,0,-5,0 得到的是0,0,5,10
        painter->drawText(opt.rect.adjusted(0, 0, -10, 0), text,
                QTextOption(Qt::AlignVCenter|Qt::AlignRight));
        painter->restore();
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}

QWidget *ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    static QStringList usStates;
    if (usStates.isEmpty())
        usStates << "(Unknown)" << "Alabama" << "Alaska"
            << "Arizona" << "Arkansas" << "California"
            << "Colorado" << "Connecticut" << "Delaware"
            << "District Of Columbia" << "Florida" << "Georgia"
            << "Hawaii" << "Idaho" << "Illinois" << "Indiana"
            << "Iowa" << "Kansas" << "Kentucky" << "Louisiana"
            << "Maine" << "Maryland" << "Massachusetts"
            << "Michigan" << "Minnesota" << "Mississippi"
            << "Missouri" << "Montana" << "Nebraska" << "Nevada"
            << "New Hampshire" << "New Jersey" << "New Mexico"
            << "New York" << "North Carolina" << "North Dakota"
            << "Ohio" << "Oklahoma" << "Oregon" << "Pennsylvania"
            << "Rhode Island" << "South Carolina"
            << "South Dakota" << "State" << "Tennessee" << "Texas"
            << "Utah" << "Vermont" << "Virginia" << "Washington"
            << "West Virginia" << "Wisconsin" << "Wyoming";

    if (index.column() == Zipcode)
        return new ZipcodeSpinBox(parent);
    if (index.column() == State) {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(usStates);
        return editor;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == Zipcode) {
        int value = index.model()->data(index).toInt();
        ZipcodeSpinBox *spinBox =
                qobject_cast<ZipcodeSpinBox*>(editor);
        Q_ASSERT(spinBox);
        spinBox->setValue(value);
    }
    else if (index.column() == State) {
        QString state = index.model()->data(index).toString();
        QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(comboBox);
        comboBox->setCurrentIndex(comboBox->findText(state));
    }
    else
        QStyledItemDelegate::setEditorData(editor, index);
}

void ItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == Zipcode) {
        ZipcodeSpinBox *spinBox =
                qobject_cast<ZipcodeSpinBox*>(editor);
        Q_ASSERT(spinBox);
        spinBox->interpretText();
        model->setData(index, spinBox->value());
    }
    else if (index.column() == State) {
        QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(comboBox);
        model->setData(index, comboBox->currentText());
    }
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}
