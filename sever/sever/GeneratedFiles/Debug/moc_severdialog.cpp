/****************************************************************************
** Meta object code from reading C++ file 'severdialog.h'
**
** Created: Wed Jun 24 16:59:20 2020
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../severdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'severdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SeverDialog[] = {

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
      13,   12,   12,   12, 0x0a,
      21,   12,   12,   12, 0x0a,
      40,   12,   12,   12, 0x0a,
      74,   62,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SeverDialog[] = {
    "SeverDialog\0\0start()\0acceptConnection()\0"
    "updateSeverProgress()\0soket_error\0"
    "displayError(QAbstractSocket::SocketError)\0"
};

const QMetaObject SeverDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SeverDialog,
      qt_meta_data_SeverDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SeverDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SeverDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SeverDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SeverDialog))
        return static_cast<void*>(const_cast< SeverDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SeverDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: start(); break;
        case 1: acceptConnection(); break;
        case 2: updateSeverProgress(); break;
        case 3: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
