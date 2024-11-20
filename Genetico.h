#ifndef GENETICO_H
#define GENETICO_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include "AGreedy2.h"
#include "sexo.h"
#include "Funciones.h"
#pragma once

/**
 * @brief Clase que implementa un algoritmo genético para maximizar la calidad de soluciones generadas.
 */
class Genetico {
private:
    // Variables miembro privadas
    float thr = 0.8;                           ///< Umbral para determinar diferencias
    int alpha = 0.01;                        ///< Probabilidad de mutación
    int maxTime;                             ///< Tiempo máximo permitido para la ejecución
    int solQuality = 0;                      ///< Calidad de la mejor solución encontrada
    Sexo cama;                               ///< Clase que gestiona el cruce genético
    std::string bestSol;                     ///< Mejor solución generada
    std::vector<std::string> cadenasOriginales; ///< Cadenas originales leídas del archivo
    std::vector<std::string> cadenas100;    ///< Población actual de soluciones
    std::vector<std::string> cadenas150;    ///< Población expandida tras procreación
    std::vector<int> valores100;            ///< Calidad de las soluciones en `cadenas100`
    std::vector<int> valores150;            ///< Calidad de las soluciones en `cadenas150`
    std::chrono::system_clock::time_point startTime; ///< Tiempo de inicio del algoritmo
    std::chrono::system_clock::time_point bestTime = std::chrono::system_clock::time_point::min(); ///< Tiempo de la mejor solución
    std::mt19937 gen;                        ///< Generador de números aleatorios

    // Métodos privados
    void procreador();                       ///< Realiza la combinación de soluciones para generar nuevas
    void matador();                          ///< Selecciona las mejores soluciones y elimina las peores
    bool checkTime();                        ///< Verifica si el tiempo máximo ha sido alcanzado
    void genetizar();                        ///< Realiza iteraciones del algoritmo genético

public:
    /**
     * @brief Constructor de la clase Genetico.
     * @param ifp Ruta del archivo de entrada.
     * @param maxTime Tiempo máximo para la ejecución del algoritmo.
     * @param cadenas100 Población inicial de soluciones.
     */
    Genetico(const std::string& ifp, int maxTime, std::vector<std::string> cadenas100);

    /**
     * @brief Obtiene la calidad final de la mejor solución encontrada.
     * @return Calidad de la mejor solución.
     */
    float getFinalQuality();

    /**
     * @brief Obtiene el tiempo en el que se encontró la mejor solución.
     * @return Tiempo transcurrido desde el inicio hasta la mejor solución.
     */
    double getFinalTime();
};

#endif // GENETICO_H
