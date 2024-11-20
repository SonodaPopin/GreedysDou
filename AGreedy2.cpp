#include "AGreedy2.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <random>
#include "Funciones.h"

// Implementación de los métodos privados

std::vector<char> AGreedy2::obtenerCaracteresFrecuentes() {
    std::unordered_map<char, int> frecuencia;
    for (const std::string& linea : datos) {
        for (char caracter : linea) {
            frecuencia[caracter]++;
        }
    }
    std::vector<std::pair<char, int>> frecuenciaVector(frecuencia.begin(), frecuencia.end());
    std::sort(frecuenciaVector.begin(), frecuenciaVector.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    for (const auto& par : frecuenciaVector) {
        caracteresFrecuentes.push_back(par.first);
    }
    return caracteresFrecuentes;
}

std::string AGreedy2::ejecutar() {
    if (datos.empty()) {
        std::cerr << "No hay datos para procesar." << std::endl;
        return "";
    }
    std::uniform_real_distribution<> probDist(0.0, 1.0);
    std::uniform_int_distribution<> indexDist;
    size_t longitudLinea = datos[0].length();
    std::string seleccionada(longitudLinea, ' ');

    for (size_t i = 0; i < longitudLinea; ++i) {
        std::unordered_map<char, int> frecuenciaPosicion;
        for (const std::string& linea : datos) {
            frecuenciaPosicion[linea[i]]++;
        }
        char caracterMenosFrecuente = std::min_element(
            frecuenciaPosicion.begin(), frecuenciaPosicion.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; }
        )->first;

        double p = probDist(gen);
        if (p < alpha) {
            std::vector<char> caracteresPosibles;
            for (const auto& par : frecuenciaPosicion) {
                if (par.first != caracterMenosFrecuente) {
                    caracteresPosibles.push_back(par.first);
                }
            }
            if (!caracteresPosibles.empty()) {
                indexDist = std::uniform_int_distribution<>(0, caracteresPosibles.size() - 1);
                seleccionada[i] = caracteresPosibles[indexDist(gen)];
            } else {
                seleccionada[i] = caracterMenosFrecuente;
            }
        } else {
            seleccionada[i] = caracterMenosFrecuente;
        }
    }
    return seleccionada;
}

// Implementación de los métodos públicos

AGreedy2::AGreedy2(const std::string& ifp, float alpha)
    : ifp(ifp), alpha(alpha), gen(std::random_device{}()) {
    datos = leerArchivo(ifp);
    caracteresFrecuentes = obtenerCaracteresFrecuentes();
    srand(static_cast<unsigned>(time(0)));
}

std::vector<std::string> AGreedy2::generarSolucion() {
    std::vector<std::string> sols;
    sols.resize(100);
    for (int i = 0; i < 100; i++) {
        gen.seed(std::random_device{}());
        sols[i] = ejecutar();
        int calidad = contarDiferencias(sols[i], datos, 0.8);
    }
    return sols;
}
