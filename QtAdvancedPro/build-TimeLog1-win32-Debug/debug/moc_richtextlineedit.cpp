/****************************************************************************
** Meta object code from reading C++ file 'richtextlineedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TimeLog1/richtextlineedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'richtextlineedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RichTextLineEdit_t {
    QByteArrayData data[11];
    char stringdata[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RichTextLineEdit_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RichTextLineEdit_t qt_meta_stringdata_RichTextLineEdit = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 13),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 12),
QT_MOC_LITERAL(4, 45, 10),
QT_MOC_LITERAL(5, 56, 26),
QT_MOC_LITERAL(6, 83, 3),
QT_MOC_LITERAL(7, 87, 15),
QT_MOC_LITERAL(8, 103, 10),
QT_MOC_LITERAL(9, 114, 8),
QT_MOC_LITERAL(10, 123, 6)
    },
    "RichTextLineEdit\0returnPressed\0\0"
    "toggleItalic\0toggleBold\0"
    "customContextMenuRequested\0pos\0"
    "applyTextEffect\0applyColor\0QAction*\0"
    "action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RichTextLineEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    1,   47,    2, 0x08 /* Private */,
       7,    0,   50,    2, 0x08 /* Private */,
       8,    1,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void RichTextLineEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RichTextLineEdit *_t = static_cast<RichTextLineEdit *>(_o);
        switch (_id) {
        case 0: _t->returnPressed(); break;
        case 1: _t->toggleItalic(); break;
        case 2: _t->toggleBold(); break;
        case 3: _t->customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->applyTextEffect(); break;
        case 5: _t->applyColor((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RichTextLineEdit::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RichTextLineEdit::returnPressed)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject RichTextLineEdit::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_RichTextLineEdit.data,
      qt_meta_data_RichTextLineEdit,  qt_static_metacall, 0, 0}
};


const QMetaObject *RichTextLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RichTextLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RichTextLineEdit.stringdata))
        return static_cast<void*>(const_cast< RichTextLineEdit*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int RichTextLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void RichTextLineEdit::returnPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
