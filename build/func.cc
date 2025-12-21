#include "func.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include <numeric>
/*
 -- FUNCIONES AUXILIARES --
*/

int pow3(int exp){
  int retVal = 1;
  for(int i = 0; i < exp; i++){
    retVal*=3;
  }

  return retVal;
}

std::string vToString(std::vector<int> v){
  std::string retVal = accumulate(v.begin(), v.end(), std::string(),
                          [](const std::string &a, int b) {
                            return a + std::to_string(b); });
  return retVal;
}

std::string clip(std::string s){
  std::string retVal;
  std::copy_if(s.begin(), s.end(), std::back_inserter(retVal), [](char c) { return std::isalpha(c); }); // keeps only letters
  return retVal;
}

std::vector<std::string> readWords(std::string filename){
  std::ifstream f(filename);
  std::vector<std::string> retVal;

  std::string buf;

  while(std::getline(f,buf)){
    retVal.push_back(clip(buf));
  }

  return retVal;
}

std::vector<int> getResultV(int r){
  std::vector<int> retVal;
  for(int i = 0; i < 5;i++){
    int exp = 4-i;
    retVal.push_back( r / pow3(exp) );
    r-=(r/pow3(exp))*pow3(exp);
  }

  return retVal;
}

int getResultInt(std::vector<int> v){
  int retVal = 0;
  
  for(int i = 0; i < v.size(); i++){
    retVal += v[i]*pow(3,4-i);
  }
  
  return retVal;
}


