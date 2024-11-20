#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>
#pragma once

std::vector<std::string> leerArchivo(const std::string& ifp);
int contarDiferencias(const std::string& cadena, const std::vector<std::string>& originales, float thr);
double probabilidad(std::vector<int> valores);

#endif