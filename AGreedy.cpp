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

class AGreedy{
    private:
    std::string ifp;
    float thr;
    float alpha;
    std::vector<std::string> datos;

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
        std::cout << "Archivo leído correctamente." << std::endl;
    }

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

    double calcularSimilitud(const std::string& seleccionada) {
        if (datos.empty()) return 0.0;

        double sumaSimilitudes = 0.0;
        size_t longitudLinea = datos[0].length();

        for (const std::string& linea : datos) {
            if (linea.length() != longitudLinea) continue; // Asegurar que las líneas tienen la misma longitud

            int coincidencias = 0;
            for (size_t i = 0; i < longitudLinea; ++i) {
                if (seleccionada[i] == linea[i]) {
                    coincidencias++;
                }
            }
            sumaSimilitudes += static_cast<double>(coincidencias) / longitudLinea;
        }

        return sumaSimilitudes / datos.size(); // Promedio de similitud
    }

    public:
    AGreedy(const std::string & ifp, float thr, float alpha){
        this->ifp = ifp;
        this->thr = thr;
        this->alpha = alpha;

        leerArchivo();
    }

    void ejecutar() {
        // Iniciar medición de tiempo
        auto start = std::chrono::high_resolution_clock::now();

        srand(static_cast<unsigned>(time(0))); // Inicializa la semilla para números aleatorios

        std::vector<char> caracteresFrecuentes = obtenerCaracteresFrecuentes();
        
        if (datos.empty()) {
            std::cerr << "No hay datos para procesar." << std::endl;
            return;
        }
        
        size_t longitudLinea = datos[0].length();
        std::string seleccionada(longitudLinea, ' ');

        size_t caracteresDiferentesRequeridos = static_cast<size_t>(longitudLinea * thr);
        
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
        // Finalizar medición de tiempo
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        double calidad = calcularSimilitud(seleccionada);

        // Imprimir resultados
        std::cout << "Cadena seleccionada: " << seleccionada << std::endl;
        std::cout << "Calidad de la cadena: " << calidad * 100 << "%" << std::endl;
        std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << std::endl;
    }
};

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
    algoritmo.ejecutar();

    return 0;
}
