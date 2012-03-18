/****************************************************************************
** Meta object code from reading C++ file 'scgfindwidget.h'
**
** Created: Sun Mar 18 14:49:45 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/scgfindwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scgfindwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgFindWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      31,   14,   14,   14, 0x05,
      42,   14,   14,   14, 0x05,
      62,   57,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      76,   14,   14,   14, 0x08,
      92,   57,   14,   14, 0x08,
     113,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SCgFindWidget[] = {
    "SCgFindWidget\0\0escapePressed()\0"
    "findNext()\0findPrevious()\0text\0"
    "find(QString)\0updateButtons()\0"
    "textChanged(QString)\0caseSensitivityChanged(int)\0"
};

void SCgFindWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCgFindWidget *_t = static_cast<SCgFindWidget *>(_o);
        switch (_id) {
        case 0: _t->escapePressed(); break;
        case 1: _t->findNext(); break;
        case 2: _t->findPrevious(); break;
        case 3: _t->find((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateButtons(); break;
        case 5: _t->textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->caseSensitivityChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SCgFindWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgFindWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SCgFindWidget,
      qt_meta_data_SCgFindWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgFindWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgFindWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgFindWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgFindWidget))
        return static_cast<void*>(const_cast< SCgFindWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SCgFindWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void SCgFindWidget::escapePressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SCgFindWidget::findNext()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SCgFindWidget::findPrevious()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SCgFindWidget::find(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
