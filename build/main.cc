#include "matrix.h"
#include "func.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main(){
  srand(time(0));

  cout << "-- WORDLE SOLVER --" << endl;

  cout << "Reading words and creating matrix..." << endl;
  
  resultsMatrix mtx(readWords("../words/allowed_words.txt"));
  vector<string> possible = readWords("../words/possible_words.txt");
  
  cout << "Done!" << endl << endl;

  string solution = possible[rand() % possible.size()];

  cout << "Choosing the best first word..." << endl;

  auto start = chrono::high_resolution_clock::now();

  string guess = mtx.chooseBestWord();

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end-start);

  cout << "Time to choose: " << duration.count() / 1000.0 << " milliseconds" << endl;

  cout << solution << endl << endl;

  cout << guess << endl << endl;
  

  while(guess != solution){
    mtx.updateSet(mtx.getResult(solution,guess), guess);
    guess = mtx.chooseBestWord();
    cout << guess << endl << endl;
  }

  return 0;
}
