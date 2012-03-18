/****************************************************************************
** Meta object code from reading C++ file 'scgarrangertuple.h'
**
** Created: Sun Mar 18 14:49:33 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/scgarrangertuple.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scgarrangertuple.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgTupleArranger[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   18,   17,   17, 0x09,
      48,   18,   17,   17, 0x09,
      67,   18,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_SCgTupleArranger[] = {
    "SCgTupleArranger\0\0newSpacing\0"
    "xValueChanged(int)\0yValueChanged(int)\0"
    "dValueChanged(int)\0"
};

void SCgTupleArranger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCgTupleArranger *_t = static_cast<SCgTupleArranger *>(_o);
        switch (_id) {
        case 0: _t->xValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->yValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->dValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SCgTupleArranger::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgTupleArranger::staticMetaObject = {
    { &SCgArranger::staticMetaObject, qt_meta_stringdata_SCgTupleArranger,
      qt_meta_data_SCgTupleArranger, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgTupleArranger::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgTupleArranger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgTupleArranger::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgTupleArranger))
        return static_cast<void*>(const_cast< SCgTupleArranger*>(this));
    return SCgArranger::qt_metacast(_clname);
}

int SCgTupleArranger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SCgArranger::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
