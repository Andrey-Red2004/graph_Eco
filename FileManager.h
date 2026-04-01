#pragma once
#include "grafo.h"
#include <string>

// FileManager: capa de persistencia
// Lee y escribe los archivos JSON del campus usando parsing manual
// (sin dependencias externas: no nlohmann/json, solo STL)
class FileManager {
public:
    // Carga nodos y aristas en el grafo dado; retorna true si tuvo éxito
    static bool cargarGrafo(Grafo& grafo,
        const std::string& rutaNodos,
        const std::string& rutaAristas);

    // Guarda el estado actual de bloqueos
    static bool guardarBloqueos(const Grafo& grafo,
        const std::string& rutaBloqueos);

    // Carga bloqueos y los aplica al grafo
    static bool cargarBloqueos(Grafo& grafo,
        const std::string& rutaBloqueos);

private:
    // Parsers manuales de JSON minimalista (arrays de objetos planos)
    static bool parsearNodos(Grafo& grafo, const std::string& ruta);
    static bool parsearAristas(Grafo& grafo, const std::string& ruta);

    // Utilidades de string
    static std::string leerArchivo(const std::string& ruta);
    static std::string extraerValor(const std::string& json,
        const std::string& clave);
    static int         extraerInt(const std::string& json,
        const std::string& clave);
    static double      extraerDouble(const std::string& json,
        const std::string& clave);
};