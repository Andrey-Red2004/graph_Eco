#include "AlgoritmosGrafo.h"
#include <queue>
#include <stack>
#include <chrono>
#include <algorithm>
#include <limits>

using namespace std::chrono;

//  Helpers para medir tiempo
static auto ahora() { return high_resolution_clock::now(); }
static long long microsegundos(time_point<high_resolution_clock> inicio) {
    return duration_cast<microseconds>(ahora() - inicio).count();
}

// Construye un mapa id→índice para los vectores de visitado
static std::unordered_map<int, int> construirIndices(const Grafo& g) {
    std::unordered_map<int, int> idx;
    int i = 0;
    for (const auto& n : g.getNodos()) idx[n.getId()] = i++;
    return idx;
}

//  DFS completo
ResultadoRecorrido AlgoritmosGrafo::dfs(const Grafo& g, int inicioId,
    bool movilidadReducida) {
    ResultadoRecorrido res;
    auto t0 = ahora();

    auto indices = construirIndices(g);
    std::vector<bool> visitado(g.cantidadNodos(), false);

    dfsRecursivo(g, inicioId, visitado, res, 0.0, movilidadReducida);

    res.nodosVisitados = static_cast<int>(res.ordenVisita.size());
    res.tiempoMicros = microsegundos(t0);
    return res;
}

void AlgoritmosGrafo::dfsRecursivo(const Grafo& g, int nodoId,
    std::vector<bool>& visitado,
    ResultadoRecorrido& res,
    double distAcum,
    bool movilidadReducida) {
    // Marca por ID: busca la posición en el vector
    int pos = -1;
    const auto& nodos = g.getNodos();
    for (int i = 0; i < (int)nodos.size(); ++i)
        if (nodos[i].getId() == nodoId) { pos = i; break; }

    if (pos == -1 || visitado[pos]) return;
    visitado[pos] = true;

    // Verificar si el nodo mismo está bloqueado
    const Nodo* n = g.buscarNodo(nodoId);
    if (!n || n->isBloqueado()) return;

    res.ordenVisita.push_back(nodoId);
    res.distanciasAcum.push_back(distAcum);

    for (const Vecino& v : g.getVecinos(nodoId, movilidadReducida))
        dfsRecursivo(g, v.nodoId, visitado, res,
            distAcum + v.distancia, movilidadReducida);
}

//  BFS completo
ResultadoRecorrido AlgoritmosGrafo::bfs(const Grafo& g, int inicioId,
    bool movilidadReducida) {
    ResultadoRecorrido res;
    auto t0 = ahora();

    // Mapa de distancias acumuladas por nodoId
    std::unordered_map<int, double> distAcum;
    std::unordered_map<int, bool>   visitado;

    for (const auto& n : g.getNodos()) {
        distAcum[n.getId()] = std::numeric_limits<double>::infinity();
        visitado[n.getId()] = false;
    }

    const Nodo* inicio = g.buscarNodo(inicioId);
    if (!inicio || inicio->isBloqueado()) {
        res.tiempoMicros = microsegundos(t0);
        return res;
    }

    std::queue<int> cola;
    cola.push(inicioId);
    visitado[inicioId] = true;
    distAcum[inicioId] = 0.0;

    while (!cola.empty()) {
        int actual = cola.front(); cola.pop();

        res.ordenVisita.push_back(actual);
        res.distanciasAcum.push_back(distAcum[actual]);

        for (const Vecino& v : g.getVecinos(actual, movilidadReducida)) {
            if (!visitado[v.nodoId]) {
                visitado[v.nodoId] = true;
                distAcum[v.nodoId] = distAcum[actual] + v.distancia;
                cola.push(v.nodoId);
            }
        }
    }

    res.nodosVisitados = static_cast<int>(res.ordenVisita.size());
    res.tiempoMicros = microsegundos(t0);
    return res;
}

//  Buscar camino DFS (módulo 5)
ResultadoCamino AlgoritmosGrafo::buscarCaminoDFS(const Grafo& g,
    int origenId, int destinoId,
    bool movilidadReducida) {
    ResultadoCamino res;
    auto t0 = ahora();

    std::unordered_map<int, bool> visitado;
    for (const auto& n : g.getNodos()) visitado[n.getId()] = false;

    std::vector<int> caminoActual;
    double distAcum = 0.0;

    res.encontrado = dfsBuscarCamino(g, origenId, destinoId, visitado,
        caminoActual, distAcum,
        res.nodosVisitados, movilidadReducida);
    if (res.encontrado) {
        res.camino = caminoActual;
        res.distanciaTotal = distAcum;
    }
    res.tiempoMicros = microsegundos(t0);
    return res;
}

bool AlgoritmosGrafo::dfsBuscarCamino(const Grafo& g, int actual, int destino,
    std::unordered_map<int, bool>& visitado,
    std::vector<int>& caminoActual,
    double& distAcum, int& nodosVisitados,
    bool movilidadReducida) {
    const Nodo* n = g.buscarNodo(actual);
    if (!n || n->isBloqueado()) return false;

    visitado[actual] = true;
    caminoActual.push_back(actual);
    nodosVisitados++;

    if (actual == destino) return true;

    for (const Vecino& v : g.getVecinos(actual, movilidadReducida)) {
        if (!visitado[v.nodoId]) {
            double prevDist = distAcum;
            distAcum += v.distancia;

            if (dfsBuscarCamino(g, v.nodoId, destino, visitado,
                caminoActual, distAcum,
                nodosVisitados, movilidadReducida))
                return true;

            distAcum = prevDist; // Backtrack
        }
    }

    caminoActual.pop_back(); // Backtrack
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Dijkstra
// ─────────────────────────────────────────────────────────────────────────────
ResultadoDijkstra AlgoritmosGrafo::dijkstra(const Grafo& g,
    int origenId, int destinoId,
    bool movilidadReducida) {
    ResultadoDijkstra res;
    auto t0 = ahora();

    const double INF = std::numeric_limits<double>::infinity();

    std::unordered_map<int, double> dist;
    std::unordered_map<int, int>    padre;

    for (const auto& n : g.getNodos()) {
        dist[n.getId()] = INF;
        padre[n.getId()] = -1;
    }
    dist[origenId] = 0.0;

    // Min-heap: {distancia, nodoId}
    using Par = std::pair<double, int>;
    std::priority_queue<Par, std::vector<Par>, std::greater<Par>> pq;
    pq.push({ 0.0, origenId });

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        if (d > dist[u]) continue; // Entrada obsoleta
        if (u == destinoId) break;

        for (const Vecino& v : g.getVecinos(u, movilidadReducida)) {
            double nueva = dist[u] + v.distancia;
            if (nueva < dist[v.nodoId]) {
                dist[v.nodoId] = nueva;
                padre[v.nodoId] = u;
                pq.push({ nueva, v.nodoId });
            }
        }
    }

    if (dist[destinoId] < INF) {
        res.encontrado = true;
        res.distanciaTotal = dist[destinoId];
        // Reconstruir camino
        int cur = destinoId;
        while (cur != -1) {
            res.camino.push_back(cur);
            cur = padre[cur];
        }
        std::reverse(res.camino.begin(), res.camino.end());
    }

    res.tiempoMicros = microsegundos(t0);
    return res;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Ruta estudiante nuevo (pasa por puntos de referencia)
//  Estrategia: Dijkstra en cadena  origen→ref1→ref2→...→destino
// ─────────────────────────────────────────────────────────────────────────────
ResultadoDijkstra AlgoritmosGrafo::rutaEstudianteNuevo(const Grafo& g,
    int origenId,
    int destinoId,
    const std::vector<int>& puntosRef,
    bool movilidadReducida) {
    ResultadoDijkstra total;
    total.encontrado = true;

    auto t0 = ahora();

    // Construir la secuencia de waypoints
    std::vector<int> waypoints;
    waypoints.push_back(origenId);
    for (int r : puntosRef) waypoints.push_back(r);
    waypoints.push_back(destinoId);

    for (int i = 0; i + 1 < (int)waypoints.size(); ++i) {
        auto seg = dijkstra(g, waypoints[i], waypoints[i + 1], movilidadReducida);
        if (!seg.encontrado) {
            total.encontrado = false;
            break;
        }
        // Unir caminos (evitar duplicar el nodo de unión)
        if (!total.camino.empty()) seg.camino.erase(seg.camino.begin());
        for (int n : seg.camino) total.camino.push_back(n);
        total.distanciaTotal += seg.distanciaTotal;
    }

    total.tiempoMicros = microsegundos(t0);
    return total;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Verificar si el campus es completamente conexo
// ─────────────────────────────────────────────────────────────────────────────
bool AlgoritmosGrafo::esCampusConexo(const Grafo& g, bool movilidadReducida) {
    if (g.cantidadNodos() == 0) return true;

    // BFS desde el primer nodo no bloqueado
    int inicio = -1;
    for (const auto& n : g.getNodos())
        if (!n.isBloqueado()) { inicio = n.getId(); break; }
    if (inicio == -1) return true; // Todos bloqueados

    std::unordered_map<int, bool> visitado;
    for (const auto& n : g.getNodos()) visitado[n.getId()] = false;

    std::queue<int> cola;
    cola.push(inicio);
    visitado[inicio] = true;

    while (!cola.empty()) {
        int actual = cola.front(); cola.pop();
        for (const Vecino& v : g.getVecinos(actual, movilidadReducida))
            if (!visitado[v.nodoId]) {
                visitado[v.nodoId] = true;
                cola.push(v.nodoId);
            }
    }

    // Verificar que todos los nodos no bloqueados fueron visitados
    for (const auto& n : g.getNodos())
        if (!n.isBloqueado() && !visitado[n.getId()])
            return false;

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Análisis comparativo BFS vs DFS (módulo 7)
// ─────────────────────────────────────────────────────────────────────────────
AnalisisComparativo AlgoritmosGrafo::compararBfsDfs(const Grafo& g,
    int origenId, int destinoId,
    bool movilidadReducida) {
    AnalisisComparativo a;
    a.dfs = buscarCaminoDFS(g, origenId, destinoId, movilidadReducida);

    // BFS también busca camino (adaptación simple: BFS hasta encontrar destino)
    {
        ResultadoCamino bfsRes;
        auto t0 = ahora();

        std::unordered_map<int, bool>   visitado;
        std::unordered_map<int, int>    padre;
        std::unordered_map<int, double> distAcum;
        for (const auto& n : g.getNodos()) {
            visitado[n.getId()] = false;
            padre[n.getId()] = -1;
            distAcum[n.getId()] = 0.0;
        }

        std::queue<int> cola;
        cola.push(origenId);
        visitado[origenId] = true;

        while (!cola.empty() && !bfsRes.encontrado) {
            int actual = cola.front(); cola.pop();
            bfsRes.nodosVisitados++;

            if (actual == destinoId) {
                bfsRes.encontrado = true;
                // Reconstruir camino
                int cur = destinoId;
                while (cur != -1) { bfsRes.camino.push_back(cur); cur = padre[cur]; }
                std::reverse(bfsRes.camino.begin(), bfsRes.camino.end());
                bfsRes.distanciaTotal = distAcum[destinoId];
                break;
            }
            for (const Vecino& v : g.getVecinos(actual, movilidadReducida)) {
                if (!visitado[v.nodoId]) {
                    visitado[v.nodoId] = true;
                    padre[v.nodoId] = actual;
                    distAcum[v.nodoId] = distAcum[actual] + v.distancia;
                    cola.push(v.nodoId);
                }
            }
        }
        bfsRes.tiempoMicros = duration_cast<microseconds>(ahora() - t0).count();
        a.bfs = bfsRes;
    }

    // Determinar ganadores
    a.ganadorNodos = (a.bfs.nodosVisitados <= a.dfs.nodosVisitados) ? "BFS" : "DFS";
    a.ganadorTiempo = (a.bfs.tiempoMicros <= a.dfs.tiempoMicros) ? "BFS" : "DFS";

    return a;
}