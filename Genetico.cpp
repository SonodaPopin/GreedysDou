#include <iostream>
#include <cstdlib>
#include <chrono>
#include <map>
#include "AGreedy2.cpp"
#include "LocalSearch.cpp"

using namespace std;
using namespace chrono;

class Genetico {
private:
    int thr = 0.8;
    int alpha = 0.8;
    int maxTime, solQuality;
    AGreedy2 creador;
    string bestSol;
    vector<string> cadenasOriginales;
    std::map<string, int> cadenas100, cadenas150;
    system_clock::time_point startTime;
    system_clock::time_point bestTime = system_clock::time_point::min();

    int contarDiferencias(const string& txtnuevo) {
        int contador = 0;
        for (const string& cadena : cadenasOriginales) {
            int diferencias = 0;
            for (int i = 0; i < cadena.length(); i++) {
                if (cadena[i] != txtnuevo[i]) {
                    diferencias++;
                }
            }
            float total = static_cast<float>(diferencias) / cadena.length();
            if (total >= thr) {
                contador++;
            }
        }
        return contador;
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
    void genetizar() {
        startTime = system_clock::now();
        while (!checkTime()) {
            string cadenaDestruida = demoledor(solution, destructionMargin);
            string cadenaReconstruida = reconstruir(cadenaDestruida);
            int nuevaCalidad = codicia.contarDiferencias(cadenaReconstruida);
            if (nuevaCalidad > solQuality) {
                solution = cadenaReconstruida;
                solQuality = nuevaCalidad;
                bestTime = system_clock::now();
                cout << "Mejor calidad obtenida: " << solQuality 
                << " Tiempo usado para obtenerla: " << getFinalTime() << " segundos." << endl;
            }
        }
    }
public:
    Genetico(const std::string& ifp, int maxTime) 
        : creador(ifp, thr, alpha), maxTime(maxTime),{
        for (int i=0; i<100; i++){
            string solucion = creador.generarSolucion();
            cadenas100[solucion] = contarDiferencias(solucion);
        }
        cadenasOriginales = creador.getDatos();
        genetizar();
    }
    /**
     * @brief Getter para obtener el valor de calidad final guardado.
     * @return El valor de calidad.
     */
    float getFinalQuality(){
        return(solQuality);
    }
    /**
     * @brief Getter para obtener el tiempo de la mejor solución obtenida.
     * @return El tiempo.
     */
    double getFinalTime() {
    if (bestTime == system_clock::time_point::min()) {
        return 0.0;
    }
    return duration_cast<seconds>(bestTime - startTime).count();
}
};