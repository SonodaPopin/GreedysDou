#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <random>

/**
 * @class LocalSearch
 * @brief Implementa un algoritmo de búsqueda local para optimizar una solución inicial basada en un dataset dado.
 */
class LocalSearch {
private:
    std::vector<std::string> dataset; 

    /**
     * @brief Calcula la distancia total entre una cadena dada y todas las cadenas en el dataset.
     * @param s La cadena a evaluar.
     * @return La distancia total entre la cadena `s` y el dataset.
     */
    int calculate_distance(const std::string& s) {
        int total_distance = 0;

        for (const auto& str : dataset) {
            int distance = 0;

            for (size_t i = 0; i < s.size(); ++i) {
                if (s[i] != str[i]) distance++;
            }

            total_distance += distance;
        }
        return total_distance;
    }

    /**
     * @brief Genera un vecino de la solución actual modificando un carácter aleatorio.
     * @param current_solution La solución actual.
     * @return Una nueva solución vecina.
     */
    std::string generate_neighbor(const std::string& current_solution) {
        std::string neighbor = current_solution;

        size_t pos = rand() % neighbor.size();
        char alfabeto[] = {'A', 'C', 'G', 'T'};
        char current_char = neighbor[pos];

        char new_char;
        do {
            new_char = alfabeto[rand() % 4];
        } while (new_char == current_char);

        neighbor[pos] = new_char;

        return neighbor;
    }

public:

    /**
     * @brief Constructor de la clase LocalSearch.
     * @param data El conjunto de datos sobre el que se evaluarán las soluciones.
     */
    LocalSearch(const std::vector<std::string>& data) : dataset(data) {
        srand(static_cast<unsigned int>(time(0)));
    }

    /**
     * @brief Ejecuta el algoritmo de búsqueda local para encontrar una solución mejor.
     * @param current_solution La solución inicial a optimizar.
     * @return La mejor solución encontrada.
     */
    std::string local_search(const std::string& current_solution) {
        std::string best_solution = current_solution;
        int best_distance = calculate_distance(current_solution);

        bool improved = true;
        while (improved) {
            improved = false;
            std::string neighbor = generate_neighbor(best_solution);

            int neighbor_distance = calculate_distance(neighbor);
            if (neighbor_distance < best_distance) {
                best_solution = neighbor;
                best_distance = neighbor_distance;
                improved = true;
            }
        }

        return best_solution;
    }
};