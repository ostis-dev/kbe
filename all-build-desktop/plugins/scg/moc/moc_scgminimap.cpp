/****************************************************************************
** Meta object code from reading C++ file 'scgminimap.h'
**
** Created: Sun Mar 18 14:49:21 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/scgminimap.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scgminimap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgMinimap[] = {

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
      17,   12,   11,   11, 0x09,
      46,   42,   11,   11, 0x09,
      68,   11,   11,   11, 0x29,

       0        // eod
};

static const char qt_meta_stringdata_SCgMinimap[] = {
    "SCgMinimap\0\0rect\0sceneRectChanged(QRectF)\0"
    "val\0updateViewedArea(int)\0updateViewedArea()\0"
};

void SCgMinimap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCgMinimap *_t = static_cast<SCgMinimap *>(_o);
        switch (_id) {
        case 0: _t->sceneRectChanged((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 1: _t->updateViewedArea((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateViewedArea(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SCgMinimap::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgMinimap::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_SCgMinimap,
      qt_meta_data_SCgMinimap, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgMinimap::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgMinimap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgMinimap::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgMinimap))
        return static_cast<void*>(const_cast< SCgMinimap*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int SCgMinimap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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
