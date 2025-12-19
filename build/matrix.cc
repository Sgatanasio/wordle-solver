#include "matrix.h"
#include "func.h"
#include <algorithm>
#include <cmath>
#include <iterator>

int resultsMatrix::calcResult(std::string w1, std::string w2){
  
  if(w1.length() != 5 || w2.length() != 5){
    return -1;
  }

  int retVal = 0;

  for(int i = 0; i < w2.length(); i++){
    if(w1[i] == w2[i]){
      retVal += 2*3^(4-i);
    } else if (w2.find(w1[i])) { 
      retVal += 1*3^(4-i);
    }
  }

  return retVal;
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
  v_ = v;
  posV_ = v;
  calcMatrix();
}

int resultsMatrix::getIndex(std::string w){
  auto it = std::find(v_.begin(), v_.end(), w);
  return std::distance(v_.begin(),it);
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

bool validWord(std::vector<char> positioned, std::vector<char> unpositioned, std::string w){

  for(int i = 0; i < positioned.size(); i++){
    if(positioned[i] != 0 && positioned[i] != w[i]){
      return false;
    }
  }

  for(char c : unpositioned){
    if(w.find(c) == -1){
      return false;
    }
  }

  return true;
}

void resultsMatrix::updateSet(int result, std::string prevWord){

  std::vector<int> rV = getResultV(result);

  std::vector<char> positioned;
  std::vector<char> unpositioned;

  //Sacar las letras posicionadas y no posicionadas

  for(int i = 0; i < prevWord.length(); i++){
    if(rV[i] == 2){
      positioned.push_back(prevWord[i]);
    }else{
      positioned.push_back(0);
      if(rV[i] == 1){
        unpositioned.push_back(prevWord[i]);
      }
    }
  }

  for(auto it = v_.begin(); it != v_.end();){
    if(!validWord(positioned, unpositioned, *it)){
      v_.erase(it);
    }else{
      ++it;
    }
  }
  calcMatrix();
}

float resultsMatrix::wordEntropy(std::string w){
  
  std::array<int,243> counts = {0};
  int wIdx = getIndex(w);

  for(int i = 0; i < v_.size(); i++){
    int r = m_[wIdx][i];
    counts[r]++;
  }

  float entropy = 0;
  for (int i = 0; i < 243; i++) {
    if (counts[i] > 0) {
      float p = (float)counts[i] / v_.size();
      entropy += p * (-log2f(p));
    }
  }
  return entropy;
}

std::string resultsMatrix::chooseBestWord(){
  float bestEntropy = 0;
  std::string retVal;
  for(std::string w : v_){
    float entropy = wordEntropy(w);

    if(entropy > bestEntropy){
      bestEntropy = entropy;
      retVal = w;
    }
  }

  return retVal;
}

