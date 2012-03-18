/****************************************************************************
** Meta object code from reading C++ file 'scswindow.h'
**
** Created: Sun Mar 18 14:57:55 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scs/scswindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCsWindow[] = {

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

static const char qt_meta_stringdata_SCsWindow[] = {
    "SCsWindow\0"
};

void SCsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCsWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCsWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SCsWindow,
      qt_meta_data_SCsWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCsWindow))
        return static_cast<void*>(const_cast< SCsWindow*>(this));
    if (!strcmp(_clname, "EditorInterface"))
        return static_cast< EditorInterface*>(const_cast< SCsWindow*>(this));
    if (!strcmp(_clname, "com.OSTIS.kbe.EditorInterface/1.0"))
        return static_cast< EditorInterface*>(const_cast< SCsWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int SCsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_SCsWindowFactory[] = {

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

static const char qt_meta_stringdata_SCsWindowFactory[] = {
    "SCsWindowFactory\0"
};

void SCsWindowFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCsWindowFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCsWindowFactory::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SCsWindowFactory,
      qt_meta_data_SCsWindowFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCsWindowFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCsWindowFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCsWindowFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCsWindowFactory))
        return static_cast<void*>(const_cast< SCsWindowFactory*>(this));
    if (!strcmp(_clname, "EditorFactoryInterface"))
        return static_cast< EditorFactoryInterface*>(const_cast< SCsWindowFactory*>(this));
    if (!strcmp(_clname, "com.OSTIS.kbe.EditorFactoryInterface/1.0"))
        return static_cast< EditorFactoryInterface*>(const_cast< SCsWindowFactory*>(this));
    return QObject::qt_metacast(_clname);
}

int SCsWindowFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
