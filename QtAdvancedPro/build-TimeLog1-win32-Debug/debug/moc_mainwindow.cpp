/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TimeLog1/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 10),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 7),
QT_MOC_LITERAL(4, 31, 8),
QT_MOC_LITERAL(5, 40, 8),
QT_MOC_LITERAL(6, 49, 10),
QT_MOC_LITERAL(7, 60, 7),
QT_MOC_LITERAL(8, 68, 10),
QT_MOC_LITERAL(9, 79, 15),
QT_MOC_LITERAL(10, 95, 5),
QT_MOC_LITERAL(11, 101, 23),
QT_MOC_LITERAL(12, 125, 4),
QT_MOC_LITERAL(13, 130, 8),
QT_MOC_LITERAL(14, 139, 5),
QT_MOC_LITERAL(15, 145, 4),
QT_MOC_LITERAL(16, 150, 8),
QT_MOC_LITERAL(17, 159, 8),
QT_MOC_LITERAL(18, 168, 7),
QT_MOC_LITERAL(19, 176, 10),
QT_MOC_LITERAL(20, 187, 5),
QT_MOC_LITERAL(21, 193, 8)
    },
    "MainWindow\0stopTiming\0\0fileNew\0fileOpen\0"
    "fileSave\0fileSaveAs\0editAdd\0editDelete\0"
    "editStartOrStop\0start\0editHideOrShowDoneTasks\0"
    "hide\0setDirty\0dirty\0load\0filename\0"
    "taskPath\0timeout\0updateIcon\0frame\0"
    "updateUi"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    1,  101,    2, 0x08 /* Private */,
      11,    1,  104,    2, 0x08 /* Private */,
      13,    1,  107,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x28 /* Private | MethodCloned */,
      15,    2,  111,    2, 0x08 /* Private */,
      15,    1,  116,    2, 0x28 /* Private | MethodCloned */,
      18,    0,  119,    2, 0x08 /* Private */,
      19,    1,  120,    2, 0x08 /* Private */,
      21,    0,  123,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,   16,   17,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->stopTiming(); break;
        case 1: _t->fileNew(); break;
        case 2: _t->fileOpen(); break;
        case 3: { bool _r = _t->fileSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->fileSaveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: _t->editAdd(); break;
        case 6: _t->editDelete(); break;
        case 7: _t->editStartOrStop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->editHideOrShowDoneTasks((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->setDirty((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setDirty(); break;
        case 11: _t->load((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 12: _t->load((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->timeout(); break;
        case 14: _t->updateIcon((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->updateUi(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
