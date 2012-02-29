/****************************************************************************
** Meta object code from reading C++ file 'm4scpcodeeditor.h'
**
** Created: Tue Feb 28 22:47:24 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../m4scpcodeeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'm4scpcodeeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_M4SCpCodeEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      47,   45,   16,   16, 0x08,
      85,   79,   16,   16, 0x08,
     115,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_M4SCpCodeEditor[] = {
    "M4SCpCodeEditor\0\0updateLineNumberAreaWidth()\0"
    ",\0updateLineNumberArea(QRect,int)\0"
    "index\0insertCompletion(QModelIndex)\0"
    "changeSelection()\0"
};

const QMetaObject M4SCpCodeEditor::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_M4SCpCodeEditor,
      qt_meta_data_M4SCpCodeEditor, 0 }
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
        switch (_id) {
        case 0: updateLineNumberAreaWidth(); break;
        case 1: updateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: insertCompletion((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: changeSelection(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
