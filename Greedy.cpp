#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <chrono>

using namespace std;
    /**
     * @brief Clase Greedy que realiza los procesos y guarda los resultados.
     */
class Greedy {
private:
    string ifp, text, finaltext;
    float thr;
    int nnn, mmm, finalquality;
    vector<string> cadenasOriginales;
    chrono::duration<double> elapsed;
    /**
    * @brief Abre un archivo .txt y pasa su contenido a un string.
    * @return false si no se pudo abrir el archivo, true si se logró.
    */
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
    /**
    * @brief Toma una una cadena de texto y la separa en muchas cadenas que estaban separadas por un espacio,
    * comparándolas para encontrar los caracteres que menos se repiten en cada posición y crear una nueva cadena en base a ellos.
    * @return La cadena resultante compuesta de los caracteres menos repetidos.
    */
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
    /**
     * @brief Cuenta las diferencias entre la cadena antes creada y las cadenas originales, aumentando en 1 el contador 
     * por cada cadena cuyo porcentaje de diferencia con la otra es mayor al umbral seleccionado.
     * @return El número total de cadenas que cumplen esta condición.
     */
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
    /**
    * @brief El método constructor de Greedy que llama a las otras funciones y guarda el tiempo total de ejecución además
    * del resultado final de calidad.
    * @param ifp el string sobre el que se aplicará el greedy.
    * @param thr el umbral que se usará.
    */
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
    /**
     * @brief Getter para obtener el tiempo de ejecución guardado.
     * @return El tiempo.
     */
    chrono::duration<double> getElapsed(){
        return(elapsed);
    }
    /**
     * @brief Getter para obtener el valor de calidad final guardado.
     * @return El valor de calidad.
     */
    float getQuality(){
        return(finalquality);
    }
};

/*int main(int argc, char *argv[]) {
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
}*/
