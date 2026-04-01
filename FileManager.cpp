#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <stdexcept>

//  Utilidades privadas

std::string FileManager::leerArchivo(const std::string& ruta) {
    std::ifstream f(ruta);
    if (!f.is_open()) {
        std::cerr << "[FileManager] No se pudo abrir: " << ruta << "\n";
        return "";
    }
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

// Extrae el valor string de  "clave": "valor"
std::string FileManager::extraerValor(const std::string& bloque,
    const std::string& clave) {
    std::string patron = "\"" + clave + "\"\\s*:\\s*\"([^\"]*)\"";
    std::regex  re(patron);
    std::smatch m;
    if (std::regex_search(bloque, m, re)) return m[1].str();
    return "";
}

// Extrae el valor entero de  "clave": 123
int FileManager::extraerInt(const std::string& bloque,
    const std::string& clave) {
    std::string patron = "\"" + clave + "\"\\s*:\\s*(-?\\d+)";
    std::regex  re(patron);
    std::smatch m;
    if (std::regex_search(bloque, m, re)) return std::stoi(m[1].str());
    return -1;
}

// Extrae el valor double de  "clave": 123.45
double FileManager::extraerDouble(const std::string& bloque,
    const std::string& clave) {
    std::string patron = "\"" + clave + "\"\\s*:\\s*(-?[\\d.]+)";
    std::regex  re(patron);
    std::smatch m;
    if (std::regex_search(bloque, m, re)) return std::stod(m[1].str());
    return 0.0;
}


//  Parsear nodos.json

bool FileManager::parsearNodos(Grafo& grafo, const std::string& ruta) {
    std::string contenido = leerArchivo(ruta);
    if (contenido.empty()) return false;

    // Dividir por objetos { ... }
    std::regex objRe("\\{([^}]+)\\}");
    auto inicio = std::sregex_iterator(contenido.begin(), contenido.end(), objRe);
    auto fin = std::sregex_iterator();

    for (auto it = inicio; it != fin; ++it) {
        std::string bloque = (*it)[1].str();

        int         id = extraerInt(bloque, "id");
        std::string nombre = extraerValor(bloque, "nombre");
        std::string tipo = extraerValor(bloque, "tipo");
        double      posX = extraerDouble(bloque, "posX");
        double      posY = extraerDouble(bloque, "posY");

        if (id < 0) {
            std::cerr << "[FileManager] Nodo con id inválido ignorado.\n";
            continue;
        }

        Nodo n(id, nombre, stringToTipoNodo(tipo), posX, posY);
        grafo.agregarNodo(n);
    }
    return true;
}

//  Parsear aristas.json
bool FileManager::parsearAristas(Grafo& grafo, const std::string& ruta) {
    std::string contenido = leerArchivo(ruta);
    if (contenido.empty()) return false;

    std::regex objRe("\\{([^}]+)\\}");
    auto inicio = std::sregex_iterator(contenido.begin(), contenido.end(), objRe);
    auto fin = std::sregex_iterator();

    for (auto it = inicio; it != fin; ++it) {
        std::string bloque = (*it)[1].str();

        int    id = extraerInt(bloque, "id");
        int    origen = extraerInt(bloque, "origen");
        int    destino = extraerInt(bloque, "destino");
        double distancia = extraerDouble(bloque, "distancia");
        std::string acceso = extraerValor(bloque, "acceso");

        if (id < 0 || origen < 0 || destino < 0) {
            std::cerr << "[FileManager] Arista con campos inválidos ignorada.\n";
            continue;
        }

        Arista a(id, origen, destino, distancia, stringToTipoAcceso(acceso));
        grafo.agregarArista(a);
    }
    return true;
}

//  API pública
bool FileManager::cargarGrafo(Grafo& grafo,
    const std::string& rutaNodos,
    const std::string& rutaAristas) {
    grafo.limpiar();
    bool ok1 = parsearNodos(grafo, rutaNodos);
    bool ok2 = parsearAristas(grafo, rutaAristas);

    if (ok1 && ok2)
        std::cout << "[FileManager] Grafo cargado: "
        << grafo.cantidadNodos() << " nodos, "
        << grafo.cantidadAristas() << " aristas.\n";
    return ok1 && ok2;
}

bool FileManager::guardarBloqueos(const Grafo& grafo,
    const std::string& rutaBloqueos) {
    std::ofstream f(rutaBloqueos);
    if (!f.is_open()) {
        std::cerr << "[FileManager] No se pudo escribir: " << rutaBloqueos << "\n";
        return false;
    }

    f << "{\n";
    f << "  \"nodosBloqueados\": [";
    bool primero = true;
    for (const auto& n : grafo.getNodos()) {
        if (n.isBloqueado()) {
            if (!primero) f << ", ";
            f << n.getId();
            primero = false;
        }
    }
    f << "],\n";

    f << "  \"aristasBloqueadas\": [";
    primero = true;
    for (const auto& a : grafo.getaristas()) {
        if (a.isBloqueada()) {
            if (!primero) f << ", ";
            f << a.getId();
            primero = false;
        }
    }
    f << "]\n}\n";

    return true;
}

bool FileManager::cargarBloqueos(Grafo& grafo,
    const std::string& rutaBloqueos) {
    std::string contenido = leerArchivo(rutaBloqueos);
    if (contenido.empty()) return false;

    // Extraer array de nodos bloqueados
    std::regex arrNodos("\"nodosBloqueados\"\\s*:\\s*\\[([^\\]]*)\\]");
    std::smatch mN;
    if (std::regex_search(contenido, mN, arrNodos)) {
        std::string arr = mN[1].str();
        std::regex num("\\d+");
        auto it = std::sregex_iterator(arr.begin(), arr.end(), num);
        for (; it != std::sregex_iterator(); ++it)
            grafo.bloquearNodo(std::stoi((*it)[0].str()), true);
    }

    // Extraer array de aristas bloqueadas
    std::regex arrAristas("\"aristasBloqueadas\"\\s*:\\s*\\[([^\\]]*)\\]");
    std::smatch mA;
    if (std::regex_search(contenido, mA, arrAristas)) {
        std::string arr = mA[1].str();
        std::regex num("\\d+");
        auto it = std::sregex_iterator(arr.begin(), arr.end(), num);
        for (; it != std::sregex_iterator(); ++it)
            grafo.bloquearArista(std::stoi((*it)[0].str()), true);
    }

    return true;
}