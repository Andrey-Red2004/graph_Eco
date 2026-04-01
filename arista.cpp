#include "Arista.h"

Arista::Arista(int id, int nodoOrigenId, int nodoDestinoId,
    double distancia, TipoAcceso acceso)
    : id_(id), origenId_(nodoOrigenId), destinoId_(nodoDestinoId),
    distancia_(distancia), acceso_(acceso)
{
}

double Arista::getPesoEfectivo(bool movilidadReducida) const {
    if (bloqueada_) return -1.0; // Ruta no disponible

    if (!movilidadReducida) return distancia_;

    // Lógica de movilidad reducida
    switch (acceso_) {
    case TipoAcceso::SoloGradas:
        // Completamente inaccesible para silla de ruedas / muletas
        return -1.0;

    case TipoAcceso::Pendiente:
        // Costo extra del 80% por dificultad en pendientes
        return distancia_ * 1.8;

    case TipoAcceso::SoloRampa:
        // Pequeño factor extra por el esfuerzo de la rampa (20%)
        return distancia_ * 1.2;

    case TipoAcceso::Normal:
    default:
        return distancia_;
    }
}

std::string tipoAccesoToString(TipoAcceso t) {
    switch (t) {
    case TipoAcceso::Normal:      return "Normal";
    case TipoAcceso::SoloRampa:   return "SoloRampa";
    case TipoAcceso::SoloGradas:  return "SoloGradas";
    case TipoAcceso::Pendiente:   return "Pendiente";
    default:                      return "Normal";
    }
}

TipoAcceso stringToTipoAcceso(const std::string& s) {
    if (s == "SoloRampa")  return TipoAcceso::SoloRampa;
    if (s == "SoloGradas") return TipoAcceso::SoloGradas;
    if (s == "Pendiente")  return TipoAcceso::Pendiente;
    return TipoAcceso::Normal;
}