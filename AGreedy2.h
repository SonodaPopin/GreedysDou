#ifndef AGREEDY2_H
#define AGREEDY2_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <unordered_map>
#pragma once

/**
 * @brief Clase que implementa un algoritmo heurístico basado en un enfoque codicioso y probabilístico
 *        para encontrar una cadena que maximice la disimilitud con otras cadenas en un archivo.
 */
class AGreedy2 {
private:
    // Variables miembro privadas
    std::string ifp;                          ///< Ruta del archivo de entrada
    float alpha;                              ///< Parámetro probabilístico para la selección de caracteres
    float calidad;                            ///< Calidad de la solución generada
    std::vector<char> caracteresFrecuentes;   ///< Lista de caracteres ordenados por frecuencia
    std::chrono::duration<double> elapsed;    ///< Tiempo transcurrido durante la ejecución
    std::mt19937 gen;                         ///< Generador de números aleatorios

    /**
     * @brief Calcula la frecuencia de cada carácter en todas las líneas y devuelve los caracteres ordenados por frecuencia.
     * @return Un vector con los caracteres ordenados de mayor a menor frecuencia.
     */
    std::vector<char> obtenerCaracteresFrecuentes();

    /**
     * @brief Ejecuta el algoritmo para generar una cadena que maximice la disimilitud.
     * @return La cadena seleccionada por el algoritmo.
     */
    std::string ejecutar();

public:
    // Variables miembro públicas
    std::vector<std::string> datos;           ///< Contenedor con las líneas del archivo de entrada

    /**
     * @brief Constructor de la clase AGreedy2.
     * @param ifp Ruta del archivo de entrada.
     * @param alpha Parámetro probabilístico para la selección de caracteres.
     */
    AGreedy2(const std::string& ifp, float alpha);

    /**
     * @brief Genera una solución utilizando el algoritmo y la devuelve.
     * @return Un vector con las soluciones generadas por el algoritmo.
     */
    std::vector<std::string> generarSolucion();
};

#endif // AGREEDY2_H