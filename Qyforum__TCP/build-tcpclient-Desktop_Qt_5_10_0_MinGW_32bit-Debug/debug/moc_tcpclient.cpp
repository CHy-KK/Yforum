/****************************************************************************
** Meta object code from reading C++ file 'tcpclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tcpclient/tcpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tcpclient_t {
    QByteArrayData data[25];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcpclient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcpclient_t qt_meta_stringdata_tcpclient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "tcpclient"
QT_MOC_LITERAL(1, 10, 9), // "goto_send"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 10), // "goto_login"
QT_MOC_LITERAL(4, 32, 10), // "goto_level"
QT_MOC_LITERAL(5, 43, 7), // "initial"
QT_MOC_LITERAL(6, 51, 6), // "log_in"
QT_MOC_LITERAL(7, 58, 8), // "Register"
QT_MOC_LITERAL(8, 67, 8), // "postview"
QT_MOC_LITERAL(9, 76, 10), // "typechoose"
QT_MOC_LITERAL(10, 87, 6), // "inpost"
QT_MOC_LITERAL(11, 94, 7), // "login_2"
QT_MOC_LITERAL(12, 102, 7), // "login_3"
QT_MOC_LITERAL(13, 110, 5), // "ptype"
QT_MOC_LITERAL(14, 116, 10), // "newConnect"
QT_MOC_LITERAL(15, 127, 11), // "std::string"
QT_MOC_LITERAL(16, 139, 1), // "a"
QT_MOC_LITERAL(17, 141, 1), // "b"
QT_MOC_LITERAL(18, 143, 11), // "readMessage"
QT_MOC_LITERAL(19, 155, 11), // "sendMessage"
QT_MOC_LITERAL(20, 167, 13), // "state_initial"
QT_MOC_LITERAL(21, 181, 11), // "state_login"
QT_MOC_LITERAL(22, 193, 16), // "state_typechoose"
QT_MOC_LITERAL(23, 210, 14), // "state_postview"
QT_MOC_LITERAL(24, 225, 12) // "state_inpost"

    },
    "tcpclient\0goto_send\0\0goto_login\0"
    "goto_level\0initial\0log_in\0Register\0"
    "postview\0typechoose\0inpost\0login_2\0"
    "login_3\0ptype\0newConnect\0std::string\0"
    "a\0b\0readMessage\0sendMessage\0state_initial\0"
    "state_login\0state_typechoose\0"
    "state_postview\0state_inpost"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcpclient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06 /* Public */,
       3,    0,  110,    2, 0x06 /* Public */,
       4,    1,  111,    2, 0x06 /* Public */,
       5,    0,  114,    2, 0x06 /* Public */,
       6,    0,  115,    2, 0x06 /* Public */,
       7,    0,  116,    2, 0x06 /* Public */,
       8,    0,  117,    2, 0x06 /* Public */,
       9,    0,  118,    2, 0x06 /* Public */,
      10,    0,  119,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,  120,    2, 0x0a /* Public */,
      12,    1,  121,    2, 0x0a /* Public */,
      14,    2,  124,    2, 0x0a /* Public */,
      18,    0,  129,    2, 0x0a /* Public */,
      19,    0,  130,    2, 0x0a /* Public */,
      20,    0,  131,    2, 0x0a /* Public */,
      21,    0,  132,    2, 0x0a /* Public */,
      22,    0,  133,    2, 0x0a /* Public */,
      23,    0,  134,    2, 0x0a /* Public */,
      24,    0,  135,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int,   16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tcpclient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcpclient *_t = static_cast<tcpclient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->goto_send(); break;
        case 1: _t->goto_login(); break;
        case 2: _t->goto_level((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->initial(); break;
        case 4: _t->log_in(); break;
        case 5: _t->Register(); break;
        case 6: _t->postview(); break;
        case 7: _t->typechoose(); break;
        case 8: _t->inpost(); break;
        case 9: _t->login_2(); break;
        case 10: _t->login_3((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->newConnect((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->readMessage(); break;
        case 13: _t->sendMessage(); break;
        case 14: _t->state_initial(); break;
        case 15: _t->state_login(); break;
        case 16: _t->state_typechoose(); break;
        case 17: _t->state_postview(); break;
        case 18: _t->state_inpost(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (tcpclient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::goto_send)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (tcpclient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::goto_login)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (tcpclient::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::goto_level)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (tcpclient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::initial)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (tcpclient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::log_in)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (tcpclient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::Register)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (tcpclient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::postview)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (tcpclient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::typechoose)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (tcpclient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::inpost)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject tcpclient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_tcpclient.data,
      qt_meta_data_tcpclient,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *tcpclient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcpclient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tcpclient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int tcpclient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void tcpclient::goto_send()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void tcpclient::goto_login()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void tcpclient::goto_level(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void tcpclient::initial()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void tcpclient::log_in()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void tcpclient::Register()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void tcpclient::postview()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void tcpclient::typechoose()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void tcpclient::inpost()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
