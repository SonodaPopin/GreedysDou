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

/**
 * @brief Clase que implementa un algoritmo heurístico basado en un enfoque codicioso y probabilístico
 *        para encontrar una cadena que maximice la disimilitud con otras cadenas en un archivo.
 */
class AGreedy{
    private:
    std::string ifp, seleccionada;
    float thr, alpha, calidad;
    std::vector<std::string> datos;
    std::chrono::duration<double> elapsed;

    /**
     * @brief Lee el archivo y carga su contenido en el dataset.
     */
    void leerArchivo() {
        std::ifstream archivo(ifp);
        if (!archivo) {
            std::cerr << "No se puede abrir el archivo: " << ifp << std::endl;
            exit(1);
        }

        std::string linea;
        while (std::getline(archivo, linea)) {
            datos.push_back(linea);
        }

        archivo.close();
    }

    /**
     * @brief Calcula la frecuencia de cada carácter en todas las líneas y devuelve los caracteres ordenados por frecuencia.
     * @return Un vector con los caracteres ordenados de mayor a menor frecuencia.
     */
    std::vector<char> obtenerCaracteresFrecuentes() {
        std::unordered_map<char, int> frecuencia;
        
        // Contar la frecuencia de cada carácter en todas las líneas
        for (const std::string& linea : datos) {
            for (char caracter : linea) {
                frecuencia[caracter]++;
            }
        }
        
        // Ordenar caracteres por frecuencia (más frecuentes primero)
        std::vector<std::pair<char, int>> frecuenciaVector(frecuencia.begin(), frecuencia.end());
        std::sort(frecuenciaVector.begin(), frecuenciaVector.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
        
        // Extraer solo los caracteres en función de su frecuencia
        std::vector<char> caracteresFrecuentes;
        for (const auto& par : frecuenciaVector) {
            caracteresFrecuentes.push_back(par.first);
        }

        return caracteresFrecuentes;
    }

    /**
     * @brief Calcula la calidad de la solución basada en el umbral de similitud dado.
     * @param seleccionada La cadena seleccionada por el algoritmo.
     * @param thr Umbral de similitud.
     * @return La calidad como la proporción de cadenas que cumplen con el umbral.
     */
    double calcularSimilitud(const std::string& seleccionada, float thr) {
    if (datos.empty()) return 0.0;

    double sumaDiferencias = 0.0;
    size_t longitudLinea = datos[0].length();
    float conteoDiferencias = 0;  

    for (const std::string& linea : datos) {
        if (linea.length() != longitudLinea) continue; 

        int diferencias = 0;
        for (size_t i = 0; i < longitudLinea; ++i) {
            if (seleccionada[i] != linea[i]) {
                diferencias++;
            }
        }

        float proporcionDiferencias = static_cast<float>(diferencias) / longitudLinea;

        if (proporcionDiferencias >= thr) {
            conteoDiferencias++;
        }
    }

    return (conteoDiferencias); 
    }

    /**
     * @brief Ejecuta el algoritmo para generar una cadena que maximice la disimilitud.
     * @return La cadena seleccionada por el algoritmo.
     */
    std::string ejecutar() {

        srand(static_cast<unsigned>(time(0))); // Inicializa la semilla para números aleatorios

        std::vector<char> caracteresFrecuentes = obtenerCaracteresFrecuentes();
        
        if (datos.empty()) {
            std::cerr << "No hay datos para procesar." << std::endl;
            return 0;
        }
        
        size_t longitudLinea = datos[0].length();
        std::string seleccionada(longitudLinea, ' ');

        size_t caracteresDiferentesRequeridos = static_cast<size_t>(longitudLinea);
        
        for (size_t i = 0; i < longitudLinea; ++i) {
        std::unordered_map<char, int> frecuenciaPosicion;
        for (const std::string& linea : datos) {
            if (i < linea.length()) {
                frecuenciaPosicion[linea[i]]++;
            }
        }

        // Obtener el carácter más frecuente en esa posición
        char caracterMenosFrecuente = std::min_element(
            frecuenciaPosicion.begin(), frecuenciaPosicion.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; }
        )->first;

        double p = static_cast<double>(rand()) / RAND_MAX;
        if (p < alpha) {
            // Elegir aleatoriamente un carácter en lugar del menos frecuente
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
            // Usar el carácter menos frecuente
            seleccionada[i] = caracterMenosFrecuente;
        }
    }
        return seleccionada;
    }

    public:

    /**
     * @brief Constructor de la clase AGreedy.
     * @param ifp Ruta del archivo de entrada.
     * @param thr Umbral de similitud.
     * @param alpha Parámetro probabilístico para la selección de caracteres.
     */
    AGreedy(const std::string & ifp, float thr, float alpha){
        this->ifp = ifp;
        this->thr = thr;
        this->alpha = alpha;

        leerArchivo();

        auto start = std::chrono::high_resolution_clock::now();
        seleccionada = ejecutar();
        auto end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        calidad = calcularSimilitud(seleccionada, thr);
    }

    /**
     * @brief Devuelve la calidad de la solución seleccionada.
     * @return Calidad de la solución.
     */
    float getCalidad(){
        return (calidad);
    }

    /**
     * @brief Devuelve el tiempo de ejecución del algoritmo.
     * @return Duración del tiempo de ejecución.
     */
    std::chrono::duration<double> getElapsed(){
        return(elapsed);
    }
};
/** 
 int main(int argc, char* argv[]) {
     if (argc < 7) {
        std::cerr << "Uso: " << argv[0] << " -i <archivo> -th <umbral> -alpha <valor-alpha>" << std::endl;
        return 1;
    }

    std::string archivo;
    float umbral;
    float alpha;

    // Procesar los argumentos
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-i" && i + 1 < argc) {
            archivo = argv[++i];
        } else if (arg == "-th" && i + 1 < argc) {
            umbral = std::stof(argv[++i]);
        }else if (arg == "-alpha" && i + 1 < argc) {
            alpha = std::stof(argv[++i]);
        }
    }

    if (archivo.empty()) {
        std::cerr << "Archivo no proporcionado." << std::endl;
        return 1;
    }

    AGreedy algoritmo(archivo, umbral, alpha);

    std::cout << "Calidad: " << algoritmo.getCalidad() 
              << " Tiempo: " << algoritmo.getElapsed().count() << " segundos." << std::endl;

    return 0;
}
*/