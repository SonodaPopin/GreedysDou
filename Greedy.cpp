#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Greedy{
    private:
    string ifp, text, finaltext;
    float thr;
    int nnn, mmm, iii, finalquality;
    vector<string> cadenasOriginales;

    bool abrirArchivo(){
        ifstream inputFile(ifp);
        if (!inputFile.is_open()) {
            cerr << "No se pudo abrir el archivo de entrada." << endl;
            return false;
        }else{
            stringstream buffer;
            buffer << inputFile.rdbuf();
            text = buffer.str();
            inputFile.close();
            cerr << "Archivo recibido con éxito, procesando.." << endl;   
            return true;
        }
    }

    string analizarCadenas() {
        stringstream ss(ifp);
        string cadena;
        vector<unordered_map<char, int>> conteos;
        while (getline(ss, cadena)) {
            cadenasOriginales.push_back(cadena);
            if (mmm == 0) {
             mmm = cadena.length();
            }
            for(int i=0; i<mmm; i++){
                if (i >= conteos.size()) {
                conteos.resize(i + 1);
                 }
            nnn++;
            conteos[i][cadena[i]]++;
            }
        }
            string resultado;
        for (const auto& conteo : conteos) {
            char caracterMenosRepetido;
            int minConteo = 0;
            for (const auto& par : conteo) {
                if (par.second < minConteo || minConteo == 0) {
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
            float total = diferencias/mmm;
            if (total >= thr) {
                contador++;
            }
        }
        return contador;
    }

    public:
     Greedy(const string &ifp, float thr){
        this->ifp = ifp;
        this->thr = thr;
        if (!abrirArchivo()) {
        exit(1);
        }
        finaltext = analizarCadenas();
        finalquality = contarDiferencias();
        cout << finalquality << finaltext << endl;
    }
};