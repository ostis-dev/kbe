/****************************************************************************
** Meta object code from reading C++ file 'scgundoviewmodel.h'
**
** Created: Thu 19. Dec 10:55:35 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/scgundoviewmodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scgundoviewmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgUndoViewModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x0a,
      46,   17,   17,   17, 0x08,
      65,   61,   17,   17, 0x08,
      96,   90,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SCgUndoViewModel[] = {
    "SCgUndoViewModel\0\0stack\0setStack(QUndoStack*)\0"
    "stackChanged()\0obj\0stackDestroyed(QObject*)\0"
    "index\0setStackCurrentIndex(QModelIndex)\0"
};

void SCgUndoViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCgUndoViewModel *_t = static_cast<SCgUndoViewModel *>(_o);
        switch (_id) {
        case 0: _t->setStack((*reinterpret_cast< QUndoStack*(*)>(_a[1]))); break;
        case 1: _t->stackChanged(); break;
        case 2: _t->stackDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 3: _t->setStackCurrentIndex((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SCgUndoViewModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgUndoViewModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_SCgUndoViewModel,
      qt_meta_data_SCgUndoViewModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgUndoViewModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgUndoViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgUndoViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgUndoViewModel))
        return static_cast<void*>(const_cast< SCgUndoViewModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int SCgUndoViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
