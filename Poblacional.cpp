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
#include "AGreedy2.h"
#include "Genetico.h"
#include "Sexo.h"
#include "Funciones.h"

using namespace std;
 
 int main(int argc, char* argv[]) {
     if (argc < 5) {
        cerr << "Uso: " << argv[0] << " -i <archivo> -t <tiempo>" << endl;
        return 1;
    }

    std::string archivo;
    float alpha = 0.1;
    int tiempoMax = 0; 

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-i" && i + 1 < argc) {
            archivo = argv[++i];  // Obtiene el nombre del archivo
        } else if (string(argv[i]) == "-t" && i + 1 < argc) {
            tiempoMax = stoi(argv[++i]);  // Convierte el tiempo máximo a int
        } else {
            cerr << "Argumento no reconocido: " << argv[i] << endl;
            return 1;
        }
    }
    if (archivo.empty() || tiempoMax <= 0 ) {
        cerr << "Archivo o tiempo inválidos." << endl;
        return 1;
    }

    std::cerr << "iniciando" << std::endl;
    AGreedy2 algoritmo(archivo, alpha);
    std::cerr << "progresando" << std::endl;
    std::vector<std::string> solucions = algoritmo.generarSolucion();
    std::cerr << "terminando" << std::endl;
    Genetico genes(archivo, tiempoMax, solucions);
    cout << "Mejor calidad obtenida: " << genes.getFinalQuality() 
         << " Tiempo usado para obtenerla: " << genes.getFinalTime() << " segundos." << endl;
    return 0;
}