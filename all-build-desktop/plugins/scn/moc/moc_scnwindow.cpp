/****************************************************************************
** Meta object code from reading C++ file 'scnwindow.h'
**
** Created: Sun Mar 18 14:49:57 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scn/scnwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scnwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCnWindow[] = {

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

static const char qt_meta_stringdata_SCnWindow[] = {
    "SCnWindow\0"
};

void SCnWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCnWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCnWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SCnWindow,
      qt_meta_data_SCnWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCnWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCnWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCnWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCnWindow))
        return static_cast<void*>(const_cast< SCnWindow*>(this));
    if (!strcmp(_clname, "EditorInterface"))
        return static_cast< EditorInterface*>(const_cast< SCnWindow*>(this));
    if (!strcmp(_clname, "com.OSTIS.kbe.EditorInterface/1.0"))
        return static_cast< EditorInterface*>(const_cast< SCnWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int SCnWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_SCnWindowFactory[] = {

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

static const char qt_meta_stringdata_SCnWindowFactory[] = {
    "SCnWindowFactory\0"
};

void SCnWindowFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCnWindowFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCnWindowFactory::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SCnWindowFactory,
      qt_meta_data_SCnWindowFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCnWindowFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCnWindowFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCnWindowFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCnWindowFactory))
        return static_cast<void*>(const_cast< SCnWindowFactory*>(this));
    if (!strcmp(_clname, "EditorFactoryInterface"))
        return static_cast< EditorFactoryInterface*>(const_cast< SCnWindowFactory*>(this));
    if (!strcmp(_clname, "com.OSTIS.kbe.EditorFactoryInterface/1.0"))
        return static_cast< EditorFactoryInterface*>(const_cast< SCnWindowFactory*>(this));
    return QObject::qt_metacast(_clname);
}

int SCnWindowFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
