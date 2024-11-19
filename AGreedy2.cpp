#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include "Funciones.cpp"

/**
 * @brief Clase que implementa un algoritmo heurístico basado en un enfoque codicioso y probabilístico
 *        para encontrar una cadena que maximice la disimilitud con otras cadenas en un archivo.
 */
class AGreedy2{
    private:
    std::string ifp;
    float alpha, calidad;
    std::vector<std::string> datos;
    std::vector<char> caracteresFrecuentes;
    std::chrono::duration<double> elapsed;

    /**
     * @brief Calcula la frecuencia de cada carácter en todas las líneas y devuelve los caracteres ordenados por frecuencia.
     * @return Un vector con los caracteres ordenados de mayor a menor frecuencia.
     */
    std::vector<char> obtenerCaracteresFrecuentes() {
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

    /**
     * @brief Ejecuta el algoritmo para generar una cadena que maximice la disimilitud.
     * @return La cadena seleccionada por el algoritmo.
     */
    std::string ejecutar() {  
        if (datos.empty()) {
            std::cerr << "No hay datos para procesar." << std::endl;
            return "";
        }       
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
            double p = static_cast<double>(rand()) / RAND_MAX;
            if (p < alpha) {
                std::vector<char> caracteresPosibles;
                for (const auto& par : frecuenciaPosicion) {
                    if (par.first != caracterMenosFrecuente) {
                        caracteresPosibles.push_back(par.first);
                    }
                }
                if (!caracteresPosibles.empty()) {
                    seleccionada[i] = caracteresPosibles[rand() % caracteresPosibles.size()];
                } else {
                    seleccionada[i] = caracterMenosFrecuente;
                }
            } else {
                seleccionada[i] = caracterMenosFrecuente;
            }
        }
        return seleccionada;
    }

    public:

    /**
     * @brief Constructor de la clase AGreedy2.
     * @param ifp Ruta del archivo de entrada.
     * @param thr Umbral de similitud.
     * @param alpha Parámetro probabilístico para la selección de caracteres.
     */
    AGreedy2(const std::string& ifp, float alpha)
    : ifp(ifp), alpha(alpha) {
        datos = leerArchivo(ifp);
        caracteresFrecuentes = obtenerCaracteresFrecuentes();
        srand(static_cast<unsigned>(time(0)));
    }

    /**
     * @brief Genera una solución utilizando el algoritmo y la devuelve.
     * @return La solución generada por el algoritmo.
     */
    std::string generarSolucion(){
        std::string seleccionada = ejecutar();
        return seleccionada;
    }
};