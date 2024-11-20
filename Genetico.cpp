#include "Genetico.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include "sexo.h"
#include "Funciones.h"

using namespace std;
using namespace chrono;

// Implementación de los métodos privados

void Genetico::procreador() {
    double percentil = probabilidad(valores100);
    while (!valores100.empty()) {
        int selector = rand() % valores100.size();
        bool key = false;
        while (!key) {
            int seleccionado = rand() % valores100.size();
            while (selector == seleccionado) {
                seleccionado = rand() % valores100.size();
            }
            double distancia = abs(valores100[selector] - valores100[seleccionado]);
            double chance = distancia / percentil;
            int dado = rand() % 101;
            if (dado >= chance) {
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

void Genetico::matador() {
    double percentil = probabilidad(valores150);
    int maxValor = *max_element(valores150.begin(), valores150.end());
    while (valores100.size() < 100) {
        int seleccionado = rand() % valores150.size();
        double distancia = abs(maxValor - valores150[seleccionado]);
        double chance = distancia / percentil;
        int dado = rand() % 101;
        if (dado >= chance) {
            valores100.push_back(valores150[seleccionado]);
            cadenas100.push_back(cadenas150[seleccionado]);
            valores150.erase(valores150.begin() + seleccionado);
            cadenas150.erase(cadenas150.begin() + seleccionado);
        }
    }
    valores150.clear();
    cadenas150.clear();
}

bool Genetico::checkTime() {
    auto tiempoActual = system_clock::now();
    return duration_cast<seconds>(tiempoActual - startTime).count() >= maxTime;
}

void Genetico::genetizar() {
    cerr << "genetizando" << endl;
    startTime = system_clock::now();
    while (!checkTime()) {
        int maxValue = *std::max_element(valores100.begin(), valores100.end());
        cerr << "mejor obtenida de generacion " << maxValue << endl;
        procreador();
        matador();
        if (maxValue > solQuality) {
            solQuality = maxValue;
            bestTime = system_clock::now();
            cout << "Mejor calidad obtenida: " << solQuality 
                 << " Tiempo usado para obtenerla: " << getFinalTime() << " segundos." << endl;
        }
    }
}

// Implementación de los métodos públicos

Genetico::Genetico(const std::string& ifp, int maxTime, vector<string> cadenas100) 
    : maxTime(maxTime), cama(ifp), cadenas100(cadenas100) {
    cadenas100.resize(100);
    valores100.resize(100);
    cadenasOriginales = leerArchivo(ifp);
    cerr << "Constructor genetico" << endl;
    for (int i = 0; i < 100; i++) {
        valores100[i] = contarDiferencias(cadenas100[i], cadenasOriginales, thr);
    }
    cerr << "genetizar" << endl;
    genetizar();
}

float Genetico::getFinalQuality() {
    return solQuality;
}

double Genetico::getFinalTime() {
    if (bestTime == system_clock::time_point::min()) {
        return 0.0;
    }
    return duration_cast<seconds>(bestTime - startTime).count();
}
