/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../foOscars/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "newMessage",
    "",
    "message",
    "startGame",
    "hostClicked",
    "displayMessageFromServer",
    "connectClicked",
    "readSocket",
    "displayMessage",
    "str",
    "displayError",
    "QAbstractSocket::SocketError",
    "socketError",
    "sendChatMessage",
    "cardPlayed",
    "nextActionClicked",
    "PreviousActionClicked",
    "updateTableauAfterActionCardSelectSlot",
    "actionCardFromPersonalPileSelected",
    "cardID",
    "Card",
    "actionCard",
    "onStartClicked",
    "displayPopUp",
    "index",
    "tableauCardClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[54];
    char stringdata0[11];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[10];
    char stringdata5[12];
    char stringdata6[25];
    char stringdata7[15];
    char stringdata8[11];
    char stringdata9[15];
    char stringdata10[4];
    char stringdata11[13];
    char stringdata12[29];
    char stringdata13[12];
    char stringdata14[16];
    char stringdata15[11];
    char stringdata16[18];
    char stringdata17[22];
    char stringdata18[39];
    char stringdata19[35];
    char stringdata20[7];
    char stringdata21[5];
    char stringdata22[11];
    char stringdata23[15];
    char stringdata24[13];
    char stringdata25[6];
    char stringdata26[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 10),  // "newMessage"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 7),  // "message"
        QT_MOC_LITERAL(31, 9),  // "startGame"
        QT_MOC_LITERAL(41, 11),  // "hostClicked"
        QT_MOC_LITERAL(53, 24),  // "displayMessageFromServer"
        QT_MOC_LITERAL(78, 14),  // "connectClicked"
        QT_MOC_LITERAL(93, 10),  // "readSocket"
        QT_MOC_LITERAL(104, 14),  // "displayMessage"
        QT_MOC_LITERAL(119, 3),  // "str"
        QT_MOC_LITERAL(123, 12),  // "displayError"
        QT_MOC_LITERAL(136, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(165, 11),  // "socketError"
        QT_MOC_LITERAL(177, 15),  // "sendChatMessage"
        QT_MOC_LITERAL(193, 10),  // "cardPlayed"
        QT_MOC_LITERAL(204, 17),  // "nextActionClicked"
        QT_MOC_LITERAL(222, 21),  // "PreviousActionClicked"
        QT_MOC_LITERAL(244, 38),  // "updateTableauAfterActionCardS..."
        QT_MOC_LITERAL(283, 34),  // "actionCardFromPersonalPileSel..."
        QT_MOC_LITERAL(318, 6),  // "cardID"
        QT_MOC_LITERAL(325, 4),  // "Card"
        QT_MOC_LITERAL(330, 10),  // "actionCard"
        QT_MOC_LITERAL(341, 14),  // "onStartClicked"
        QT_MOC_LITERAL(356, 12),  // "displayPopUp"
        QT_MOC_LITERAL(369, 5),  // "index"
        QT_MOC_LITERAL(375, 18)   // "tableauCardClicked"
    },
    "MainWindow",
    "newMessage",
    "",
    "message",
    "startGame",
    "hostClicked",
    "displayMessageFromServer",
    "connectClicked",
    "readSocket",
    "displayMessage",
    "str",
    "displayError",
    "QAbstractSocket::SocketError",
    "socketError",
    "sendChatMessage",
    "cardPlayed",
    "nextActionClicked",
    "PreviousActionClicked",
    "updateTableauAfterActionCardSelectSlot",
    "actionCardFromPersonalPileSelected",
    "cardID",
    "Card",
    "actionCard",
    "onStartClicked",
    "displayPopUp",
    "index",
    "tableauCardClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  116,    2, 0x06,    1 /* Public */,
       4,    0,  119,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,  120,    2, 0x0a,    4 /* Public */,
       6,    1,  121,    2, 0x0a,    5 /* Public */,
       7,    0,  124,    2, 0x0a,    7 /* Public */,
       8,    0,  125,    2, 0x0a,    8 /* Public */,
       9,    1,  126,    2, 0x0a,    9 /* Public */,
      11,    1,  129,    2, 0x0a,   11 /* Public */,
      14,    0,  132,    2, 0x0a,   13 /* Public */,
      15,    0,  133,    2, 0x0a,   14 /* Public */,
      16,    0,  134,    2, 0x0a,   15 /* Public */,
      17,    0,  135,    2, 0x0a,   16 /* Public */,
      18,    0,  136,    2, 0x0a,   17 /* Public */,
      19,    2,  137,    2, 0x0a,   18 /* Public */,
      23,    0,  142,    2, 0x0a,   21 /* Public */,
      24,    1,  143,    2, 0x0a,   22 /* Public */,
      26,    0,  146,    2, 0x0a,   24 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    1,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 21,   20,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'newMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'startGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hostClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayMessageFromServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'connectClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readSocket'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'displayError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>,
        // method 'sendChatMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cardPlayed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nextActionClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'PreviousActionClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTableauAfterActionCardSelectSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'actionCardFromPersonalPileSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<Card, std::false_type>,
        // method 'onStartClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayPopUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'tableauCardClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->startGame(); break;
        case 2: _t->hostClicked(); break;
        case 3: _t->displayMessageFromServer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->connectClicked(); break;
        case 5: _t->readSocket(); break;
        case 6: _t->displayMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->displayError((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 8: _t->sendChatMessage(); break;
        case 9: _t->cardPlayed(); break;
        case 10: _t->nextActionClicked(); break;
        case 11: _t->PreviousActionClicked(); break;
        case 12: _t->updateTableauAfterActionCardSelectSlot(); break;
        case 13: _t->actionCardFromPersonalPileSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Card>>(_a[2]))); break;
        case 14: _t->onStartClicked(); break;
        case 15: _t->displayPopUp((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->tableauCardClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString );
            if (_t _q_method = &MainWindow::newMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::startGame; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::newMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::startGame()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
