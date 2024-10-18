#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Greedy.cpp"  // Incluye tu archivo Greedy.h que contiene la implementación del Greedy original

using namespace std;
using namespace chrono;

/**
 * @brief Clase IteratedGreedy que extiende el Greedy original para realizar iteraciones en búsqueda de mejores resultados.
 */
class IteratedGreedy : public Greedy {
private:
    int maxTime;
    float destructionMargin;
    system_clock::time_point startTime;
    /**
     * @brief Destruye partes aleatorias de la cadena entregada reemplazandolas por partes aleatorias de las cadenas originales.
     * @param stringademoler La cadena a modificar.
     * @param perceltilmargen El porcentaje de los valores de la cadena que serán modificados.
     * @return La cadena modificada.
     */
    string demoledor(const string& stringademoler, int percentilmargen) {
        string stringdemolido = stringademoler;
        int numeromargen = stringademoler.length() * percentilmargen;
        for (int i = 0; i < numeromargen; i++) {
            int suertudo = rand() % stringademoler.length();
            stringdemolido[suertudo] = cadenasOriginales[rand() % cadenasOriginales.size()][suertudo];
        }
        return stringdemolido;
    }
     /**
     * @brief Método para reconstruir la cadena modificada empleando el Greedy original.
     * @param cadena La cadena recién modificada.
     * @return La cadena reconstruida.
     */
    string reconstruir(const string& stringdestruido) {
        return analizarCadenas();
    }
    /**
     * @brief Verifica si ha pasado el tiempo máximo permitido para las iteraciones.
     * @return true si el tiempo límite ha sido excedido, false en caso contrario.
     */
    bool checkTime() {
        auto tiempoActual = system_clock::now();
        return duration_cast<seconds>(tiempoActual - startTime).count() >= maxTime;
    }
    /**
     * @brief Método para realizar una nueva iteración del algoritmo Iterated Greedy.
     */
    void iterar() {
        startTime = system_clock::now();
        while (!checkTime()) {
            string cadenaDestruida = demoledor(finaltext, destructionMargin);
            string cadenaReconstruida = reconstruir(cadenaDestruida);
            int nuevaCalidad = contarDiferencias(cadenaReconstruida);
            if (nuevaCalidad < finalquality) {
                finaltext = cadenaReconstruida;
                finalquality = nuevaCalidad;
            }
        }
    }

public:
    /**
     * @brief Constructor de IteratedGreedy que ejecuta el algoritmo iterado por un tiempo límite.
     * @param ifp El archivo de texto de entrada.
     * @param thr El umbral de diferencias.
     * @param maxTime El tiempo máximo (en segundos) para ejecutar las iteraciones.
     * @param destructionMargin El porcentaje de la cadena que será modificada en cada iteración.
     */
    IteratedGreedy(const string& ifp, float thr, int maxTime, float destructionMargin) 
        : Greedy(ifp, thr), maxTime(maxTime), destructionMargin(destructionMargin) {
        iterar();
    }
};

int main(int argc, char *argv[]) {
    if (argc != 6) {
        cerr << "Uso: " << argv[0] << " -i <archivo> -th <umbral> -t <tiempo>" << endl;
        return 1;
    }

    string archivo;
    float umbral = 0.0;
    int tiempoMax = 0;
    
    // Procesa los argumentos de línea de comandos
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-i" && i + 1 < argc) {
            archivo = argv[++i];  // Obtiene el nombre del archivo
        } else if (string(argv[i]) == "-th" && i + 1 < argc) {
            umbral = stof(argv[++i]);  // Convierte el umbral a float
        } else if (string(argv[i]) == "-t" && i + 1 < argc) {
            tiempoMax = stoi(argv[++i]);  // Convierte el tiempo máximo a int
        } else {
            cerr << "Argumento no reconocido: " << argv[i] << endl;
            return 1;
        }
    }

    if (archivo.empty() || umbral <= 0.0 || tiempoMax <= 0) {
        cerr << "Archivo, umbral o tiempo inválidos." << endl;
        return 1;
    }

    // Crea una instancia de IteratedGreedy con el archivo, umbral y tiempo máximo
    IteratedGreedy algoritmo(archivo, umbral, tiempoMax, 0.1);

    // Muestra los resultados finales
    cout << "Calidad final: " << algoritmo.getQuality() 
         << " Tiempo total: " << algoritmo.getElapsed().count() << " segundos." << endl;

    return 0;
}
