#include "Sexo.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Funciones.h"

using namespace std;

// Implementación de los métodos de la clase Sexo

/**
 * @brief Constructor que inicializa la clase leyendo un archivo de entrada.
 * @param archivo La ruta del archivo a leer.
 */
Sexo::Sexo(const string& archivo) : ifp(archivo) {
    dataset = leerArchivo(ifp);
}

/**
 * @brief Cuenta la frecuencia de un carácter específico en una posición dada dentro del dataset.
 * @param caracter El carácter cuya frecuencia se evalúa.
 * @param posicion La posición en la que se evalúa el carácter.
 * @return La frecuencia del carácter en la posición especificada.
 */
int Sexo::contarFrecuencia(char caracter, int posicion) {
    int frecuencia = 0;
    for (const string& cadena : dataset) {
        if (cadena[posicion] == caracter) {
            frecuencia++;
        }
    }
    return frecuencia;
}

/**
 * @brief Genera un "hijo" genético basado en las frecuencias de caracteres de los padres en el dataset.
 * @param padre1 Primera cadena parental.
 * @param padre2 Segunda cadena parental.
 * @return La cadena resultante que representa al "hijo".
 */
string Sexo::sexo(const string& padre1, const string& padre2) {
    string hijo;
    int longitud = padre1.size();

    for (int i = 0; i < longitud; i++) {
        char char1 = padre1[i];
        char char2 = padre2[i];

        int frecuencia1 = contarFrecuencia(char1, i);
        int frecuencia2 = contarFrecuencia(char2, i);

        if (frecuencia1 < frecuencia2) {
            hijo += char1;
        } else {
            hijo += char2;
        }
    }

    return hijo;
}
