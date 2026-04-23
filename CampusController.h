#pragma once
#include "grafo.h"
#include "AlgoritmosGrafo.h"
#include "FileManager.h"
#include <string>
#include <vector>
#include <unordered_map>

// Perfil activo del usuario (afecta algoritmos y pesos)
enum class PerfilUsuario {
    EstudianteRegular,   // Prioriza ruta más corta (Dijkstra)
    EstudianteNuevo,     // Pasa por biblioteca y soda primero
    MovilidadReducida    // Evita gradas, pondera pendientes
};

// ─────────────────────────────────────────────────────────────────────────────
//  CampusController
//  La UI SOLO habla con esta clase. Nunca llama a Grafo o algoritmos directamente.
// ─────────────────────────────────────────────────────────────────────────────
class CampusController {
public:
    CampusController() = default;

    // ── Inicialización ────────────────────────────────────────────────────────
    bool inicializar(const std::string& dirDatos);
    void setPerfil(PerfilUsuario perfil) { perfil_ = perfil; }
    PerfilUsuario getPerfil() const { return perfil_; }

    // ── Acceso al grafo (solo lectura para la UI) ─────────────────────────────
    const Grafo& getGrafo() const;
    bool setMapaActivo(const std::string& mapaId);

    // ── Módulos del sistema ───────────────────────────────────────────────────

    // Módulo 2: DFS desde un punto
    ResultadoRecorrido recorridoDFS(int inicioId) const;

    // Módulo 3: BFS desde un punto
    ResultadoRecorrido recorridoBFS(int inicioId) const;

    // Módulo 4: ¿Es el campus conexo?
    bool esCampusConexo() const;

    // Módulo 5: Buscar camino entre dos puntos (DFS)
    ResultadoCamino buscarCamino(int origenId, int destinoId) const;

    // Módulo 6: Ruta según perfil activo
    // - EstudianteRegular → Dijkstra directo
    // - EstudianteNuevo   → pasa por biblioteca(id=2) y soda(id=4)
    // - MovilidadReducida → Dijkstra con pesos ajustados
    ResultadoDijkstra calcularRuta(int origenId, int destinoId) const;

    // Módulo 7: Análisis comparativo BFS vs DFS
    AnalisisComparativo analizarComplejidad(int origenId, int destinoId) const;

    // Módulo 8: Bloqueos
    void bloquearNodo(int id, bool bloqueado);
    void bloquearArista(int id, bool bloqueado);
    void limpiarBloqueos();
    bool guardarBloqueos() const;

    // Nodos de referencia para estudiante nuevo (pueden modificarse)
    void setPuntosReferencia(const std::vector<int>& ids) { puntosRef_ = ids; }
    const std::vector<int>& getPuntosReferencia() const { return puntosRef_; }

private:
    std::unordered_map<std::string, Grafo> grafos_;
    std::string    mapaActivo_ = "Universidad";
    PerfilUsuario  perfil_ = PerfilUsuario::EstudianteRegular;
    std::string    dirDatos_;
    std::vector<int> puntosRef_ = { 2, 4 }; // Biblioteca y Soda por defecto

    bool movilidadReducida() const {
        return perfil_ == PerfilUsuario::MovilidadReducida;
    }
};