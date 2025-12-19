#ifndef FUNC_H
#define FUNC_H
#endif 

#include <string>
#include <vector>

// Limpiar palabra
std::string clip(std::string s);

// Leer palabras de un archivo
std::vector<std::string> readWords(std::string filename);

// De código a vector y de vector a código
std::vector<int> getResultV(int r);
int getResultInt(std::vector<int> v);

// De vector a string
std::string vToString(std::vector<int> v);
