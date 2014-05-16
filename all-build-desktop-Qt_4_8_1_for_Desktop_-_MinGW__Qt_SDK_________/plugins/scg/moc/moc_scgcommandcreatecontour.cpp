/****************************************************************************
** Meta object code from reading C++ file 'scgcommandcreatecontour.h'
**
** Created: Thu 19. Dec 10:55:39 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/commands/scgcommandcreatecontour.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scgcommandcreatecontour.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgCommandCreateContour[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SCgCommandCreateContour[] = {
    "SCgCommandCreateContour\0\0contourDestroyed()\0"
};

void SCgCommandCreateContour::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCgCommandCreateContour *_t = static_cast<SCgCommandCreateContour *>(_o);
        switch (_id) {
        case 0: _t->contourDestroyed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCgCommandCreateContour::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgCommandCreateContour::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SCgCommandCreateContour,
      qt_meta_data_SCgCommandCreateContour, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgCommandCreateContour::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgCommandCreateContour::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgCommandCreateContour::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgCommandCreateContour))
        return static_cast<void*>(const_cast< SCgCommandCreateContour*>(this));
    if (!strcmp(_clname, "SCgBaseCommand"))
        return static_cast< SCgBaseCommand*>(const_cast< SCgCommandCreateContour*>(this));
    return QObject::qt_metacast(_clname);
}

int SCgCommandCreateContour::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
