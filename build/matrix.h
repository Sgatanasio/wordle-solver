#ifndef MATRIX_H
#define MATRIX_H 
#endif

#include <vector>
#include <string>
#include <array>

class resultsMatrix{
  private:
    // Vector de palabras del que se genera la matriz
    std::vector<std::string> v_;
    
    // Matriz de resultados
    std::vector<std::vector<int>> m_;
    
    // Vector de palabras posibles
    std::vector<std::string>posV_;

    // Calcula el resultado
    int calcResult(std::string w1, std::string w2);
    
    // Recalcula la matriz basado en el vector v_
    void calcMatrix();
  public:
    // Constructor, llama a result para calcular cada resultado y generar la matriz
    resultsMatrix(std::vector<std::string> v);
    
    // De palabra a índice y de índice a palabra (vector)
    int getIndex(std::string w);
    std::string getWord(int i);

    // Sacar resultado por índice y por palabra (matriz)
    int getResult(int i, int j);
    int getResult(std::string w1, std::string w2);

    // Actualizar el vector de palabras posibles
    void updateSet(int result,std::string prevWord);
    
    // Probabilidad de que una palabra de un resultado
    float resultProb(int result, std::string w);

    // Entropía de una palabra
    float wordEntropy(std::string w);

    // Sacar la mejor palabra 
    std::string chooseBestWord();
};
