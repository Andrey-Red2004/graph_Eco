#pragma once
#include <string>

// Restricciones de accesibilidad de la arista
enum class TipoAcceso {
    Normal,          // Apta para todos
    SoloRampa,       // Hay rampa pero no gradas (silla de ruedas: OK)
    SoloGradas,      // Solo gradas, sin rampa (silla de ruedas: bloqueada)
    Pendiente        // Pendiente pronunciada (muletas/silla: peso aumentado)
};

std::string tipoAccesoToString(TipoAcceso t);
TipoAcceso  stringToTipoAcceso(const std::string& s);

class Arista {
public:
    Arista() = default;
    Arista(int id, int nodoOrigenId, int nodoDestinoId,
        double distancia, TipoAcceso acceso = TipoAcceso::Normal);

    // Getters base
    int    getId()           const { return id_; }
    int    getOrigenId()     const { return origenId_; }
    int    getDestinoId()    const { return destinoId_; }
    double getDistancia()    const { return distancia_; }
    TipoAcceso getTipoAcceso() const { return acceso_; }
    bool   isBloqueada()     const { return bloqueada_; }

    // Peso efectivo según el perfil del usuario
    // factorMovilidad: 1.0 = normal, >1.0 = movilidad reducida aumenta el costo
    // Si la arista es SoloGradas y movilidad reducida → retorna -1 (no disponible)
    double getPesoEfectivo(bool movilidadReducida) const;

    // Setters
    void setBloqueada(bool b) { bloqueada_ = b; }
    void setDistancia(double d) { distancia_ = d; }

private:
    int        id_ = -1;
    int        origenId_ = -1;
    int        destinoId_ = -1;
    double     distancia_ = 0.0;   // metros
    TipoAcceso acceso_ = TipoAcceso::Normal;
    bool       bloqueada_ = false; // Punto de fallo activo
};