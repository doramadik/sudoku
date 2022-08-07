#include "GeneticAlgorithm.h"


/*
* This driver will be responsible for running the program by invoking a GeneticAlgorithm 
* object and run the program using the object. There will be two input taken from the command line
* an int value representing the population size and an int value representing the number of generation
* to perform genetic evolution on finding the most fit (solution) to the a sudoku puzzle.
* The initial sudoku board will also be input in using cin. 
*/

#include <cctype>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
   //notice the missing input data
   if(argc < 3 ) {
      cout << "Please input population size and maxinum number of generation! " << endl;
      abort();
   
   //ignore all the other extra input in command line argument, then process
   } else if (argc > 3) {
      cout << "Extra Data will be ignored. " << endl << endl;

   }

   //store command line argument data
   double probability = 0.03;
   int population_size = stoi(argv[1]);
   int max_generation = stoi(argv[2]);

   
   Sudoku mySudoku;
   cout << "Please input Sudoku: ";
   cin>> mySudoku;   //input sudoku
   cout << endl;

   //GA to process the GA interations
   GeneticAlgorithm GA;
   GA.processSudoku(mySudoku, population_size, max_generation, probability);
   
   GA.printSudoku();    //printout the best solution 
   GA.getBestFitness(); //printout the best solution fitness

}
