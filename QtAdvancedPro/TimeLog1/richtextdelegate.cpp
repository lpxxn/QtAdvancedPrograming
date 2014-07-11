#include "richtextlineedit.h"
#include "richtextdelegate.h"
#include <QModelIndex>
#include <QPainter>
#include <QPixmapCache>
#include <QDebug>

RichTextDelegate::RichTextDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    checkbox = new QCheckBox;
    checkbox->setFixedSize(
                qRound(1.3 * checkbox->sizeHint().height())+3,
                checkbox->sizeHint().height()+4);
    label = new QLabel;
    label->setTextFormat(Qt::RichText);
    label->setWordWrap(false);
}


void RichTextDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{


    bool selected = option.state & QStyle::State_Selected;
    QPalette palette(option.palette);
    palette.setColor(QPalette::Active, QPalette::Window,
                     selected ? option.palette.highlight().color()
                              : option.palette.base().color());
    palette.setColor(QPalette::Active, QPalette::WindowText,
                     selected
                     ? option.palette.highlightedText().color()
                     : option.palette.text().color());

    bool mouseOver = option.state & QStyle::State_MouseOver;
    if(mouseOver) {
        palette.setColor(QPalette::Active, QPalette::Window,
                         Qt::blue);
        //        palette.setColor(QPalette::Active, QPalette::WindowText,
        //                         Qt::red);
    }

    int yOffset = checkbox->height() < option.rect.height()
            ? (option.rect.height() - checkbox->height()) / 2 : 0;
    QRect checkboxRect(option.rect.x(), option.rect.y() ,
                       checkbox->width(), checkbox->height()+2);
    checkbox->setPalette(palette);
    bool checked = index.model()->data(index, Qt::CheckStateRole)
            .toInt() == Qt::Checked;
    checkbox->setChecked(checked);

    QRect labelRect(option.rect.x() + checkbox->width(),
                    option.rect.y(), option.rect.width() - checkbox->width(),
                    option.rect.height());

    if(mouseOver) {
        //palette.setColor(QPalette::background(),Qt::red);
        //qDebug()<<"mouseover set background";
        //label->setStyleSheet("QLabel { background-color:red; }");
    }
    label->setPalette(palette);




    label->setFixedSize(qMax(0, labelRect.width()),
                        labelRect.height());
    QString html = index.model()->data(index, Qt::DisplayRole)
            .toString();
    label->setText(html);

    QString checkboxKey = QString("CHECKBOX:%1.%2").arg(selected)
            .arg(checked);
    paintWidget(painter, checkboxRect, checkboxKey, checkbox);
    QString labelKey = QString("LABEL:%1.%2.%3x%4").arg(selected)
            .arg(html).arg(labelRect.width()).arg(labelRect.height());
    qDebug()<<labelKey;
    paintWidget(painter, labelRect, labelKey, label);
    if(mouseOver)
    {
        QLinearGradient linearGrad(option.rect.x(),option.rect.y(),option.rect.bottomLeft().x(),option.rect.bottomLeft().y());
        //251,253,255   249,252,255   242,248,255  242,245,255
        linearGrad.setColorAt(0, QColor(251,253,255));
        linearGrad.setColorAt(0.3, QColor(249,252,255));
        linearGrad.setColorAt(0.7, QColor(242,248,255));
        linearGrad.setColorAt(1, QColor(242,245,255));
        //QBrush background = linearGrad;//
        QBrush background =option.palette.highlight();
        //QColor backColor = option.palette.highlight().color();
        QColor backColor = QColor(242,245,255);
        backColor.setAlpha(90);
        background.setColor(backColor);
        qDebug()<<option.rect;
        painter->fillRect(option.rect, background);
        painter->setPen(option.palette.text().color());
    }
}


void RichTextDelegate::paintWidget(QPainter *painter,
                                   const QRect &rect, const QString &cacheKey,
                                   QWidget *widget) const
{
    QPixmap pixmap(widget->size());
    if (!QPixmapCache::find(cacheKey, &pixmap)) {

        widget->render(&pixmap);
        QPixmapCache::insert(cacheKey, pixmap);
    }
    painter->drawPixmap(rect, pixmap);
    painter->setBackground(QBrush(Qt::red));
}


QSize RichTextDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    QString html = index.model()->data(index, Qt::DisplayRole)
            .toString();
    document.setDefaultFont(option.font);
    document.setHtml(html);
    return QSize(document.idealWidth(), option.fontMetrics.height());
}


QWidget *RichTextDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option, const QModelIndex&) const
{
    RichTextLineEdit *editor = new RichTextLineEdit(parent);
    editor->viewport()->setFixedHeight(option.rect.height());
    connect(editor, SIGNAL(returnPressed()),
            this, SLOT(closeAndCommitEditor()));
    return editor;
}


void RichTextDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
    QString html = index.model()->data(index, Qt::DisplayRole)
            .toString();
    RichTextLineEdit *lineEdit = qobject_cast<RichTextLineEdit*>(
                editor);
    Q_ASSERT(lineEdit);
    lineEdit->setHtml(html);
}


void RichTextDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model, const QModelIndex &index) const
{
    RichTextLineEdit *lineEdit = qobject_cast<RichTextLineEdit*>(
                editor);
    Q_ASSERT(lineEdit);
    model->setData(index, lineEdit->toSimpleHtml());
}


void RichTextDelegate::closeAndCommitEditor()
{
    RichTextLineEdit *lineEdit = qobject_cast<RichTextLineEdit*>(
                sender());
    Q_ASSERT(lineEdit);
    emit commitData(lineEdit);
    emit closeEditor(lineEdit);
}

