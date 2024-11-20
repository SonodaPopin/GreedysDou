#ifndef SEXO_H
#define SEXO_H

#include <string>
#include <vector>
#pragma once

/**
 * @class Sexo
 * @brief Clase que genera un "hijo" genético a partir de dos padres, utilizando frecuencias de caracteres en un dataset.
 */
class Sexo {
private:
    std::string ifp;                         ///< Ruta del archivo de entrada.
    std::vector<std::string> dataset;        ///< Dataset con las cadenas para cálculo de frecuencias.

    /**
     * @brief Cuenta la frecuencia de un carácter específico en una posición dada dentro del dataset.
     * @param caracter El carácter cuya frecuencia se evalúa.
     * @param posicion La posición en la que se evalúa el carácter.
     * @return La frecuencia del carácter en la posición especificada.
     */
    int contarFrecuencia(char caracter, int posicion);

public:
    /**
     * @brief Constructor que inicializa la clase leyendo un archivo de entrada.
     * @param archivo La ruta del archivo a leer.
     */
    Sexo(const std::string& archivo);

    /**
     * @brief Genera un "hijo" genético basado en las frecuencias de caracteres de los padres en el dataset.
     * @param padre1 Primera cadena parental.
     * @param padre2 Segunda cadena parental.
     * @return La cadena resultante que representa al "hijo".
     */
    std::string sexo(const std::string& padre1, const std::string& padre2);
};

#endif // SEXO_H
