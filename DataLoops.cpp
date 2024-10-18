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
#include "IteratedLocalSearch.cpp"

    /**
     * @brief Calcula la media de un vector de floats.
     * @return La media.
     */
double calcularMedia(const std::vector<double>& valores) {
    double suma = std::accumulate(valores.begin(), valores.end(), 0.0);
    return suma / valores.size();
}

    /**
     * @brief Calcula la desviación estándar de un vector de doubles.
     * @return La desviación estándar.
     */
double calcularDesviacionEstandar(const std::vector<double>& valores, double media) {
    double sumaCuadrados = 0.0;
    for (double valor : valores) {
        sumaCuadrados += std::pow(valor - media, 2);
    }
    return std::sqrt(sumaCuadrados / valores.size());
}
    /**
     * @brief Realiza el Greedy sobre un conjunto de archivos txt dentro del dataset.
     * @return La desviación estándar.
     * @param N Se revisarán los archivos con este número de cadenas.
     * @param M Se revisarán los archivos con cadenas de este largo.
     * @param umbral el umbral que se usará en el greedy.
     */
void loopGreedy(int N, int M, float umbral){
    std::vector<double> calidades;
    string j = "000";
        for (int i = 1; i <= 100; ++i) {
        if (i < 10){
            j = "00" +std::to_string(i);
        }else if(i < 100){
            j = "0" +std::to_string(i); 
        }else{
            j = "100";
        }
        string archivo = "Dataset/" + std::to_string(N) + "-" + std::to_string(M) + "-" + j + ".txt";

        // Ejecutar AGreedy en el archivo

        Greedy algoritmo(archivo, umbral);
        calidades.push_back(algoritmo.getQuality());
    }
    double mediaCalidad = calcularMedia(calidades);
    std::cout << "Media Calidad Greedy: " << mediaCalidad << std::endl;
}
    /**
     * @brief Realiza el Greedy aleatorizado sobre un conjunto de archivos txt dentro del dataset.
     * @return La desviación estándar.
     * @param N Se revisarán los archivos con este número de cadenas.
     * @param M Se revisarán los archivos con cadenas de este largo.
     * @param umbral el umbral que se usará en el greedy.
     * @param alpha el valor de alpha que se usará en el greedy.
     */
void loopAGreedy(int N, int M, float umbral, float alpha){
    std::vector<double> calidades;
    string j = "000";
        for (int i = 1; i <= 100; ++i) {
        if (i < 10){
            j = "00" +std::to_string(i);
        }else if(i < 100){
            j = "0" +std::to_string(i); 
        }else{
            j = "100";
        }
        string archivo = "Dataset/" + std::to_string(N) + "-" + std::to_string(M) + "-" + j + ".txt";

        AGreedy algoritmo(archivo, umbral, alpha);
        calidades.push_back(algoritmo.getCalidad());
    }
    double mediaCalidad = calcularMedia(calidades);
    double desviacionCalidad = calcularDesviacionEstandar(calidades, mediaCalidad);
    std::cout << "Media Calidad AGreedy: " << mediaCalidad << std::endl;
    std::cout << "Desviacion Estandar Calidad A-Greedy: " << desviacionCalidad << std::endl;
}

void loopILS(int N, int M, float umbral, int tiempoMax, float destructionMargin){
    std::vector<double> calidades;
    std::vector<double> tiempos;
    std::string j = "000";
        for (int i = 1; i <= 100; ++i) {
        if (i < 10){
            j = "00" +std::to_string(i);
        }else if(i < 100){
            j = "0" +std::to_string(i); 
        }else{
            j = "100";
        }
        std::string archivo = "D:/Joako/Desktop/Archivos de la U/SistemasAdaptativos/GreedysDou/Dataset/" + std::to_string(N) + "-" + std::to_string(M) + "-" + j + ".txt";

        IteratedLocalSearch algoritmo(archivo, umbral, tiempoMax, destructionMargin);
        calidades.push_back(algoritmo.getFinalQuality());
        tiempos.push_back(algoritmo.getFinalTime());
    }
    double mediaCalidad = calcularMedia(calidades);
    double desviacionCalidad = calcularDesviacionEstandar(calidades, mediaCalidad);
    double tiempoPromedio = calcularMedia(tiempos);
    std::cout << "Media Calidad ILS: " << mediaCalidad << std::endl;
    std::cout << "Desviacion Estandar Calidad ILS: " << desviacionCalidad << std::endl;
    std::cout << "Tiempo Promedio ILS: " << tiempoPromedio << std::endl;
}


    /**
     * @brief Función main que realiza las pruebas
     */
int main() {
   
    return 0;
}
