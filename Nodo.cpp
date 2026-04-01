#include "Nodo.h"

Nodo::Nodo(int id, const std::string& nombre, TipoNodo tipo,
    double posX, double posY)
    : id_(id), nombre_(nombre), tipo_(tipo), posX_(posX), posY_(posY)
{
}

std::string tipoNodoToString(TipoNodo tipo) {
    switch (tipo) {
    case TipoNodo::EntradaPrincipal:      return "EntradaPrincipal";
    case TipoNodo::Biblioteca:            return "Biblioteca";
    case TipoNodo::BloqueAulas:           return "BloqueAulas";
    case TipoNodo::SodaComedor:           return "SodaComedor";
    case TipoNodo::Parqueo:               return "Parqueo";
    case TipoNodo::ZonaEsparcimiento:     return "ZonaEsparcimiento";
    case TipoNodo::OficinaAdministrativa: return "OficinaAdministrativa";
    case TipoNodo::LabComputo:            return "LabComputo";
    default:                              return "Desconocido";
    }
}

TipoNodo stringToTipoNodo(const std::string& s) {
    if (s == "EntradaPrincipal")      return TipoNodo::EntradaPrincipal;
    if (s == "Biblioteca")            return TipoNodo::Biblioteca;
    if (s == "BloqueAulas")           return TipoNodo::BloqueAulas;
    if (s == "SodaComedor")           return TipoNodo::SodaComedor;
    if (s == "Parqueo")               return TipoNodo::Parqueo;
    if (s == "ZonaEsparcimiento")     return TipoNodo::ZonaEsparcimiento;
    if (s == "OficinaAdministrativa") return TipoNodo::OficinaAdministrativa;
    if (s == "LabComputo")            return TipoNodo::LabComputo;
    return TipoNodo::Desconocido;
}