#include "CampusController.h"
#include <iostream>

// Inicializacion

bool CampusController::inicializar(const std::string& dirDatos) {
    dirDatos_ = dirDatos;

    std::string rutaNodos = dirDatos + "/nodos.json";
    std::string rutaAristas = dirDatos + "/aristas.json";
    std::string rutaBloqueos = dirDatos + "/bloqueos.json";

    if (!FileManager::cargarGrafo(grafo_, rutaNodos, rutaAristas)) {
        std::cerr << "[Controller] Error cargando grafo.\n";
        return false;
    }

    // Los bloqueos son opcionales; si el archivo no existe, no es un error
    FileManager::cargarBloqueos(grafo_, rutaBloqueos);

    std::cout << "[Controller] Inicializado. Nodos: "
        << grafo_.cantidadNodos()
        << ", Aristas: " << grafo_.cantidadAristas() << "\n";
    return true;
}

// Modulos

ResultadoRecorrido CampusController::recorridoDFS(int inicioId) const {
    return AlgoritmosGrafo::dfs(grafo_, inicioId, movilidadReducida());
}

ResultadoRecorrido CampusController::recorridoBFS(int inicioId) const {
    return AlgoritmosGrafo::bfs(grafo_, inicioId, movilidadReducida());
}

bool CampusController::esCampusConexo() const {
    return AlgoritmosGrafo::esCampusConexo(grafo_, movilidadReducida());
}

ResultadoCamino CampusController::buscarCamino(int origenId, int destinoId) const {
    return AlgoritmosGrafo::buscarCaminoDFS(grafo_, origenId, destinoId,
        movilidadReducida());
}

ResultadoDijkstra CampusController::calcularRuta(int origenId, int destinoId) const {
    if (perfil_ == PerfilUsuario::EstudianteNuevo) {
        return AlgoritmosGrafo::rutaEstudianteNuevo(grafo_, origenId, destinoId,
            puntosRef_,
            movilidadReducida());
    }
    // EstudianteRegular y MovilidadReducida → Dijkstra directo
    // (MovilidadReducida ya está manejado dentro de dijkstra vía movilidadReducida())
    return AlgoritmosGrafo::dijkstra(grafo_, origenId, destinoId,
        movilidadReducida());
}

AnalisisComparativo CampusController::analizarComplejidad(int origenId,
    int destinoId) const {
    return AlgoritmosGrafo::compararBfsDfs(grafo_, origenId, destinoId,
        movilidadReducida());
}

// Bloqueos
void CampusController::bloquearNodo(int id, bool bloqueado) {
    grafo_.bloquearNodo(id, bloqueado);
}

void CampusController::bloquearArista(int id, bool bloqueado) {
    grafo_.bloquearArista(id, bloqueado);
}

void CampusController::limpiarBloqueos() {
    grafo_.limpiarBloqueos();
}

bool CampusController::guardarBloqueos() const {
    return FileManager::guardarBloqueos(grafo_,
        dirDatos_ + "/bloqueos.json");
}