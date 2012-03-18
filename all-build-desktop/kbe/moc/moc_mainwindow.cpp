/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Mar 18 14:58:05 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../sources/kbe/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      25,   11,   11,   11, 0x0a,
      49,   11,   11,   11, 0x0a,
      75,   11,   11,   11, 0x0a,
      92,   11,   11,   11, 0x0a,
     102,   11,   11,   11, 0x0a,
     120,  113,   11,   11, 0x0a,
     139,   11,   11,   11, 0x2a,
     150,  113,   11,   11, 0x0a,
     171,   11,   11,   11, 0x2a,
     184,   11,   11,   11, 0x0a,
     198,   11,   11,   11, 0x0a,
     218,   11,   11,   11, 0x0a,
     229,   11,   11,   11, 0x0a,
     241,   11,   11,   11, 0x0a,
     261,  255,   11,   11, 0x0a,
     288,  286,   11,   11, 0x0a,
     322,  317,   11,   11, 0x0a,
     352,  346,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0updateMenu()\0"
    "updateSpcificViewMenu()\0"
    "updateRecentFileActions()\0openRecentFile()\0"
    "fileNew()\0fileOpen()\0window\0"
    "fileSave(QWidget*)\0fileSave()\0"
    "fileSaveAs(QWidget*)\0fileSaveAs()\0"
    "fileSaveAll()\0fileExportToImage()\0"
    "fileExit()\0helpAbout()\0helpAboutQt()\0"
    "index\0subWindowHasChanged(int)\0w\0"
    "windowWillBeClosed(QWidget*)\0hide\0"
    "updateDockWidgets(bool)\0event\0"
    "closeEvent(QCloseEvent*)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->updateMenu(); break;
        case 1: _t->updateSpcificViewMenu(); break;
        case 2: _t->updateRecentFileActions(); break;
        case 3: _t->openRecentFile(); break;
        case 4: _t->fileNew(); break;
        case 5: _t->fileOpen(); break;
        case 6: _t->fileSave((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 7: _t->fileSave(); break;
        case 8: _t->fileSaveAs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 9: _t->fileSaveAs(); break;
        case 10: _t->fileSaveAll(); break;
        case 11: _t->fileExportToImage(); break;
        case 12: _t->fileExit(); break;
        case 13: _t->helpAbout(); break;
        case 14: _t->helpAboutQt(); break;
        case 15: _t->subWindowHasChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->windowWillBeClosed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 17: _t->updateDockWidgets((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "EditorObserverInterface"))
        return static_cast< EditorObserverInterface*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "com.OSTIS.kbe.EditorObserverInterface/1.0"))
        return static_cast< EditorObserverInterface*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
