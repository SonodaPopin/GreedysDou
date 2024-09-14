#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <string>
#include <fstream>
#include <sstream> 
#include <unordered_map>

class AGreedy{
    private:
    std::string ifp;
    float thr;
    std::vector<std::string> datos;

    void leerArchivo() {
        std::ifstream archivo(ifp);
        if (!archivo) {
            std::cerr << "No se puede abrir el archivo: " << ifp << std::endl;
            exit(1);
        }

        std::string linea;
        while (std::getline(archivo, linea)) {
            datos.push_back(linea);
        }

        archivo.close();
        std::cout << "Archivo leído correctamente." << std::endl;
    }

    public:
    AGreedy(const std::string & ifp, float thr){
        this->ifp = ifp;
        this->thr = thr;

        leerArchivo();
    }

    void ejecutar() {
        srand(static_cast<unsigned>(time(0))); // Inicializa la semilla para números aleatorios

        std::vector<std::string> seleccionados;
        int numCaracteresSeleccionados = 0;
        int numLineasSeleccionadas = 0;

        for (const std::string& linea : datos) {
            std::string seleccionada;
            int caracteresSeleccionadosEnLinea = 0;

            for (char caracter : linea) {
                double probabilidad = static_cast<double>(rand()) / RAND_MAX; // Genera una probabilidad entre 0 y 1
                if (probabilidad < thr) {
                    seleccionada += caracter;
                    caracteresSeleccionadosEnLinea++;
                }
            }

            if (caracteresSeleccionadosEnLinea > 0) {
                seleccionados.push_back(seleccionada);
                numLineasSeleccionadas++;
                numCaracteresSeleccionados += caracteresSeleccionadosEnLinea;
            }
        }

        // Mostrar resultados
        std::cout << "Número de líneas con caracteres seleccionados: " << numLineasSeleccionadas << std::endl;
        std::cout << "Número total de caracteres seleccionados: " << numCaracteresSeleccionados << std::endl;
        std::cout << "Líneas con caracteres seleccionados: " << std::endl;
        for (const std::string& linea : seleccionados) {
            std::cout << linea << std::endl;
        }
    }
    
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <archivo> <umbral>" << std::endl;
        return 1;
    }

    std::string archivo = argv[1];
    float umbral = std::stof(argv[2]);

    AGreedy algoritmo(archivo, umbral);
    algoritmo.ejecutar();

    return 0;
}

