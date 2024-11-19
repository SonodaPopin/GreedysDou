#include <iostream>
#include <cstdlib>
#include <chrono>
#include <map>
#include "AGreedy2.cpp"
#include "LocalSearch.cpp"
#include "sexo.cpp"

using namespace std;
using namespace chrono;

class Genetico {
private:
    int thr = 0.8;
    int alpha = 0.8;
    int maxTime, solQuality;
    AGreedy2 creador;
    Sexo cama;
    string bestSol;
    vector<string> cadenasOriginales;
    vector<string> cadenas100, cadenas150;
    vector<int> valores100, valores150;
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
    double probabilidad(vector<int> valores){
         int maxValor = 0;
         int minValor = 999;
         int valor;
         for (int i; i<valores.size(); i++) {
            valor = valores[i];
            if (valor > maxValor) {
                maxValor = valor;
            }
            if (valor < maxValor) {
                minValor = valor;
            }
        }
        double percentil = (maxValor-minValor)/100;
        return percentil;
    }
    vector<string> procreador() {
        double percentil = probabilidad(valores100);
        while (!valores100.empty()) {
            int selector = rand() % cadenas100.size();
            bool key = false;
            while(key == false){
                int seleccionado = rand() % cadenas100.size();
                while(selector = seleccionado){
                    int seleccionado = rand() % cadenas100.size();
                }
                double distancia = abs(valores100[selector] - valores100[seleccionado]);
                double chance = distancia/percentil;
                int dado = rand() % 101;
                if (dado >= chance){
                    valores150.push_back(valores100[selector]);
                    cadenas150.push_back(cadenas100[selector]);
                    valores150.push_back(valores100[seleccionado]);
                    cadenas150.push_back(cadenas100[seleccionado]);
                    string hijo = cama.sexo(cadenas100[selector], cadenas100[seleccionado]);
                    valores150.push_back(contarDiferencias(hijo));
                    cadenas150.push_back(hijo);
                    rotate(valores100.begin() + selector, valores100.begin() + selector + 1, valores100.end());
                    valores100.pop_back();
                    rotate(cadenas100.begin() + selector, cadenas100.begin() + selector + 1, cadenas100.end());
                    cadenas100.pop_back();
                    rotate(valores100.begin() + seleccionado, valores100.begin() + seleccionado + 1, valores100.end());
                    valores100.pop_back();
                    rotate(cadenas100.begin() + seleccionado, cadenas100.begin() + seleccionado + 1, cadenas100.end());
                    cadenas100.pop_back();
                    key = true;
                }
            }
        }
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
            procreador();
            cadenas100 = matador(cadenas150, valores150);
            int maxValor = 0;
            string nuevaCadena = "";
            for (int i; i<100; i++) {
                int valor = valores100[i];
                if (valor > maxValor) {
                    maxValor = valor;
                    nuevaCadena = cadenas100[i];
                }
            }
            if (maxValor > solQuality) {
                bestSol = nuevaCadena;
                solQuality = maxValor;
                bestTime = system_clock::now();
                cout << "Mejor calidad obtenida: " << solQuality 
                << " Tiempo usado para obtenerla: " << getFinalTime() << " segundos." << endl;
            }
        }
    }
public:
    Genetico(const std::string& ifp, int maxTime) 
        : creador(ifp, thr, alpha), maxTime(maxTime), cama(ifp){
        for (int i=0; i<100; i++){
            string solucion = creador.generarSolucion();
            cadenas100[i] = solucion;
            valores100[i] = contarDiferencias(solucion);
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