/****************************************************************************
** Meta object code from reading C++ file 'DListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../DListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DListWidget_t {
    const uint offsetsAndSize[12];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DListWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DListWidget_t qt_meta_stringdata_DListWidget = {
    {
QT_MOC_LITERAL(0, 11), // "DListWidget"
QT_MOC_LITERAL(12, 10), // "setListPos"
QT_MOC_LITERAL(23, 0), // ""
QT_MOC_LITERAL(24, 12), // "partOfHeight"
QT_MOC_LITERAL(37, 11), // "mainResized"
QT_MOC_LITERAL(49, 14) // "contentResized"

    },
    "DListWidget\0setListPos\0\0partOfHeight\0"
    "mainResized\0contentResized"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DListWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x08,    1 /* Private */,
       4,    0,   35,    2, 0x08,    3 /* Private */,
       5,    0,   36,    2, 0x08,    4 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DListWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setListPos((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->mainResized(); break;
        case 2: _t->contentResized(); break;
        default: ;
        }
    }
}

const QMetaObject DListWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<DWidget::staticMetaObject>(),
    qt_meta_stringdata_DListWidget.offsetsAndSize,
    qt_meta_data_DListWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DListWidget_t
, QtPrivate::TypeAndForceComplete<DListWidget, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *DListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DListWidget.stringdata0))
        return static_cast<void*>(this);
    return DWidget::qt_metacast(_clname);
}

int DListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
