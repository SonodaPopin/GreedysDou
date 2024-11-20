#include "Funciones.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> leerArchivo(const string& ifp) {
    ifstream archivo(ifp);
    vector<string> datos;
    if (!archivo) {
        throw runtime_error("No se puede abrir el archivo: " + ifp);
    }
    string linea;
    while (getline(archivo, linea)) {
        datos.push_back(linea);
    }
    archivo.close();
    return datos;
}

int contarDiferencias(const string& seleccionada, const vector<string>& cadenas, float thr) {
    int contador = 0;
    for (const std::string& cadena : cadenas) {
        if (cadena.length() != seleccionada.length()) continue;
        int diferencias = 0;
        for (size_t i = 0; i < seleccionada.length(); ++i) {
            if (seleccionada[i] != cadena[i]) {
                diferencias++;
            }
        }
        float proporcionDiferencias = static_cast<float>(diferencias) / seleccionada.length();
        if (proporcionDiferencias >= thr) {
            contador++;
        }
    }
    return contador;
}

double probabilidad(vector<int> valores){
    if (valores.empty()) return 1;
    int maxValor = *max_element(valores.begin(), valores.end());
    int minValor = *min_element(valores.begin(), valores.end());
    double percentil = (maxValor-minValor)/100;
    if (percentil != 0){
        return percentil;
    }else{
        return 1;
    }
}
