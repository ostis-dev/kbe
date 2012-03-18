/****************************************************************************
** Meta object code from reading C++ file 'scgwindow.h'
**
** Created: Sun Mar 18 14:49:15 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/scgwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scgwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      26,   10,   10,   10, 0x08,
      39,   10,   10,   10, 0x08,
      51,   10,   10,   10, 0x08,
      67,   10,   10,   10, 0x08,
      85,   10,   10,   10, 0x08,
     104,   10,   10,   10, 0x08,
     126,   10,   10,   10, 0x08,
     150,   10,   10,   10, 0x08,
     161,   10,   10,   10, 0x08,
     187,  173,   10,   10, 0x08,
     213,   10,   10,   10, 0x08,
     224,   10,   10,   10, 0x08,
     243,  239,   10,   10, 0x08,
     268,   10,   10,   10, 0x08,
     285,   10,   10,   10, 0x08,
     291,   10,   10,   10, 0x08,
     298,   10,   10,   10, 0x08,
     306,   10,   10,   10, 0x08,
     329,  323,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SCgWindow[] = {
    "SCgWindow\0\0onSelectMode()\0onPairMode()\0"
    "onBusMode()\0onContourMode()\0"
    "onGridAlignment()\0onTupleAlignment()\0"
    "onVerticalAlignment()\0onHorizontalAlignment()\0"
    "onZoomIn()\0onZoomOut()\0newScaleValue\0"
    "onViewScaleChanged(qreal)\0findNext()\0"
    "findPrevious()\0ttf\0findTextChanged(QString)\0"
    "showTextSearch()\0cut()\0copy()\0paste()\0"
    "deleteSelected()\0value\0"
    "stackCleanStateChanged(bool)\0"
};

void SCgWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCgWindow *_t = static_cast<SCgWindow *>(_o);
        switch (_id) {
        case 0: _t->onSelectMode(); break;
        case 1: _t->onPairMode(); break;
        case 2: _t->onBusMode(); break;
        case 3: _t->onContourMode(); break;
        case 4: _t->onGridAlignment(); break;
        case 5: _t->onTupleAlignment(); break;
        case 6: _t->onVerticalAlignment(); break;
        case 7: _t->onHorizontalAlignment(); break;
        case 8: _t->onZoomIn(); break;
        case 9: _t->onZoomOut(); break;
        case 10: _t->onViewScaleChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 11: _t->findNext(); break;
        case 12: _t->findPrevious(); break;
        case 13: _t->findTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->showTextSearch(); break;
        case 15: _t->cut(); break;
        case 16: _t->copy(); break;
        case 17: _t->paste(); break;
        case 18: _t->deleteSelected(); break;
        case 19: _t->stackCleanStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SCgWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SCgWindow,
      qt_meta_data_SCgWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgWindow))
        return static_cast<void*>(const_cast< SCgWindow*>(this));
    if (!strcmp(_clname, "EditorInterface"))
        return static_cast< EditorInterface*>(const_cast< SCgWindow*>(this));
    if (!strcmp(_clname, "com.OSTIS.kbe.EditorInterface/1.0"))
        return static_cast< EditorInterface*>(const_cast< SCgWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int SCgWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
static const uint qt_meta_data_SCgWindowFactory[] = {

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

static const char qt_meta_stringdata_SCgWindowFactory[] = {
    "SCgWindowFactory\0"
};

void SCgWindowFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCgWindowFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgWindowFactory::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SCgWindowFactory,
      qt_meta_data_SCgWindowFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgWindowFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgWindowFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgWindowFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgWindowFactory))
        return static_cast<void*>(const_cast< SCgWindowFactory*>(this));
    if (!strcmp(_clname, "EditorFactoryInterface"))
        return static_cast< EditorFactoryInterface*>(const_cast< SCgWindowFactory*>(this));
    if (!strcmp(_clname, "com.OSTIS.kbe.EditorFactoryInterface/1.0"))
        return static_cast< EditorFactoryInterface*>(const_cast< SCgWindowFactory*>(this));
    return QObject::qt_metacast(_clname);
}

int SCgWindowFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
