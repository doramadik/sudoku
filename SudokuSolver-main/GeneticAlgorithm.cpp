

/*
* This GeneticAlgorithm class ask the Population for the bestFitness, halting iterations if a solution 
* has been found or if the maximum number of generations limit has been reached, command the Population 
* to cull 90% of its Puzzles, and command the Population to reproduce a newGeneration.
* It contains the SudokuPopulation object, an original 9x9 Sudoku grid and the solution or best result
* of the Sudoku.
*/

#include "GeneticAlgorithm.h"


//default constructor
GeneticAlgorithm::GeneticAlgorithm()
{}

//destructor
GeneticAlgorithm::~GeneticAlgorithm()
{}


/*
* takes input datas in parameter, use them to to determine original Sudoku, population size and maximum 
* number of generation will be created. The method stores the orginal input sudoku, create a population of 
* sudoku solutions with different generation to find the final result
* pre-condition: input datas have to be valid
* post-condition: find the correct solution for Sudoku or the best solution with lowest fitness score
* function called: GeneticAlgorithm::processGenerations()
* return: true if process completed, false otherwise
*/
void GeneticAlgorithm::processSudoku(Sudoku& s, int size, int maxGen, double prob)
{
    population_size_ = size;
    generation_number_ = maxGen;
    probability_ = prob;
    solutionFound = false;
    original_sudoku_ = s;


    //create population
    population_.createPopulation(original_sudoku_, population_size_, probability_);
    processGenerations();       //creates generations to find best solution

    //store the best result
    result_sudoku_ = population_.bestIndividual();
}


/*
* The method command the Population to cull 90% of its Puzzles and reproduce a newGeneration until
* the maximum number of generation is reached or correct solution is found
* pre-condition: original sudoku and population are valid
* post-condition: the result_sudoku will br determined after the process is done
*/
void GeneticAlgorithm::processGenerations()
{
    int countGeneration = 0;    //count the generation processed

    //run until reach the maximum number of generation or the solution is found with fitness = 0
    while (countGeneration < generation_number_ && !solutionFound) {
        
        population_.cull();     //delete 90% worst sudoku, keep 10% sudoku that have best fitness scores
        population_.createNewGen(solutionFound);    //create new generation with the remaining 10%
        countGeneration++;
    }
}


/*
* print out the 9x9 grid result solution of input sudoku
* pre-condition: input sudoku valid
* post-condition: printout 9x9 grid of sudoku 
*/
void GeneticAlgorithm::printSudoku()
{
    result_sudoku_.printGrid();
    cout << endl;
}


/*
* print out fitness score of the result solution
* pre-condition: the result solution valid
* return: true if process completed, false otherwise
*/
bool GeneticAlgorithm::getBestFitness()
{
    cout << "Best fitness score: " << result_sudoku_.getFit() << endl;
    return true;
}
