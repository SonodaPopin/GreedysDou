#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;
class Sexo{
private:
    char caracter;
    int posicion;
    string padre1, padre2, ifp;
    vector<string> dataset;

    void leerArchivo() {
        std::ifstream archivo(ifp);
        if (!archivo) {
            std::cerr << "No se puede abrir el archivo: " << ifp << std::endl;
            exit(1);
        }

        std::string linea;
        while (std::getline(archivo, linea)) {
            dataset.push_back(linea);
        }

        archivo.close();
    }

    int contarFrecuencia(char caracter, int posicion) {
        int frecuencia = 0;
        for (const string& cadena : dataset) {
            if (cadena[posicion] == caracter) {
                frecuencia++;
            }
        }
        return frecuencia;
    }
public:
    Sexo(const string& archivo) : ifp(archivo){
        leerArchivo();
    }

    string sexo(const string& padre1, const string& padre2) {
        string hijo;
        int longitud = padre1.size();

        for (int i = 0; i < longitud; i++) {
            char char1 = padre1[i];
            char char2 = padre2[i];

            int frecuencia1 = contarFrecuencia(char1, i);
            int frecuencia2 = contarFrecuencia(char2, i);

            if (frecuencia1 < frecuencia2) {
                hijo += char1;
            } else {
                hijo += char2;
            }
        }

        return hijo;
    }
};

int main(){
string archivo="D:/Joako/Desktop/Archivos de la U/SistemasAdaptativos/GreedysDou/Dataset/100-300-001.txt";

    Sexo dou(archivo);

    string padre1, padre2;
    cout << "Introduce el primer padre: ";
    cin >> padre1;
    cout << "Introduce el segundo padre: ";
    cin >> padre2;

    if (padre1.size() != padre2.size()) {
        cerr << "Los padres deben tener la misma longitud." << endl;
        return 1;
    }

    string hijo = dou.sexo(padre1, padre2);

    cout << "Padre 1: " << padre1 << endl;
    cout << "Padre 2: " << padre2 << endl;
    cout << "Hijo: " << hijo << endl;

    return 0;
}
