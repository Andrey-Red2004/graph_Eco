#pragma once
#include <string>

// Tipos de nodo
enum class TipoNodo {
    EntradaPrincipal,
    Biblioteca,
    BloqueAulas,
    SodaComedor,
    Parqueo,
    ZonaEsparcimiento,
    OficinaAdministrativa,
    LabComputo,       // Punto sugerido, pero se puede cambiar
	Desconocido  // Para nodos no clasificados
};

// Convierte el enum a string legible
std::string tipoNodoToString(TipoNodo tipo);
TipoNodo stringToTipoNodo(const std::string& s);

class Nodo {
public:
    Nodo() = default;
    Nodo(int id, const std::string& nombre, TipoNodo tipo,
        double posX = 0.0, double posY = 0.0);

    // Getters
    int         getId()     const { return id_; }
    std::string getNombre() const { return nombre_; }
    TipoNodo    getTipo()   const { return tipo_; }
    double      getPosX()   const { return posX_; }
    double      getPosY()   const { return posY_; }
    bool        isBloqueado() const { return bloqueado_; }

    // Setters
    void setNombre(const std::string& nombre) { nombre_ = nombre; }
    void setBloqueado(bool b) { bloqueado_ = b; }
    void setPos(double x, double y) { posX_ = x; posY_ = y; }

    bool operator==(const Nodo& otro) const { return id_ == otro.id_; }

private:
    int         id_ = -1;
    std::string nombre_;
    TipoNodo    tipo_ = TipoNodo::Desconocido;
    double      posX_ = 0.0;   // Coordenada visual X (para Qt)
    double      posY_ = 0.0;   // Coordenada visual Y (para Qt)
    bool        bloqueado_ = false; // Punto de fallo activo
};