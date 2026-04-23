#include "CampusController.h"
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <cctype>

// Inicializacion

namespace {
std::string normalizarId(const std::string& id) {
    std::string out = id;
    std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c) {
        if (std::isalnum(c)) return static_cast<char>(std::tolower(c));
        return '_';
    });
    return out;
}

std::string rutaPorMapa(const std::string& dir, const std::string& base,
    const std::string& mapaId) {
    if (mapaId == "Universidad")
        return dir + "/" + base + ".json";

    return dir + "/" + base + "_" + normalizarId(mapaId) + ".json";
}
}

bool CampusController::inicializar(const std::string& dirDatos) {
    dirDatos_ = dirDatos;
    grafos_.clear();

    const std::string rutaNodos = rutaPorMapa(dirDatos, "nodos", "Universidad");
    const std::string rutaAristas = rutaPorMapa(dirDatos, "aristas", "Universidad");
    const std::string rutaBloqueos = rutaPorMapa(dirDatos, "bloqueos", "Universidad");

    Grafo base;
    if (!FileManager::cargarGrafo(base, rutaNodos, rutaAristas)) {
        std::cerr << "[Controller] Error cargando grafo base.\n";
        return false;
    }

    FileManager::cargarBloqueos(base, rutaBloqueos);
    grafos_.emplace("Universidad", std::move(base));

    const std::vector<std::string> mapas = {
        "Piso 1", "Piso 2", "Piso 3", "Piso 4", "Piso 5", "Biblioteca", "Comedor"
    };

    for (const auto& mapa : mapas) {
        const std::string nodos = rutaPorMapa(dirDatos, "nodos", mapa);
        const std::string aristas = rutaPorMapa(dirDatos, "aristas", mapa);
        if (!std::filesystem::exists(nodos) || !std::filesystem::exists(aristas))
            continue;

        Grafo g;
        if (!FileManager::cargarGrafo(g, nodos, aristas))
            continue;

        const std::string bloqueos = rutaPorMapa(dirDatos, "bloqueos", mapa);
        FileManager::cargarBloqueos(g, bloqueos);
        grafos_.emplace(mapa, std::move(g));
    }

    mapaActivo_ = "Universidad";
    const auto& activo = getGrafo();
    std::cout << "[Controller] Inicializado. Nodos: "
        << activo.cantidadNodos()
        << ", Aristas: " << activo.cantidadAristas() << "\n";
    return true;
}

const Grafo& CampusController::getGrafo() const {
    auto it = grafos_.find(mapaActivo_);
    if (it != grafos_.end())
        return it->second;

    return grafos_.begin()->second;
}

bool CampusController::setMapaActivo(const std::string& mapaId) {
    if (grafos_.find(mapaId) == grafos_.end())
        return false;

    mapaActivo_ = mapaId;
    return true;
}

// Modulos

ResultadoRecorrido CampusController::recorridoDFS(int inicioId) const {
    return AlgoritmosGrafo::dfs(getGrafo(), inicioId, movilidadReducida());
}

ResultadoRecorrido CampusController::recorridoBFS(int inicioId) const {
    return AlgoritmosGrafo::bfs(getGrafo(), inicioId, movilidadReducida());
}

bool CampusController::esCampusConexo() const {
    return AlgoritmosGrafo::esCampusConexo(getGrafo(), movilidadReducida());
}

ResultadoCamino CampusController::buscarCamino(int origenId, int destinoId) const {
    return AlgoritmosGrafo::buscarCaminoDFS(getGrafo(), origenId, destinoId,
        movilidadReducida());
}

ResultadoDijkstra CampusController::calcularRuta(int origenId, int destinoId) const {
    if (perfil_ == PerfilUsuario::EstudianteNuevo) {
        return AlgoritmosGrafo::rutaEstudianteNuevo(getGrafo(), origenId, destinoId,
            puntosRef_,
            movilidadReducida());
    }
    // EstudianteRegular y MovilidadReducida → Dijkstra directo
    // (MovilidadReducida ya está manejado dentro de dijkstra vía movilidadReducida())
    return AlgoritmosGrafo::dijkstra(getGrafo(), origenId, destinoId,
        movilidadReducida());
}

AnalisisComparativo CampusController::analizarComplejidad(int origenId,
    int destinoId) const {
    return AlgoritmosGrafo::compararBfsDfs(getGrafo(), origenId, destinoId,
        movilidadReducida());
}

// Bloqueos
void CampusController::bloquearNodo(int id, bool bloqueado) {
    grafos_[mapaActivo_].bloquearNodo(id, bloqueado);
}

void CampusController::bloquearArista(int id, bool bloqueado) {
    grafos_[mapaActivo_].bloquearArista(id, bloqueado);
}

void CampusController::limpiarBloqueos() {
    grafos_[mapaActivo_].limpiarBloqueos();
}

bool CampusController::guardarBloqueos() const {
    const std::string ruta = rutaPorMapa(dirDatos_, "bloqueos", mapaActivo_);
    return FileManager::guardarBloqueos(getGrafo(), ruta);
}