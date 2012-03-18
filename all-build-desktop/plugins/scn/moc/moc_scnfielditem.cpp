/****************************************************************************
** Meta object code from reading C++ file 'scnfielditem.h'
**
** Created: Sun Mar 18 14:49:58 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scn/scnfielditem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scnfielditem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCnFieldItem[] = {

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
      14,   13,   13,   13, 0x0a,
      26,   13,   13,   13, 0x0a,
      38,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SCnFieldItem[] = {
    "SCnFieldItem\0\0startEdit()\0applyEdit()\0"
    "cancelEdit()\0"
};

void SCnFieldItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCnFieldItem *_t = static_cast<SCnFieldItem *>(_o);
        switch (_id) {
        case 0: _t->startEdit(); break;
        case 1: _t->applyEdit(); break;
        case 2: _t->cancelEdit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCnFieldItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCnFieldItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SCnFieldItem,
      qt_meta_data_SCnFieldItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCnFieldItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCnFieldItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCnFieldItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCnFieldItem))
        return static_cast<void*>(const_cast< SCnFieldItem*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< SCnFieldItem*>(this));
    if (!strcmp(_clname, "com.trolltech.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< SCnFieldItem*>(this));
    return QObject::qt_metacast(_clname);
}

int SCnFieldItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
