#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <chrono>

using namespace std;

class Greedy {
private:
    string ifp, text, finaltext;
    float thr;
    int nnn, mmm, finalquality;
    vector<string> cadenasOriginales;
    chrono::duration<double> elapsed;

    bool abrirArchivo() {
        ifstream inputFile(ifp);
        if (!inputFile.is_open()) {
            cerr << "No se pudo abrir el archivo de entrada." << endl;
            return false;
        } else {
            stringstream buffer;
            buffer << inputFile.rdbuf();
            text = buffer.str();
            inputFile.close();
            return true;
        }
    }

    string analizarCadenas() {
        stringstream ss(text);
        string cadena;
        vector<unordered_map<char, int>> conteos;
        while (getline(ss, cadena)) {
            cadenasOriginales.push_back(cadena);
            if (mmm == 0) {
                mmm = cadena.length();
            }
            for (int i = 0; i < mmm; i++) {
                if (i >= conteos.size()) {
                    conteos.resize(i + 1);
                }
                nnn++;
                conteos[i][cadena[i]]++;
            }
        }
        string resultado;
        for (const auto& conteo : conteos) {
            char caracterMenosRepetido = '\0';
            int minConteo = numeric_limits<int>::max();
            for (const auto& par : conteo) {
                if (par.second < minConteo) {
                    minConteo = par.second;
                    caracterMenosRepetido = par.first;
                }
            }
            resultado += caracterMenosRepetido;
        }
        return resultado;
    }

    int contarDiferencias() {
        int contador = 0;
        for (const string& cadena : cadenasOriginales) {
            int diferencias = 0;
            for (int i = 0; i < cadena.length(); i++) {
                if (cadena[i] != finaltext[i]) {
                    diferencias++;
                }
            }
            float total = static_cast<float>(diferencias) / mmm;
            if (total >= thr) {
                contador++;
            }
        }
        return contador;
    }

public:
    Greedy(const string &ifp, float thr) : ifp(ifp), thr(thr), nnn(0), mmm(0) {
        if (!abrirArchivo()) {
            exit(1);
        }
        auto start = chrono::high_resolution_clock::now();
        finaltext = analizarCadenas();
        finalquality = contarDiferencias();
        auto end = chrono::high_resolution_clock::now();
        elapsed = end - start;
    }

    chrono::duration<double> getElapsed(){
        return(elapsed);
    }
    float getQuality(){
        return(finalquality);
    }
};
/*
int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Uso: " << argv[0] << " -i <archivo> -th <umbral>" << std::endl;
        return 1;
    }
    std::string archivo;
    float thr = 0.0;
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-i" && i + 1 < argc) {
            archivo = argv[++i]; // El siguiente argumento es el archivo
        } else if (std::string(argv[i]) == "-th" && i + 1 < argc) {
            thr = std::stof(argv[++i]); // El siguiente argumento es el umbral (convertido a float)
        } else {
            std::cerr << "Argumento no reconocido: " << argv[i] << std::endl;
            return 1;
        }
    }
    if (archivo.empty() || thr <= 0.0) {
        std::cerr << "Archivo o umbral inválidos." << std::endl;
        return 1;
    }
    Greedy algoritmo(archivo, thr);
    std::cout << "Calidad: " << algoritmo.getQuality() 
              << " Tiempo: " << algoritmo.getElapsed().count() << " segundos." << std::endl;

    return 0;
}
*/