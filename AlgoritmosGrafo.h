#pragma once
#include "grafo.h"
#include <vector>
#include <string>
#include <limits>
#include <unordered_map>

// ── Resultado de un recorrido DFS o BFS ──────────────────────────────────────
struct ResultadoRecorrido {
    std::vector<int>    ordenVisita;       // IDs de nodos en orden de visita
    std::vector<double> distanciasAcum;   // Distancia acumulada en cada paso
    int                 nodosVisitados = 0;
    long long           tiempoMicros = 0; // Tiempo de ejecución en µs
};

// ── Resultado de búsqueda de camino ──────────────────────────────────────────
struct ResultadoCamino {
    bool              encontrado = false;
    std::vector<int>  camino;             // IDs de nodos del camino
    double            distanciaTotal = 0.0;
    int               nodosVisitados = 0;
    long long         tiempoMicros = 0;
};

// ── Resultado de Dijkstra ─────────────────────────────────────────────────────
struct ResultadoDijkstra {
    bool              encontrado = false;
    std::vector<int>  camino;
    double            distanciaTotal = 0.0;
    long long         tiempoMicros = 0;
};

// ── Análisis comparativo BFS vs DFS ──────────────────────────────────────────
struct AnalisisComparativo {
    ResultadoCamino bfs;
    ResultadoCamino dfs;
    std::string     ganadorNodos;   // "BFS" o "DFS" (quien visitó menos)
    std::string     ganadorTiempo;  // "BFS" o "DFS" (quien fue más rápido)
};

// ─────────────────────────────────────────────────────────────────────────────
//  Clase principal de algoritmos (sin estado propio, todo recibe el grafo)
// ─────────────────────────────────────────────────────────────────────────────
class AlgoritmosGrafo {
public:
    // Recorrido DFS completo desde un nodo inicio
    static ResultadoRecorrido dfs(const Grafo& g, int inicioId,
        bool movilidadReducida = false);

    // Recorrido BFS completo desde un nodo inicio
    static ResultadoRecorrido bfs(const Grafo& g, int inicioId,
        bool movilidadReducida = false);

    // Busca camino entre dos nodos usando DFS (módulo 5 del enunciado)
    static ResultadoCamino buscarCaminoDFS(const Grafo& g,
        int origenId, int destinoId,
        bool movilidadReducida = false);

    // Ruta más corta: Dijkstra (para el perfil "veterano")
    static ResultadoDijkstra dijkstra(const Grafo& g,
        int origenId, int destinoId,
        bool movilidadReducida = false);

    // Ruta para "estudiante nuevo": pasa obligatoriamente por puntos de referencia
    // puntosRef: IDs de nodos que deben visitarse (ej. biblioteca, soda)
    static ResultadoDijkstra rutaEstudianteNuevo(const Grafo& g,
        int origenId, int destinoId,
        const std::vector<int>& puntosRef,
        bool movilidadReducida = false);

    // Verifica si el grafo es completamente conexo (módulo 4)
    static bool esCampusConexo(const Grafo& g, bool movilidadReducida = false);

    // Análisis comparativo BFS vs DFS para el módulo 7
    static AnalisisComparativo compararBfsDfs(const Grafo& g,
        int origenId, int destinoId,
        bool movilidadReducida = false);

private:
    // Auxiliares internas
    static void dfsRecursivo(const Grafo& g, int nodoId,
        std::vector<bool>& visitado,
        ResultadoRecorrido& res,
        double distAcum,
        bool movilidadReducida);

    static bool dfsBuscarCamino(const Grafo& g, int actual, int destino,
        std::unordered_map<int, bool>& visitado,
        std::vector<int>& caminoActual,
        double& distAcum, int& nodosVisitados,
        bool movilidadReducida);
};
