/****************************************************************************
** Meta object code from reading C++ file 'extendedtabwidget.h'
**
** Created: Sun Mar 18 14:58:06 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../sources/kbe/extendedtabwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'extendedtabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExtendedTabWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   19,   18,   18, 0x05,
      46,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      59,   18,   18,   18, 0x0a,
      81,   18,   18,   18, 0x0a,
     107,  101,   18,   18, 0x0a,
     118,   18,   18,   18, 0x2a,
     137,  130,  126,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ExtendedTabWidget[] = {
    "ExtendedTabWidget\0\0w\0tabBeforeClose(QWidget*)\0"
    "tabsUpdate()\0closeOtherDocuments()\0"
    "closeAllDocuments()\0index\0close(int)\0"
    "close()\0int\0window\0addSubWindow(EditorInterface*)\0"
};

void ExtendedTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ExtendedTabWidget *_t = static_cast<ExtendedTabWidget *>(_o);
        switch (_id) {
        case 0: _t->tabBeforeClose((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->tabsUpdate(); break;
        case 2: _t->closeOtherDocuments(); break;
        case 3: _t->closeAllDocuments(); break;
        case 4: _t->close((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->close(); break;
        case 6: { int _r = _t->addSubWindow((*reinterpret_cast< EditorInterface*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ExtendedTabWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ExtendedTabWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_ExtendedTabWidget,
      qt_meta_data_ExtendedTabWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ExtendedTabWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ExtendedTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ExtendedTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExtendedTabWidget))
        return static_cast<void*>(const_cast< ExtendedTabWidget*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int ExtendedTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ExtendedTabWidget::tabBeforeClose(QWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExtendedTabWidget::tabsUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
