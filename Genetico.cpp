#include <iostream>
#include <cstdlib>
#include <chrono>
#include "AGreedy2.cpp"
#include "LocalSearch.cpp"
#include "sexo.cpp"
#include "Funciones.cpp"

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

    void procreador() {
        double percentil = probabilidad(valores100);
        while (!valores100.empty()) {
            int selector = rand() % valores100.size();
            bool key = false;
            while(!key){
                int seleccionado = rand() % valores100.size();
                while(selector == seleccionado){
                    int seleccionado = rand() % valores100.size();
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
                    valores150.push_back(contarDiferencias(hijo, cadenasOriginales, thr));
                    cadenas150.push_back(hijo);
                    valores100.erase(valores100.begin() + selector);
                    cadenas100.erase(cadenas100.begin() + selector);
                    if (seleccionado > selector) seleccionado--;
                    valores100.erase(valores100.begin() + seleccionado);
                    cadenas100.erase(cadenas100.begin() + seleccionado);
                    key = true;
                }
            }
        }
    }
    void matador(){
        double percentil = probabilidad(valores150);
        int maxValor = 0;
        for (int i = 0; i<valores150.size(); i++) {
            int valor = valores150[i];
            if (valor > maxValor) {
                maxValor = valor;
            }
        }
        while (valores100.size() < 100) {
            int seleccionado = rand() % valores150.size();
            double distancia = abs(maxValor - valores150[seleccionado]);
            double chance = distancia/percentil;
            int dado = rand() % 101;
            if (dado >= chance){
                valores100.push_back(valores150[seleccionado]);
                cadenas100.push_back(cadenas150[seleccionado]);
                valores150.erase(valores150.begin() + seleccionado);
                cadenas150.erase(cadenas150.begin() + seleccionado);
            }
        }
        valores150.clear();
        cadenas150.clear();
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
            matador();
            int maxValor = 0;
            string nuevaCadena = "";
            for (int i = 0; i<100; i++) {
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
        : creador(ifp, alpha), maxTime(maxTime), cama(ifp){
        cadenas100.resize(100);
        valores100.resize(100);
        cadenasOriginales = leerArchivo(ifp);
        for (int i=0; i<100; i++){
            string solucion = creador.generarSolucion();
            cadenas100[i] = solucion;
            valores100[i] = contarDiferencias(solucion, cadenasOriginales, thr);
        }
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