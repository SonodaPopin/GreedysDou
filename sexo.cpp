#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Funciones.h"

using namespace std;

/**
 * @class Sexo
 * @brief Clase que genera un "hijo" genético a partir de dos padres, utilizando frecuencias de caracteres en un dataset.
 */
class Sexo{
private:
    string padre1, padre2, ifp;
    vector<string> dataset;

    /**
     * @brief Cuenta la frecuencia de un carácter específico en una posición dada dentro del dataset.
     * @param caracter El carácter cuya frecuencia se evalúa.
     * @param posicion La posición en la que se evalúa el carácter.
     * @return La frecuencia del carácter en la posición especificada.
     */
    int contarFrecuencia(char caracter, int posicion) {
        int frecuencia = 0;
        for (const string& cadena : dataset) {
            if (cadena[posicion] == caracter) {
                frecuencia++;
            }
        }
        return frecuencia;
    }
public:

    /**
     * @brief Constructor que inicializa la clase leyendo un archivo de entrada.
     * @param archivo La ruta del archivo a leer.
     */
    Sexo(const string& archivo) : ifp(archivo){
        dataset = leerArchivo(ifp);
    }

    /**
     * @brief Genera un "hijo" genético basado en las frecuencias de caracteres de los padres en el dataset.
     * @param padre1 Primera cadena parental.
     * @param padre2 Segunda cadena parental.
     * @return La cadena resultante que representa al "hijo".
     */
    string sexo(const string& padre1, const string& padre2) {
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
};
/** 
int main(){
string archivo="D:/Joako/Desktop/Archivos de la U/SistemasAdaptativos/GreedysDou/Dataset/100-300-001.txt";

    Sexo dou(archivo);

    string padre1, padre2;
    cout << "Introduce el primer padre: ";
    cin >> padre1;
    cout << "Introduce el segundo padre: ";
    cin >> padre2;

    if (padre1.size() != padre2.size()) {
        cerr << "Los padres deben tener la misma longitud." << endl;
        return 1;
    }

    string hijo = dou.sexo(padre1, padre2);

    cout << "Padre 1: " << padre1 << endl;
    cout << "Padre 2: " << padre2 << endl;
    cout << "Hijo: " << hijo << endl;

    return 0;
}
*/ 