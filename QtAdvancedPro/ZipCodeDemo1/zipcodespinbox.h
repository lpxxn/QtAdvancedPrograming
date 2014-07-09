#ifndef ZIPCODESPINBOX_H
#define ZIPCODESPINBOX_H

#include <QSpinBox>
#include <QWidget>
#include "global.h"
class ZipcodeSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit ZipcodeSpinBox(QWidget *parent = 0);

signals:

public slots:
protected:
    QString textFromValue(int value) const
        { return QString("%1").arg(value, 5, 10, QChar('0')); }

};

#endif // ZIPCODESPINBOX_H
