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
    int nnn, mmm, iii;

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

    void separador() {
        string p1, p2, p3;
        istringstream iss(ifp);
        getline(iss, p1, '-');
        getline(iss, p2, '-');
        getline(iss, p2, '.');
        nnn = stoi(p1);
        mmm = stoi(p2);
        iii = stoi(p3);
    }
    
    public:
     Greedy(const string &ifp, float thr){
        this->ifp = ifp;
        this->thr = thr;
        if (!abrirArchivo()) {
        exit(1);
        }
        separador();
    }
};