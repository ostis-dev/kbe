/****************************************************************************
** Meta object code from reading C++ file 'm4scpwindow.h'
**
** Created: Sun Mar 18 14:48:05 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/m4scp/m4scpwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'm4scpwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_M4SCpWindow[] = {

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

static const char qt_meta_stringdata_M4SCpWindow[] = {
    "M4SCpWindow\0"
};

void M4SCpWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData M4SCpWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject M4SCpWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_M4SCpWindow,
      qt_meta_data_M4SCpWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &M4SCpWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *M4SCpWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *M4SCpWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_M4SCpWindow))
        return static_cast<void*>(const_cast< M4SCpWindow*>(this));
    if (!strcmp(_clname, "EditorInterface"))
        return static_cast< EditorInterface*>(const_cast< M4SCpWindow*>(this));
    if (!strcmp(_clname, "com.OSTIS.kbe.EditorInterface/1.0"))
        return static_cast< EditorInterface*>(const_cast< M4SCpWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int M4SCpWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_M4SCpWindowFactory[] = {

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

static const char qt_meta_stringdata_M4SCpWindowFactory[] = {
    "M4SCpWindowFactory\0"
};

void M4SCpWindowFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData M4SCpWindowFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject M4SCpWindowFactory::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_M4SCpWindowFactory,
      qt_meta_data_M4SCpWindowFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &M4SCpWindowFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *M4SCpWindowFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *M4SCpWindowFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_M4SCpWindowFactory))
        return static_cast<void*>(const_cast< M4SCpWindowFactory*>(this));
    if (!strcmp(_clname, "EditorFactoryInterface"))
        return static_cast< EditorFactoryInterface*>(const_cast< M4SCpWindowFactory*>(this));
    if (!strcmp(_clname, "com.OSTIS.kbe.EditorFactoryInterface/1.0"))
        return static_cast< EditorFactoryInterface*>(const_cast< M4SCpWindowFactory*>(this));
    return QObject::qt_metacast(_clname);
}

int M4SCpWindowFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
