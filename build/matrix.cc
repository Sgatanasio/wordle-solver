#include "matrix.h"
#include "func.h"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <utility>
#include <cassert>
#include <iostream>
int resultsMatrix::calcResult(const std::string& solution, const std::string& guess)
{
    assert(solution.size() == 5 && guess.size() == 5);

    int result[5] = {0, 0, 0, 0, 0};
    bool used[5]   = {false, false, false, false, false};

    // PASS 1: Greens
    for (int i = 0; i < 5; ++i) {
        if (guess[i] == solution[i]) {
            result[i] = 2;
            used[i] = true;
        }
    }

    // PASS 2: Yellows
    for (int i = 0; i < 5; ++i) {
        if (result[i] != 0) continue;

        for (int j = 0; j < 5; ++j) {
            if (!used[j] && guess[i] == solution[j]) {
                result[i] = 1;
                used[j] = true;
                break;
            }
        }
    }

    // Encode: r0*3^4 + r1*3^3 + ... + r4*3^0
    int code = 0;
    for (int i = 0; i < 5; ++i) {
        code = code * 3 + result[i];
    }

    return code;
}

void resultsMatrix::calcMatrix(){
  for(auto w1 : v_){
    std::vector<int> row;
    for(auto w2 : v_){
      row.push_back(calcResult(w1, w2));
    }
    m_.push_back(row);
  }
}

resultsMatrix::resultsMatrix(std::vector<std::string> v){
  
  // Inicializa vectores de palabras y de posibles
  v_ = v;
  posV_.resize(v_.size(),true);
  nPos_ = v_.size();

  // Inicializa el array de letras grises

  greyLetters_.resize(26,false);

  // Inicializa mapa de índices
  for(int i = 0; i < v_.size(); i++){
    map_.insert({v[i],i});
  }
  
  // Inicializa mapas de letras máximas y mínimas

  minLetterCounts_.clear();
  maxLetterCounts_.clear();

  // Calcula la matriz
  calcMatrix();
}

int resultsMatrix::getIndex(std::string w){
  auto it = map_.find(w);

  if(it == map_.end()){
    return -1;
  }

  return it->second;
}

std::string resultsMatrix::getWord(int i){
  return v_[i];
}

int resultsMatrix::getResult(int i, int j){
  return m_[i][j];
}

int resultsMatrix::getResult(std::string w1, std::string w2){
  return getResult(getIndex(w1),getIndex(w2));
}

int resultsMatrix::getNPos(){
  return nPos_;
}

bool resultsMatrix::validWord(std::vector<char> positioned, 
                             std::vector<std::vector<char>> yellowRestrictions,
                             std::string w) {
    
    // 1. Check green positions
    for(int i = 0; i < 5; i++) {
        if(positioned[i] != 0 && positioned[i] != w[i]) {
            return false;
        }
    }
    
    // 2. Check yellow restrictions
    for(int i = 0; i < 5; i++) {
        for(char forbidden : yellowRestrictions[i]) {
            if(w[i] == forbidden) {
                return false;
            }
        }
    }
    
    // 3. Count letters in the word
    std::map<char, int> actual_counts;
    for(int i = 0; i < 5; i++) {
        actual_counts[w[i]]++;
    }
    
    // 4. Check letter count constraints
    for(const auto& [letter, actual] : actual_counts) {
        // Check minimum
        if(minLetterCounts_.find(letter) != minLetterCounts_.end()) {
            if(actual < minLetterCounts_[letter]) {
                return false;
            }
        }
        
        // Check maximum
        if(maxLetterCounts_.find(letter) != maxLetterCounts_.end()) {
            if(actual > maxLetterCounts_[letter]) {
                return false;
            }
        }
    }
    
    // 5. Check gray letters
    for(int i = 0; i < 26; i++) {
        if(greyLetters_[i]) {
            char gray_letter = 'a' + i;
            if(actual_counts[gray_letter] > 0) {
                return false;
            }
        }
    }
    
    return true;
}

void resultsMatrix::updateSet(int result, std::string prevWord) {
  for (int i = 0; i < v_.size(); i++){
    if(!posV_[i]) continue;

    if(calcResult(v_[i], prevWord) != result){
      posV_[i] = false;
      --nPos_;
    }
  }
}

float resultsMatrix::wordEntropy(std::string w){
  
  std::array<int,243> counts = {0};
  int wIdx = getIndex(w);
  
  int totalPossible = 0;
  for(int i = 0; i < v_.size(); i++){
    if(posV_[i]){
      totalPossible++;
      int r = m_[wIdx][i];
      counts[r]++;
    }
  }

  float entropy = 0;
  for (int i = 0; i < 243; i++) {
    if (counts[i] > 0) {
      float p = (float)counts[i] / totalPossible;
      entropy += p * (-log2f(p));
    }
  }
  return entropy;
}

std::string resultsMatrix::getFirstValidWord(){
  for(int i = 0; i < v_.size(); i++){
    if(posV_[i]){
      return v_[i];
    }
  }
  std::cout << "NO VALID WORDS" << std::endl;
  return "";
}

std::string resultsMatrix::chooseBestWord(){
  float bestEntropy = 0;
  std::string retVal;
  for(int i = 0; i < v_.size(); i++){
    if(posV_[i]){
      float entropy = wordEntropy(v_[i]);

      if(entropy > bestEntropy){
        bestEntropy = entropy;
        retVal = v_[i];
      }
    }
  }

  return retVal;
}

