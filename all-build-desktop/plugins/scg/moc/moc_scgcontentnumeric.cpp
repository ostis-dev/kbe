/****************************************************************************
** Meta object code from reading C++ file 'scgcontentnumeric.h'
**
** Created: Sun Mar 18 14:49:25 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/scgcontentnumeric.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scgcontentnumeric.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgContentNumericDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SCgContentNumericDialog[] = {
    "SCgContentNumericDialog\0\0"
    "enableApplyButton(QValidator::State)\0"
    "slotEnableApplyButton(QString)\0"
};

void SCgContentNumericDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCgContentNumericDialog *_t = static_cast<SCgContentNumericDialog *>(_o);
        switch (_id) {
        case 0: _t->enableApplyButton((*reinterpret_cast< QValidator::State(*)>(_a[1]))); break;
        case 1: _t->slotEnableApplyButton((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SCgContentNumericDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgContentNumericDialog::staticMetaObject = {
    { &SCgContentDialog::staticMetaObject, qt_meta_stringdata_SCgContentNumericDialog,
      qt_meta_data_SCgContentNumericDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgContentNumericDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgContentNumericDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgContentNumericDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgContentNumericDialog))
        return static_cast<void*>(const_cast< SCgContentNumericDialog*>(this));
    return SCgContentDialog::qt_metacast(_clname);
}

int SCgContentNumericDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SCgContentDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SCgContentNumericDialog::enableApplyButton(QValidator::State _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
