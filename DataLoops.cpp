#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <cmath> 
#include <iomanip>  
#include "Greedy.cpp"
#include "AGreedy.cpp"

// Función para calcular la media de un vector de floats
double calcularMedia(const std::vector<double>& valores) {
    double suma = std::accumulate(valores.begin(), valores.end(), 0.0);
    return suma / valores.size();
}

// Función para calcular la desviación estándar de un vector de doubles
double calcularDesviacionEstandar(const std::vector<double>& valores, double media) {
    double sumaCuadrados = 0.0;
    for (double valor : valores) {
        sumaCuadrados += std::pow(valor - media, 2);
    }
    return std::sqrt(sumaCuadrados / valores.size());
}

void loopGreedy(){

}

void loopAGreedy(int N, int M, float umbral, float alpha) {
    std::vector<double> calidades;
    std::vector<double> tiempos;

    // Generar archivos con formato N-M-001.txt hasta N-M-100.txt
    for (int i = 1; i <= 100; ++i) {
        // Crear el nombre del archivo en formato N-M-XXX.txt
        std::ostringstream nombreArchivo;
        nombreArchivo <<"D:/Joako/Desktop/Archivos de la U/SistemasAdaptativos/GreedysDou/Dataset/"<< N << "-" << M << "-" << std::setfill('0') << std::setw(3) << i << ".txt";

        // Ejecutar AGreedy en el archivo
        std::string archivo = nombreArchivo.str();
        std::cout << "Ejecutando AGreedy para archivo: " << archivo << std::endl;

        AGreedy algoritmo(archivo, umbral, alpha);
        calidades.push_back(algoritmo.getCalidad());
        tiempos.push_back(algoritmo.getElapsed().count());
    }

    // Calcular media y desviación estándar de calidades
    double mediaCalidad = calcularMedia(calidades);
    double desviacionCalidad = calcularDesviacionEstandar(calidades, mediaCalidad);

    // Calcular media y desviación estándar de tiempos
    double mediaTiempo = calcularMedia(tiempos);
    double desviacionTiempo = calcularDesviacionEstandar(tiempos, mediaTiempo);

    // Mostrar los resultados
    std::cout << "Resultados para N = " << N << ", M = " << M << std::endl;
    std::cout << "Media Calidad A-Greedy: " << mediaCalidad << std::endl;
    std::cout << "Desviación Estándar Calidad A-Greedy: " << desviacionCalidad << std::endl;
    std::cout << "Media Tiempo A-Greedy: " << mediaTiempo << " segundos" << std::endl;
    std::cout << "Desviación Estándar Tiempo A-Greedy: " << desviacionTiempo << " segundos" << std::endl;
}

int main() {
    loopAGreedy(100,300,0.8,0.5);
    return 0;
}
