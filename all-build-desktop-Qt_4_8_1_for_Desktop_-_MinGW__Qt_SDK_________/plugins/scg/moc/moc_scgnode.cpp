/****************************************************************************
** Meta object code from reading C++ file 'scgnode.h'
**
** Created: Thu 19. Dec 10:55:23 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/scgnode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scgnode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgNode[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SCgNode[] = {
    "SCgNode\0\0contentChanged()\0"
};

void SCgNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCgNode *_t = static_cast<SCgNode *>(_o);
        switch (_id) {
        case 0: _t->contentChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCgNode::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgNode::staticMetaObject = {
    { &SCgObject::staticMetaObject, qt_meta_stringdata_SCgNode,
      qt_meta_data_SCgNode, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgNode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgNode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgNode))
        return static_cast<void*>(const_cast< SCgNode*>(this));
    if (!strcmp(_clname, "SCgContent"))
        return static_cast< SCgContent*>(const_cast< SCgNode*>(this));
    return SCgObject::qt_metacast(_clname);
}

int SCgNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SCgObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void SCgNode::contentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
