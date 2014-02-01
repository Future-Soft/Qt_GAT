/****************************************************************************
** Meta object code from reading C++ file 'tracker.h'
**
** Created: Tue Apr 10 15:49:19 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tracker.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tracker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Tracker[] = {

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
       9,    8,    8,    8, 0x08,
      25,   19,    8,    8, 0x08,

 // methods: signature, parameters, type, tag, flags
      60,   55,    8,    8, 0x02,
      85,   79,    8,    8, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Tracker[] = {
    "Tracker\0\0runTask()\0reply\0"
    "replyFinished(QNetworkReply*)\0page\0"
    "trackPage(QString)\0event\0trackEvent(QString)\0"
};

const QMetaObject Tracker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tracker,
      qt_meta_data_Tracker, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Tracker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Tracker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Tracker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Tracker))
        return static_cast<void*>(const_cast< Tracker*>(this));
    return QObject::qt_metacast(_clname);
}

int Tracker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: runTask(); break;
        case 1: replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: trackPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: trackEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
