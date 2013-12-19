/****************************************************************************
** Meta object code from reading C++ file 'scgcontentimage.h'
**
** Created: Thu 19. Dec 10:55:28 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/scgcontentimage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scgcontentimage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgContentImageViewer[] = {

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

static const char qt_meta_stringdata_SCgContentImageViewer[] = {
    "SCgContentImageViewer\0"
};

void SCgContentImageViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCgContentImageViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgContentImageViewer::staticMetaObject = {
    { &SCgContentViewer::staticMetaObject, qt_meta_stringdata_SCgContentImageViewer,
      qt_meta_data_SCgContentImageViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgContentImageViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgContentImageViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgContentImageViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgContentImageViewer))
        return static_cast<void*>(const_cast< SCgContentImageViewer*>(this));
    return SCgContentViewer::qt_metacast(_clname);
}

int SCgContentImageViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SCgContentViewer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_SCgContentImageDialog[] = {

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
      23,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SCgContentImageDialog[] = {
    "SCgContentImageDialog\0\0chooseSource()\0"
};

void SCgContentImageDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCgContentImageDialog *_t = static_cast<SCgContentImageDialog *>(_o);
        switch (_id) {
        case 0: _t->chooseSource(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCgContentImageDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgContentImageDialog::staticMetaObject = {
    { &SCgContentDialog::staticMetaObject, qt_meta_stringdata_SCgContentImageDialog,
      qt_meta_data_SCgContentImageDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgContentImageDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgContentImageDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgContentImageDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgContentImageDialog))
        return static_cast<void*>(const_cast< SCgContentImageDialog*>(this));
    return SCgContentDialog::qt_metacast(_clname);
}

int SCgContentImageDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SCgContentDialog::qt_metacall(_c, _id, _a);
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
