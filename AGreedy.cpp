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
    AGreedy(const std::string & ifp, float thr){
        this->ifp = ifp;
        this->thr = thr;

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
        
        // Tomar una línea como referencia (asumimos que todas tienen el mismo largo)
        size_t longitudLinea = datos[0].length();
        std::string seleccionada(longitudLinea, ' ');
        
        for (size_t i = 0; i < longitudLinea; ++i) {
            // Selección aleatoria de caracteres en la posición i
            std::vector<char> candidatos;
            for (const std::string& linea : datos) {
                if (i < linea.length()) {
                    candidatos.push_back(linea[i]);
                }
            }

            if (candidatos.empty()) continue;

            size_t indiceSeleccionado = static_cast<size_t>(rand() % candidatos.size());
            seleccionada[i] = candidatos[indiceSeleccionado];
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
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <archivo> <umbral>" << std::endl;
        return 1;
    }

    std::string archivo = argv[1];
    float umbral = std::stof(argv[2]);

    AGreedy algoritmo(archivo, umbral);
    algoritmo.ejecutar();

    return 0;
}