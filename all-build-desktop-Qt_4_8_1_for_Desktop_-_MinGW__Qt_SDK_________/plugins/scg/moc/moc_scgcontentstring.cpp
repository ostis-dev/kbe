/****************************************************************************
** Meta object code from reading C++ file 'scgcontentstring.h'
**
** Created: Thu 19. Dec 10:55:26 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/scgcontentstring.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scgcontentstring.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgContentStringViewer[] = {

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

static const char qt_meta_stringdata_SCgContentStringViewer[] = {
    "SCgContentStringViewer\0"
};

void SCgContentStringViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCgContentStringViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgContentStringViewer::staticMetaObject = {
    { &SCgContentViewer::staticMetaObject, qt_meta_stringdata_SCgContentStringViewer,
      qt_meta_data_SCgContentStringViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgContentStringViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgContentStringViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgContentStringViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgContentStringViewer))
        return static_cast<void*>(const_cast< SCgContentStringViewer*>(this));
    return SCgContentViewer::qt_metacast(_clname);
}

int SCgContentStringViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SCgContentViewer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_SCgContentStringDialog[] = {

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
      35,   24,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SCgContentStringDialog[] = {
    "SCgContentStringDialog\0\0isWordWrap\0"
    "setWordWrap(bool)\0"
};

void SCgContentStringDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCgContentStringDialog *_t = static_cast<SCgContentStringDialog *>(_o);
        switch (_id) {
        case 0: _t->setWordWrap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SCgContentStringDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgContentStringDialog::staticMetaObject = {
    { &SCgContentDialog::staticMetaObject, qt_meta_stringdata_SCgContentStringDialog,
      qt_meta_data_SCgContentStringDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgContentStringDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgContentStringDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgContentStringDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgContentStringDialog))
        return static_cast<void*>(const_cast< SCgContentStringDialog*>(this));
    return SCgContentDialog::qt_metacast(_clname);
}

int SCgContentStringDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
