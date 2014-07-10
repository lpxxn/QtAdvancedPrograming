/****************************************************************************
** Meta object code from reading C++ file 'proxymodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZipCodeDemo1/proxymodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proxymodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProxyModel_t {
    QByteArrayData data[11];
    char stringdata[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProxyModel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProxyModel_t qt_meta_stringdata_ProxyModel = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 12),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 17),
QT_MOC_LITERAL(4, 43, 14),
QT_MOC_LITERAL(5, 58, 17),
QT_MOC_LITERAL(6, 76, 14),
QT_MOC_LITERAL(7, 91, 9),
QT_MOC_LITERAL(8, 101, 6),
QT_MOC_LITERAL(9, 108, 8),
QT_MOC_LITERAL(10, 117, 5)
    },
    "ProxyModel\0clearFilters\0\0setMinimumZipcode\0"
    "minimumZipcode\0setMaximumZipcode\0"
    "maximumZipcode\0setCounty\0county\0"
    "setState\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProxyModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       5,    1,   43,    2, 0x0a /* Public */,
       7,    1,   46,    2, 0x0a /* Public */,
       9,    1,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void ProxyModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProxyModel *_t = static_cast<ProxyModel *>(_o);
        switch (_id) {
        case 0: _t->clearFilters(); break;
        case 1: _t->setMinimumZipcode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setMaximumZipcode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setCounty((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setState((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ProxyModel::staticMetaObject = {
    { &QSortFilterProxyModel::staticMetaObject, qt_meta_stringdata_ProxyModel.data,
      qt_meta_data_ProxyModel,  qt_static_metacall, 0, 0}
};


const QMetaObject *ProxyModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProxyModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProxyModel.stringdata))
        return static_cast<void*>(const_cast< ProxyModel*>(this));
    return QSortFilterProxyModel::qt_metacast(_clname);
}

int ProxyModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSortFilterProxyModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
