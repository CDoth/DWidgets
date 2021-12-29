/****************************************************************************
** Meta object code from reading C++ file 'DPlot.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../DPlot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DPlot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DPlot_t {
    const uint offsetsAndSize[6];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DPlot_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DPlot_t qt_meta_stringdata_DPlot = {
    {
QT_MOC_LITERAL(0, 5), // "DPlot"
QT_MOC_LITERAL(6, 15), // "slot_updateAxes"
QT_MOC_LITERAL(22, 0) // ""

    },
    "DPlot\0slot_updateAxes\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DPlot[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DPlot *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slot_updateAxes(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject DPlot::staticMetaObject = { {
    QMetaObject::SuperData::link<DWidget::staticMetaObject>(),
    qt_meta_stringdata_DPlot.offsetsAndSize,
    qt_meta_data_DPlot,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DPlot_t
, QtPrivate::TypeAndForceComplete<DPlot, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *DPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DPlot.stringdata0))
        return static_cast<void*>(this);
    return DWidget::qt_metacast(_clname);
}

int DPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_DPlotSettings_t {
    const uint offsetsAndSize[8];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DPlotSettings_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DPlotSettings_t qt_meta_stringdata_DPlotSettings = {
    {
QT_MOC_LITERAL(0, 13), // "DPlotSettings"
QT_MOC_LITERAL(14, 13), // "slot_addPoint"
QT_MOC_LITERAL(28, 0), // ""
QT_MOC_LITERAL(29, 17) // "slot_addLivePoint"

    },
    "DPlotSettings\0slot_addPoint\0\0"
    "slot_addLivePoint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DPlotSettings[] = {

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
       1,    1,   26,    2, 0x08,    1 /* Private */,
       3,    1,   29,    2, 0x08,    3 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void DPlotSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DPlotSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slot_addPoint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slot_addLivePoint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject DPlotSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<DWidget::staticMetaObject>(),
    qt_meta_stringdata_DPlotSettings.offsetsAndSize,
    qt_meta_data_DPlotSettings,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DPlotSettings_t
, QtPrivate::TypeAndForceComplete<DPlotSettings, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>


>,
    nullptr
} };


const QMetaObject *DPlotSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DPlotSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DPlotSettings.stringdata0))
        return static_cast<void*>(this);
    return DWidget::qt_metacast(_clname);
}

int DPlotSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
