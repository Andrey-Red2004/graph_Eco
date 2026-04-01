#include "Grafo.h"
#include <algorithm>

// ── Construcción ──────────────────────────────────────────────────────────────

void Grafo::agregarNodo(const Nodo& nodo) {
    nodos_.push_back(nodo);
    if (adyacencia_.find(nodo.getId()) == adyacencia_.end())
        adyacencia_[nodo.getId()] = {};
}

void Grafo::agregarArista(const Arista& arista) {
    aristas_.push_back(arista);

    // Grafo NO dirigido: se agrega en ambas direcciones
    Vecino v1{ arista.getDestinoId(), arista.getId(), arista.getDistancia() };
    Vecino v2{ arista.getOrigenId(),  arista.getId(), arista.getDistancia() };

    adyacencia_[arista.getOrigenId()].push_back(v1);
    adyacencia_[arista.getDestinoId()].push_back(v2);
}

// ── Consultas básicas ─────────────────────────────────────────────────────────

const Nodo* Grafo::buscarNodo(int id) const {
    for (const auto& n : nodos_)
        if (n.getId() == id) return &n;
    return nullptr;
}

const Arista* Grafo::buscarArista(int id) const {
    for (const auto& a : aristas_)
        if (a.getId() == id) return &a;
    return nullptr;
}

std::vector<Vecino> Grafo::getVecinos(int nodoId, bool movilidadReducida) const {
    std::vector<Vecino> resultado;

    auto it = adyacencia_.find(nodoId);
    if (it == adyacencia_.end()) return resultado;

    for (const Vecino& v : it->second) {
        // Verificar nodo destino bloqueado
        const Nodo* destino = buscarNodo(v.nodoId);
        if (destino && destino->isBloqueado()) continue;

        // Verificar arista bloqueada o inaccesible
        const Arista* arista = buscarArista(v.aristaId);
        if (!arista) continue;

        double peso = arista->getPesoEfectivo(movilidadReducida);
        if (peso < 0.0) continue; // Ruta no disponible

        Vecino ve = v;
        ve.distancia = peso; // Usa el peso efectivo
        resultado.push_back(ve);
    }
    return resultado;
}

// ── Bloqueos ──────────────────────────────────────────────────────────────────

void Grafo::bloquearNodo(int id, bool b) {
    for (auto& n : nodos_)
        if (n.getId() == id) { n.setBloqueado(b); return; }
}

void Grafo::bloquearArista(int id, bool b) {
    for (auto& a : aristas_)
        if (a.getId() == id) { a.setBloqueada(b); return; }
}

void Grafo::limpiarBloqueos() {
    for (auto& n : nodos_)  n.setBloqueado(false);
    for (auto& a : aristas_) a.setBloqueada(false);
}

// ── Limpieza ──────────────────────────────────────────────────────────────────

void Grafo::limpiar() {
    nodos_.clear();
    aristas_.clear();
    adyacencia_.clear();
}

void Grafo::reconstruirAdyacencia() {
    adyacencia_.clear();
    for (const auto& n : nodos_)
        adyacencia_[n.getId()] = {};
    for (const auto& a : aristas_) {
        Vecino v1{ a.getDestinoId(), a.getId(), a.getDistancia() };
        Vecino v2{ a.getOrigenId(),  a.getId(), a.getDistancia() };
        adyacencia_[a.getOrigenId()].push_back(v1);
        adyacencia_[a.getDestinoId()].push_back(v2);
    }
}