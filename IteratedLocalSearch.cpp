#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Greedy.cpp"
#include "LocalSearch.cpp"

using namespace std;
using namespace chrono;

/**
 * @brief Clase IteratedLocalSearch que emplea un proceso de destrucción y LocalSearch para mejorar una solución planteada por Greedy.
 */
class IteratedLocalSearch {
private:
    Greedy codicia;
    string menoscodicia;
    string solution;
    int maxTime, solQuality;
    float destructionMargin;
    vector<string> cadenasOriginales;
    system_clock::time_point startTime;
    system_clock::time_point bestTime;
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
        LocalSearch reparar(cadenasOriginales);
        return reparar.local_search(stringdestruido);
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
            string cadenaDestruida = demoledor(solution, destructionMargin);
            string cadenaReconstruida = reconstruir(cadenaDestruida);
            int nuevaCalidad = codicia.contarDiferencias(cadenaReconstruida);
            if (nuevaCalidad < solQuality) {
                solution = cadenaReconstruida;
                solQuality = nuevaCalidad;
                bestTime = system_clock::now();
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
    IteratedLocalSearch(const string& ifp, float thr, int maxTime, float destructionMargin) 
        : codicia(ifp, thr), maxTime(maxTime), destructionMargin(destructionMargin) {
        solution = codicia.getFinaltext();
        solQuality = codicia.getQuality();
        cadenasOriginales = codicia.getOriginales();
        iterar();
    }
    /**
     * @brief Getter para obtener el valor de calidad final guardado.
     * @return El valor de calidad.
     */
    float getFinalQuality(){
        return(solQuality);
    }
    /**
     * @brief Getter para obtener el valor de calidad final guardado.
     * @return El valor de calidad.
     */
    double getFinalTime() {
        return duration_cast<seconds>(bestTime - startTime).count();
    }
};

int main(int argc, char *argv[]) {
    if (argc != 9) {
        cerr << "Uso: " << argv[0] << " -i <archivo> -th <umbral> -t <tiempo> -dm <margen de destruccion>" << endl;
        return 1;
    }
    string archivo;
    float umbral = 0.0;
    int tiempoMax = 0;  
    float destructionMargin = 0.0;
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-i" && i + 1 < argc) {
            archivo = argv[++i];  // Obtiene el nombre del archivo
        } else if (string(argv[i]) == "-th" && i + 1 < argc) {
            umbral = stof(argv[++i]);  // Convierte el umbral a float
        } else if (string(argv[i]) == "-t" && i + 1 < argc) {
            tiempoMax = stoi(argv[++i]);  // Convierte el tiempo máximo a int
        } else if (string(argv[i]) == "-dm" && i + 1 < argc) { // Añadir verificación para destructionMargin
            destructionMargin = stof(argv[++i]);  // Convierte el margen de destrucción a float
        } else {
            cerr << "Argumento no reconocido: " << argv[i] << endl;
            return 1;
        }
    }
    if (archivo.empty() || umbral <= 0.0 || tiempoMax <= 0 || destructionMargin < 0.0 || destructionMargin > 1.0) {
        cerr << "Archivo, umbral, tiempo o margen de destrucción inválidos." << endl;
        return 1;
    }
    IteratedLocalSearch algoritmo(archivo, umbral, tiempoMax, destructionMargin);
    cout << "Mejor calidad obtenida: " << algoritmo.getFinalQuality() 
         << " Tiempo usado para obtenerla: " << algoritmo.getFinalTime() << " segundos." << endl;

    return 0;
}
