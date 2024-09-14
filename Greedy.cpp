#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Greedy{
    private:
    string ifp, text;
    float thr;

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

    public:
     Greedy(const string &ifp, float thr){
        this->ifp = ifp;
        this->thr = thr;
        if (!abrirArchivo()) {
        exit(1);
        }
    }
};