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
  
  auto start = chrono::high_resolution_clock::now();

  resultsMatrix mtx(readWords("../words/allowed_words.txt"));
  vector<string> possible = readWords("../words/possible_words.txt");
  
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

  cout << "Done in: " << duration.count() / 1000.0 << "ms" << endl << endl;

  string solution = possible[rand() % possible.size()];
  string guess;
  cout << "-- GUESSING PROCESS--" << endl;
  cout << "Word to solve: " << solution << endl << endl;
  while(guess != solution){

    cout << "Number of words: " << mtx.getNPos() << endl;
    
    if(mtx.getNPos() == 0){
      cerr << "ERROR: No possible words left" <<endl;
      break;
    }

    if(mtx.getNPos() == 1){
      guess = mtx.getFirstValidWord();
      cout << "Correct guess: " << guess << endl;
      break;
    }

    cout << "Choosing the best word..." << endl;


    start = chrono::high_resolution_clock::now();

    guess = mtx.chooseBestWord();

    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end-start);

    cout << "Time to choose: " << duration.count() / 1000.0 << " milliseconds" << endl;

    cout << "Chosen word: " << guess << endl << endl;
    
    mtx.updateSet(mtx.getResult(solution,guess), guess);
  }
  
  return 0;
}
