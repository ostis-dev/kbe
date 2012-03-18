/****************************************************************************
** Meta object code from reading C++ file 'SCgPairModeEventHandler.h'
**
** Created: Sun Mar 18 14:49:40 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/event_handling/SCgPairModeEventHandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SCgPairModeEventHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgPairModeEventHandler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_SCgPairModeEventHandler[] = {
    "SCgPairModeEventHandler\0"
};

void SCgPairModeEventHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCgPairModeEventHandler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgPairModeEventHandler::staticMetaObject = {
    { &SCgEventHandler::staticMetaObject, qt_meta_stringdata_SCgPairModeEventHandler,
      qt_meta_data_SCgPairModeEventHandler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgPairModeEventHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgPairModeEventHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgPairModeEventHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgPairModeEventHandler))
        return static_cast<void*>(const_cast< SCgPairModeEventHandler*>(this));
    return SCgEventHandler::qt_metacast(_clname);
}

int SCgPairModeEventHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SCgEventHandler::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
