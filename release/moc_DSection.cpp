/****************************************************************************
** Meta object code from reading C++ file 'DSection.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../DSection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DSection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DAbstractSection_t {
    const uint offsetsAndSize[10];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DAbstractSection_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DAbstractSection_t qt_meta_stringdata_DAbstractSection = {
    {
QT_MOC_LITERAL(0, 16), // "DAbstractSection"
QT_MOC_LITERAL(17, 10), // "dblClicked"
QT_MOC_LITERAL(28, 0), // ""
QT_MOC_LITERAL(29, 7), // "clicked"
QT_MOC_LITERAL(37, 12) // "valueChanged"

    },
    "DAbstractSection\0dblClicked\0\0clicked\0"
    "valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DAbstractSection[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x06,    1 /* Public */,
       3,    0,   33,    2, 0x06,    2 /* Public */,
       4,    1,   34,    2, 0x06,    3 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void DAbstractSection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DAbstractSection *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dblClicked(); break;
        case 1: _t->clicked(); break;
        case 2: _t->valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DAbstractSection::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DAbstractSection::dblClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DAbstractSection::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DAbstractSection::clicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DAbstractSection::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DAbstractSection::valueChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject DAbstractSection::staticMetaObject = { {
    QMetaObject::SuperData::link<DWidget::staticMetaObject>(),
    qt_meta_stringdata_DAbstractSection.offsetsAndSize,
    qt_meta_data_DAbstractSection,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DAbstractSection_t
, QtPrivate::TypeAndForceComplete<DAbstractSection, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>



>,
    nullptr
} };


const QMetaObject *DAbstractSection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DAbstractSection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DAbstractSection.stringdata0))
        return static_cast<void*>(this);
    return DWidget::qt_metacast(_clname);
}

int DAbstractSection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void DAbstractSection::dblClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DAbstractSection::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DAbstractSection::valueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_DNumberSection_t {
    const uint offsetsAndSize[8];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DNumberSection_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DNumberSection_t qt_meta_stringdata_DNumberSection = {
    {
QT_MOC_LITERAL(0, 14), // "DNumberSection"
QT_MOC_LITERAL(15, 9), // "tryOverUp"
QT_MOC_LITERAL(25, 0), // ""
QT_MOC_LITERAL(26, 11) // "tryOverDown"

    },
    "DNumberSection\0tryOverUp\0\0tryOverDown"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DNumberSection[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x06,    1 /* Public */,
       3,    0,   27,    2, 0x06,    2 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DNumberSection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DNumberSection *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->tryOverUp(); break;
        case 1: _t->tryOverDown(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DNumberSection::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DNumberSection::tryOverUp)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DNumberSection::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DNumberSection::tryOverDown)) {
                *result = 1;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject DNumberSection::staticMetaObject = { {
    QMetaObject::SuperData::link<DAbstractSection::staticMetaObject>(),
    qt_meta_stringdata_DNumberSection.offsetsAndSize,
    qt_meta_data_DNumberSection,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DNumberSection_t
, QtPrivate::TypeAndForceComplete<DNumberSection, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *DNumberSection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DNumberSection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DNumberSection.stringdata0))
        return static_cast<void*>(this);
    return DAbstractSection::qt_metacast(_clname);
}

int DNumberSection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DAbstractSection::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void DNumberSection::tryOverUp()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DNumberSection::tryOverDown()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
