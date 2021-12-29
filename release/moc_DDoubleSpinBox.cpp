/****************************************************************************
** Meta object code from reading C++ file 'DDoubleSpinBox.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../DDoubleSpinBox.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DDoubleSpinBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DDoubleSpinBox_t {
    const uint offsetsAndSize[20];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DDoubleSpinBox_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DDoubleSpinBox_t qt_meta_stringdata_DDoubleSpinBox = {
    {
QT_MOC_LITERAL(0, 14), // "DDoubleSpinBox"
QT_MOC_LITERAL(15, 16), // "leftValueChanged"
QT_MOC_LITERAL(32, 0), // ""
QT_MOC_LITERAL(33, 17), // "rightValueChanged"
QT_MOC_LITERAL(51, 12), // "valueChanged"
QT_MOC_LITERAL(64, 12), // "extractValue"
QT_MOC_LITERAL(77, 13), // "extractValue2"
QT_MOC_LITERAL(91, 11), // "catchOverUp"
QT_MOC_LITERAL(103, 13), // "catchOverDown"
QT_MOC_LITERAL(117, 11) // "zeroSection"

    },
    "DDoubleSpinBox\0leftValueChanged\0\0"
    "rightValueChanged\0valueChanged\0"
    "extractValue\0extractValue2\0catchOverUp\0"
    "catchOverDown\0zeroSection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DDoubleSpinBox[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    1 /* Public */,
       3,    1,   65,    2, 0x06,    3 /* Public */,
       4,    1,   68,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   71,    2, 0x08,    7 /* Private */,
       6,    1,   74,    2, 0x08,    9 /* Private */,
       7,    0,   77,    2, 0x08,   11 /* Private */,
       8,    0,   78,    2, 0x08,   12 /* Private */,
       9,    0,   79,    2, 0x08,   13 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DDoubleSpinBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DDoubleSpinBox *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->leftValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->rightValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->extractValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->extractValue2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->catchOverUp(); break;
        case 6: _t->catchOverDown(); break;
        case 7: _t->zeroSection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DDoubleSpinBox::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DDoubleSpinBox::leftValueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DDoubleSpinBox::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DDoubleSpinBox::rightValueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DDoubleSpinBox::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DDoubleSpinBox::valueChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject DDoubleSpinBox::staticMetaObject = { {
    QMetaObject::SuperData::link<DWidget::staticMetaObject>(),
    qt_meta_stringdata_DDoubleSpinBox.offsetsAndSize,
    qt_meta_data_DDoubleSpinBox,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DDoubleSpinBox_t
, QtPrivate::TypeAndForceComplete<DDoubleSpinBox, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *DDoubleSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DDoubleSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DDoubleSpinBox.stringdata0))
        return static_cast<void*>(this);
    return DWidget::qt_metacast(_clname);
}

int DDoubleSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void DDoubleSpinBox::leftValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DDoubleSpinBox::rightValueChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DDoubleSpinBox::valueChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
