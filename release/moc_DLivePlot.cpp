/****************************************************************************
** Meta object code from reading C++ file 'DLivePlot.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../DLivePlot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DLivePlot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DLivePlot_t {
    const uint offsetsAndSize[12];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DLivePlot_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DLivePlot_t qt_meta_stringdata_DLivePlot = {
    {
QT_MOC_LITERAL(0, 9), // "DLivePlot"
QT_MOC_LITERAL(10, 13), // "slot_addPoint"
QT_MOC_LITERAL(24, 0), // ""
QT_MOC_LITERAL(25, 5), // "group"
QT_MOC_LITERAL(31, 5), // "value"
QT_MOC_LITERAL(37, 15) // "slot_updateAxes"

    },
    "DLivePlot\0slot_addPoint\0\0group\0value\0"
    "slot_updateAxes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DLivePlot[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   26,    2, 0x0a,    1 /* Public */,
       5,    0,   31,    2, 0x08,    4 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Float,    3,    4,
    QMetaType::Void,

       0        // eod
};

void DLivePlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DLivePlot *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slot_addPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->slot_updateAxes(); break;
        default: ;
        }
    }
}

const QMetaObject DLivePlot::staticMetaObject = { {
    QMetaObject::SuperData::link<DWidget::staticMetaObject>(),
    qt_meta_stringdata_DLivePlot.offsetsAndSize,
    qt_meta_data_DLivePlot,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DLivePlot_t
, QtPrivate::TypeAndForceComplete<DLivePlot, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *DLivePlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DLivePlot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DLivePlot.stringdata0))
        return static_cast<void*>(this);
    return DWidget::qt_metacast(_clname);
}

int DLivePlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
