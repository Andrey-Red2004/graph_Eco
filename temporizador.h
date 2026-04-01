#pragma once
#include <chrono>

// Utilidad simple de cronómetro para el módulo de análisis de complejidad
class Temporizador {
public:
    void iniciar() {
        inicio_ = std::chrono::high_resolution_clock::now();
    }

    long long microsegundos() const {
        auto fin = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio_).count();
    }

    long long milisegundos() const {
        return microsegundos() / 1000;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> inicio_;
};