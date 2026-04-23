/****************************************************************************
** Meta object code from reading C++ file 'EcoCampus.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../EcoCampus.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EcoCampus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
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
struct qt_meta_tag_ZN8UiBridgeE_t {};
} // unnamed namespace

template <> constexpr inline auto UiBridge::qt_create_metaobjectdata<qt_meta_tag_ZN8UiBridgeE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "UiBridge",
        "inicioChanged",
        "",
        "tiempoChanged",
        "visitadosChanged",
        "movilidadReducidaChanged",
        "enabled",
        "origenChanged",
        "destinoChanged",
        "perfilRutaChanged",
        "pisoActualChanged",
        "mostrarBibliotecaChanged",
        "mostrarComedorChanged",
        "dfsRequested",
        "bfsRequested",
        "buscarCaminoRequested",
        "rutaPerfilRequested",
        "requestDfs",
        "requestBfs",
        "requestBuscarCamino",
        "requestRutaPerfil",
        "inicio",
        "tiempo",
        "visitados",
        "movilidadReducida",
        "origen",
        "destino",
        "perfilRuta",
        "pisoActual",
        "mostrarBiblioteca",
        "mostrarComedor"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'inicioChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'tiempoChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'visitadosChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'movilidadReducidaChanged'
        QtMocHelpers::SignalData<void(bool)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 6 },
        }}),
        // Signal 'origenChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'destinoChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'perfilRutaChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'pisoActualChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'mostrarBibliotecaChanged'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'mostrarComedorChanged'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'dfsRequested'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bfsRequested'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'buscarCaminoRequested'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'rutaPerfilRequested'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'requestDfs'
        QtMocHelpers::MethodData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'requestBfs'
        QtMocHelpers::MethodData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'requestBuscarCamino'
        QtMocHelpers::MethodData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'requestRutaPerfil'
        QtMocHelpers::MethodData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'inicio'
        QtMocHelpers::PropertyData<int>(21, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'tiempo'
        QtMocHelpers::PropertyData<QString>(22, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'visitados'
        QtMocHelpers::PropertyData<QString>(23, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'movilidadReducida'
        QtMocHelpers::PropertyData<bool>(24, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'origen'
        QtMocHelpers::PropertyData<int>(25, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'destino'
        QtMocHelpers::PropertyData<int>(26, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'perfilRuta'
        QtMocHelpers::PropertyData<QString>(27, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'pisoActual'
        QtMocHelpers::PropertyData<QString>(28, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
        // property 'mostrarBiblioteca'
        QtMocHelpers::PropertyData<bool>(29, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'mostrarComedor'
        QtMocHelpers::PropertyData<bool>(30, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 9),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<UiBridge, qt_meta_tag_ZN8UiBridgeE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject UiBridge::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8UiBridgeE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8UiBridgeE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8UiBridgeE_t>.metaTypes,
    nullptr
} };

void UiBridge::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<UiBridge *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->inicioChanged(); break;
        case 1: _t->tiempoChanged(); break;
        case 2: _t->visitadosChanged(); break;
        case 3: _t->movilidadReducidaChanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->origenChanged(); break;
        case 5: _t->destinoChanged(); break;
        case 6: _t->perfilRutaChanged(); break;
        case 7: _t->pisoActualChanged(); break;
        case 8: _t->mostrarBibliotecaChanged(); break;
        case 9: _t->mostrarComedorChanged(); break;
        case 10: _t->dfsRequested(); break;
        case 11: _t->bfsRequested(); break;
        case 12: _t->buscarCaminoRequested(); break;
        case 13: _t->rutaPerfilRequested(); break;
        case 14: _t->requestDfs(); break;
        case 15: _t->requestBfs(); break;
        case 16: _t->requestBuscarCamino(); break;
        case 17: _t->requestRutaPerfil(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::inicioChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::tiempoChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::visitadosChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)(bool )>(_a, &UiBridge::movilidadReducidaChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::origenChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::destinoChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::perfilRutaChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::pisoActualChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::mostrarBibliotecaChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::mostrarComedorChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::dfsRequested, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::bfsRequested, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::buscarCaminoRequested, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (UiBridge::*)()>(_a, &UiBridge::rutaPerfilRequested, 13))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->inicio(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->tiempo(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->visitados(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->movilidadReducida(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->origen(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->destino(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->perfilRuta(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->pisoActual(); break;
        case 8: *reinterpret_cast<bool*>(_v) = _t->mostrarBiblioteca(); break;
        case 9: *reinterpret_cast<bool*>(_v) = _t->mostrarComedor(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setInicio(*reinterpret_cast<int*>(_v)); break;
        case 1: _t->setTiempo(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setVisitados(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setMovilidadReducida(*reinterpret_cast<bool*>(_v)); break;
        case 4: _t->setOrigen(*reinterpret_cast<int*>(_v)); break;
        case 5: _t->setDestino(*reinterpret_cast<int*>(_v)); break;
        case 6: _t->setPerfilRuta(*reinterpret_cast<QString*>(_v)); break;
        case 7: _t->setPisoActual(*reinterpret_cast<QString*>(_v)); break;
        case 8: _t->setMostrarBiblioteca(*reinterpret_cast<bool*>(_v)); break;
        case 9: _t->setMostrarComedor(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *UiBridge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UiBridge::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8UiBridgeE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UiBridge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 18;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void UiBridge::inicioChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void UiBridge::tiempoChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void UiBridge::visitadosChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void UiBridge::movilidadReducidaChanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void UiBridge::origenChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void UiBridge::destinoChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void UiBridge::perfilRutaChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void UiBridge::pisoActualChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void UiBridge::mostrarBibliotecaChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void UiBridge::mostrarComedorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void UiBridge::dfsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void UiBridge::bfsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void UiBridge::buscarCaminoRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void UiBridge::rutaPerfilRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}
namespace {
struct qt_meta_tag_ZN9EcoCampusE_t {};
} // unnamed namespace

template <> constexpr inline auto EcoCampus::qt_create_metaobjectdata<qt_meta_tag_ZN9EcoCampusE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "EcoCampus",
        "on_btnDFS_clicked",
        "",
        "on_btnBFS_clicked",
        "on_chkMovilidad_stateChanged",
        "state",
        "onSceneSelectionChanged",
        "onMovilidadChanged",
        "enabled",
        "onBuscarCamino_clicked",
        "onRutaPerfil_clicked",
        "onPerfilRutaChanged"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_btnDFS_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnBFS_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_chkMovilidad_stateChanged'
        QtMocHelpers::SlotData<void(int)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Slot 'onSceneSelectionChanged'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onMovilidadChanged'
        QtMocHelpers::SlotData<void(bool)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 8 },
        }}),
        // Slot 'onBuscarCamino_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRutaPerfil_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPerfilRutaChanged'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<EcoCampus, qt_meta_tag_ZN9EcoCampusE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject EcoCampus::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9EcoCampusE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9EcoCampusE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9EcoCampusE_t>.metaTypes,
    nullptr
} };

void EcoCampus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<EcoCampus *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_btnDFS_clicked(); break;
        case 1: _t->on_btnBFS_clicked(); break;
        case 2: _t->on_chkMovilidad_stateChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->onSceneSelectionChanged(); break;
        case 4: _t->onMovilidadChanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->onBuscarCamino_clicked(); break;
        case 6: _t->onRutaPerfil_clicked(); break;
        case 7: _t->onPerfilRutaChanged(); break;
        default: ;
        }
    }
}

const QMetaObject *EcoCampus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EcoCampus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9EcoCampusE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int EcoCampus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
