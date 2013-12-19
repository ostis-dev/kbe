/****************************************************************************
** Meta object code from reading C++ file 'scgview.h'
**
** Created: Thu 19. Dec 10:55:20 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/scg/scgview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scgview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCgView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,    9,    8,    8, 0x05,
      52,   44,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,   77,    8,    8, 0x08,
     105,    8,    8,    8, 0x28,
     126,    8,    8,    8, 0x08,
     148,  145,    8,    8, 0x0a,
     178,  166,    8,    8, 0x0a,
     200,  194,    8,    8, 0x0a,
     220,    8,    8,    8, 0x08,
     237,    8,    8,    8, 0x08,
     257,    8,    8,    8, 0x08,
     274,    8,    8,    8, 0x08,
     300,  293,    8,    8, 0x08,
     321,    8,    8,    8, 0x08,
     348,  337,    8,    8, 0x08,
     372,    8,    8,    8, 0x08,
     393,  388,    8,    8, 0x08,
     422,  417,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SCgView[] = {
    "SCgView\0\0newScaleFactor\0scaleChanged(qreal)\0"
    "newRect\0sceneRectChanged(QRectF)\0idx\0"
    "updateActionsState(int)\0updateActionsState()\0"
    "selectAllCommand()\0sc\0setScale(QString)\0"
    "scaleFactor\0setScale(qreal)\0scene\0"
    "setScene(SCgScene*)\0deleteSelected()\0"
    "deleteJustContour()\0swapPairOrient()\0"
    "changeIdentifier()\0action\0"
    "changeType(QAction*)\0changeContent()\0"
    "visibility\0setContentVisible(bool)\0"
    "deleteContent()\0rect\0updateSceneRect(QRectF)\0"
    "mode\0editModeChanged(int)\0"
};

void SCgView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCgView *_t = static_cast<SCgView *>(_o);
        switch (_id) {
        case 0: _t->scaleChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->sceneRectChanged((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 2: _t->updateActionsState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateActionsState(); break;
        case 4: _t->selectAllCommand(); break;
        case 5: _t->setScale((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->setScale((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 7: _t->setScene((*reinterpret_cast< SCgScene*(*)>(_a[1]))); break;
        case 8: _t->deleteSelected(); break;
        case 9: _t->deleteJustContour(); break;
        case 10: _t->swapPairOrient(); break;
        case 11: _t->changeIdentifier(); break;
        case 12: _t->changeType((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 13: _t->changeContent(); break;
        case 14: _t->setContentVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->deleteContent(); break;
        case 16: _t->updateSceneRect((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 17: _t->editModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SCgView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCgView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_SCgView,
      qt_meta_data_SCgView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCgView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCgView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCgView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCgView))
        return static_cast<void*>(const_cast< SCgView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int SCgView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void SCgView::scaleChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SCgView::sceneRectChanged(const QRectF & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
