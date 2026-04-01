#pragma once
#include "Nodo.h"
#include "arista.h"
#include <vector>
#include <unordered_map>
#include <optional>

// entrada en la lista de adyacencia
struct Vecino {
	int nodoId;
	int aristaId;
	double distancia; // distancia = peso
};

class Grafo {
public:
	// construccion 
	void agregarNodo(const Nodo& nodo);
	void agregarArista(const Arista& arista);

	// consultas basicas
	const std::vector<Nodo>& getNodos() const { return nodos_; }
	const std::vector<Arista>& getaristas() const { return aristas_; }

	// retoma nullptr si no exista
	const Nodo* buscarNodo(int id) const;
	const Arista* buscarArista(int id) const;

	// vecinos de un nodo, con peso ajustado para movilidad reducida
	std::vector<Vecino> getVecinos(int nodoId, bool movilidadReducida = false) const;

	int cantidadNodos()   const { return static_cast<int>(nodos_.size()); }
	int cantidadAristas() const { return static_cast<int>(aristas_.size()); }

	// bloqueos
	void bloquearNodo(int id, bool b);
	void bloquearArista(int id, bool b);
	void limpiarBloqueos(); // respeta todos los bloqueos


	// limpieza
	void limpiar();

private:
	std::vector<Nodo> nodos_;
	std::vector<Arista> aristas_;

	// Para acceso rápido a vecinos: nodoId -> lista de (nodoVecinoId, aristaId, distancia)
	std::unordered_map<int, std::vector<Vecino>> adyacencia_;

	void reconstruirAdyacencia();
};
