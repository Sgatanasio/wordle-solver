#ifndef MATRIX_H
#define MATRIX_H 
#include <map>
#include <vector>
#include <string>
#include <array>
#endif
class resultsMatrix{
  private:
    // Vector de palabras del que se genera la matriz
    std::vector<std::string> v_;
    
    // Matriz de resultados
    std::vector<std::vector<int>> m_;
    
    // Mapa de índices
    std::map<std::string, int> map_;

    // Vector de palabras posibles
    std::vector<bool>posV_;
    
    // Vector de letras posicionadas, no posicionadas y grises
    std::vector<char> positioned_;  
    std::vector<char> unpositioned_;
    std::vector<bool> greyLetters_;

    // Número mínimo de letras por palabra
    std::map<char, int> minLetterCounts_;
    std::map<char, int> maxLetterCounts_;
    
    // Número de palabras posibles
    int nPos_;

    // Calcula el resultado
    int calcResult(const std::string& solution, const std::string& guess);
    
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
  
    // Sacar el número de palabras posibles
    int getNPos();

    // Actualizar el vector de palabras posibles
    void updateSet(int result,std::string prevWord);
    
    bool validWord(std::vector<char> positioned, std::vector<std::vector<char>> yellowRestrictions, std::string w);

    // Entropía de una palabra
    float wordEntropy(std::string w);

    // Sacar primera palabra válida
    std::string getFirstValidWord();

    // Sacar la mejor palabra 
    std::string chooseBestWord();
};
