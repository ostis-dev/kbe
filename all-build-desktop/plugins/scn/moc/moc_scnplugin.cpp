/****************************************************************************
** Meta object code from reading C++ file 'scnplugin.h'
**
** Created: Sun Mar 18 14:49:56 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scn/scnplugin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scnplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCnPlugin[] = {

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

static const char qt_meta_stringdata_SCnPlugin[] = {
    "SCnPlugin\0"
};

void SCnPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SCnPlugin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCnPlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SCnPlugin,
      qt_meta_data_SCnPlugin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCnPlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCnPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCnPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCnPlugin))
        return static_cast<void*>(const_cast< SCnPlugin*>(this));
    if (!strcmp(_clname, "PluginInterface"))
        return static_cast< PluginInterface*>(const_cast< SCnPlugin*>(this));
    if (!strcmp(_clname, "com.OSTIS.kbe.PluginInterface/1.0"))
        return static_cast< PluginInterface*>(const_cast< SCnPlugin*>(this));
    return QObject::qt_metacast(_clname);
}

int SCnPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
