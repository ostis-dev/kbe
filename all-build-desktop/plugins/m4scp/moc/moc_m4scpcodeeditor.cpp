/****************************************************************************
** Meta object code from reading C++ file 'm4scpcodeeditor.h'
**
** Created: Sun Mar 18 14:48:06 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sources/plugins/m4scp/m4scpcodeeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'm4scpcodeeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_M4SCpCodeEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      42,   40,   16,   16, 0x08,
      69,   16,   16,   16, 0x08,
      95,   89,   16,   16, 0x08,
     125,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_M4SCpCodeEditor[] = {
    "M4SCpCodeEditor\0\0updateExtraAreaWidth()\0"
    ",\0updateExtraArea(QRect,int)\0"
    "updateBlockLevels()\0index\0"
    "insertCompletion(QModelIndex)\0"
    "changeSelection()\0"
};

void M4SCpCodeEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        M4SCpCodeEditor *_t = static_cast<M4SCpCodeEditor *>(_o);
        switch (_id) {
        case 0: _t->updateExtraAreaWidth(); break;
        case 1: _t->updateExtraArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->updateBlockLevels(); break;
        case 3: _t->insertCompletion((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: _t->changeSelection(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData M4SCpCodeEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject M4SCpCodeEditor::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_M4SCpCodeEditor,
      qt_meta_data_M4SCpCodeEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &M4SCpCodeEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *M4SCpCodeEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *M4SCpCodeEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_M4SCpCodeEditor))
        return static_cast<void*>(const_cast< M4SCpCodeEditor*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int M4SCpCodeEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
