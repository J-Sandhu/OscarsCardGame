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
    "updateTableauAfterActionCardSelectSlot",
    "onStartClicked",
    "displayPopUp",
    "index",
    "tableauCardClicked",
    "actionCardClicked",
    "anotherPlayerPersonCardClicked",
    "updateActionHand",
    "std::vector<QImage>",
    "images",
    "playerButtonClicked",
    "displayWinnerAndConfettiSlot",
    "endGameClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[56];
    char stringdata0[11];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[12];
    char stringdata5[25];
    char stringdata6[15];
    char stringdata7[11];
    char stringdata8[15];
    char stringdata9[4];
    char stringdata10[13];
    char stringdata11[29];
    char stringdata12[12];
    char stringdata13[16];
    char stringdata14[11];
    char stringdata15[39];
    char stringdata16[15];
    char stringdata17[13];
    char stringdata18[6];
    char stringdata19[19];
    char stringdata20[18];
    char stringdata21[31];
    char stringdata22[17];
    char stringdata23[20];
    char stringdata24[7];
    char stringdata25[20];
    char stringdata26[29];
    char stringdata27[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 10),  // "newMessage"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 7),  // "message"
        QT_MOC_LITERAL(31, 11),  // "hostClicked"
        QT_MOC_LITERAL(43, 24),  // "displayMessageFromServer"
        QT_MOC_LITERAL(68, 14),  // "connectClicked"
        QT_MOC_LITERAL(83, 10),  // "readSocket"
        QT_MOC_LITERAL(94, 14),  // "displayMessage"
        QT_MOC_LITERAL(109, 3),  // "str"
        QT_MOC_LITERAL(113, 12),  // "displayError"
        QT_MOC_LITERAL(126, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(155, 11),  // "socketError"
        QT_MOC_LITERAL(167, 15),  // "sendChatMessage"
        QT_MOC_LITERAL(183, 10),  // "cardPlayed"
        QT_MOC_LITERAL(194, 38),  // "updateTableauAfterActionCardS..."
        QT_MOC_LITERAL(233, 14),  // "onStartClicked"
        QT_MOC_LITERAL(248, 12),  // "displayPopUp"
        QT_MOC_LITERAL(261, 5),  // "index"
        QT_MOC_LITERAL(267, 18),  // "tableauCardClicked"
        QT_MOC_LITERAL(286, 17),  // "actionCardClicked"
        QT_MOC_LITERAL(304, 30),  // "anotherPlayerPersonCardClicked"
        QT_MOC_LITERAL(335, 16),  // "updateActionHand"
        QT_MOC_LITERAL(352, 19),  // "std::vector<QImage>"
        QT_MOC_LITERAL(372, 6),  // "images"
        QT_MOC_LITERAL(379, 19),  // "playerButtonClicked"
        QT_MOC_LITERAL(399, 28),  // "displayWinnerAndConfettiSlot"
        QT_MOC_LITERAL(428, 14)   // "endGameClicked"
    },
    "MainWindow",
    "newMessage",
    "",
    "message",
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
    "updateTableauAfterActionCardSelectSlot",
    "onStartClicked",
    "displayPopUp",
    "index",
    "tableauCardClicked",
    "actionCardClicked",
    "anotherPlayerPersonCardClicked",
    "updateActionHand",
    "std::vector<QImage>",
    "images",
    "playerButtonClicked",
    "displayWinnerAndConfettiSlot",
    "endGameClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  128,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,  131,    2, 0x0a,    3 /* Public */,
       5,    1,  132,    2, 0x0a,    4 /* Public */,
       6,    0,  135,    2, 0x0a,    6 /* Public */,
       7,    0,  136,    2, 0x0a,    7 /* Public */,
       8,    1,  137,    2, 0x0a,    8 /* Public */,
      10,    1,  140,    2, 0x0a,   10 /* Public */,
      13,    0,  143,    2, 0x0a,   12 /* Public */,
      14,    0,  144,    2, 0x0a,   13 /* Public */,
      15,    0,  145,    2, 0x0a,   14 /* Public */,
      16,    0,  146,    2, 0x0a,   15 /* Public */,
      17,    1,  147,    2, 0x0a,   16 /* Public */,
      19,    0,  150,    2, 0x0a,   18 /* Public */,
      20,    0,  151,    2, 0x0a,   19 /* Public */,
      21,    0,  152,    2, 0x0a,   20 /* Public */,
      22,    1,  153,    2, 0x0a,   21 /* Public */,
      25,    0,  156,    2, 0x0a,   23 /* Public */,
      26,    0,  157,    2, 0x0a,   24 /* Public */,
      27,    0,  158,    2, 0x0a,   25 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    1,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void,
    QMetaType::Void,
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
        // method 'updateTableauAfterActionCardSelectSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStartClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayPopUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'tableauCardClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'actionCardClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'anotherPlayerPersonCardClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateActionHand'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::vector<QImage>, std::false_type>,
        // method 'playerButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayWinnerAndConfettiSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'endGameClicked'
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
        case 1: _t->hostClicked(); break;
        case 2: _t->displayMessageFromServer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->connectClicked(); break;
        case 4: _t->readSocket(); break;
        case 5: _t->displayMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->displayError((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 7: _t->sendChatMessage(); break;
        case 8: _t->cardPlayed(); break;
        case 9: _t->updateTableauAfterActionCardSelectSlot(); break;
        case 10: _t->onStartClicked(); break;
        case 11: _t->displayPopUp((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->tableauCardClicked(); break;
        case 13: _t->actionCardClicked(); break;
        case 14: _t->anotherPlayerPersonCardClicked(); break;
        case 15: _t->updateActionHand((*reinterpret_cast< std::add_pointer_t<std::vector<QImage>>>(_a[1]))); break;
        case 16: _t->playerButtonClicked(); break;
        case 17: _t->displayWinnerAndConfettiSlot(); break;
        case 18: _t->endGameClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
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
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::newMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
