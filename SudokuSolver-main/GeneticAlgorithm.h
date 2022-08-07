

/*
* This GeneticAlgorithm class ask the Population for the bestFitness, halting iterations if a solution 
* has been found or if the maximum number of generations limit has been reached, command the Population 
* to cull 90% of its Puzzles, and command the Population to reproduce a newGeneration.
* It contains the SudokuPopulation object, an original 9x9 Sudoku grid and the solution or best result
* of the Sudoku.
*/

#pragma once
#include "SudokuPopulation.h"

using namespace std;

class GeneticAlgorithm
{
public:
//--------------------------------------------------------------
//                  CONSTRUCTORS & DESTRUCTOR
//--------------------------------------------------------------
	//default constructor
	GeneticAlgorithm();

	//destructor
	~GeneticAlgorithm();

//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
	/*
	* takes input datas in parameter, use them to to determine original Sudoku, population size and maximum 
   * number of generation will be created. The method stores the orginal input sudoku, create a population of 
	* sudoku solutions with different generation to find the final result
	* pre-condition: input datas have to be valid
	* post-condition: find the correct solution for Sudoku or the best solution with lowest fitness score
	* function called: GeneticAlgorithm::processGenerations()
	* return: true if process completed, false otherwise
	*/
	void processSudoku(Sudoku&, int, int, double);

	/*
	* print out the 9x9 grid result solution of input sudoku
	* pre-condition: input sudoku valid
	* post-condition: printout 9x9 grid of sudoku 
	*/
	void printSudoku();

	/*
	* print out fitness score of the result solution
	* pre-condition: the result solution valid
	* return: true if process completed, false otherwise
	*/
	bool getBestFitness();

	/*
	* The method command the Population to cull 90% of its Puzzles and reproduce a newGeneration until
	* the maximum number of generation is reached or correct solution is found
	* pre-condition: original sudoku and population are valid
	* post-condition: the result_sudoku will br determined after the process is done
	*/
	void processGenerations();

private:
//--------------------------------------------------------------
//                          VARIABLES
//--------------------------------------------------------------
	Sudoku original_sudoku_;			//the original 9x9 grind sudoku
	Sudoku result_sudoku_;				//the result 9x9 grind sudoku with lowest fitness score
	SudokuPopulation population_;		//Sudoku population
	int population_size_;				//store the population size
	int generation_number_;				//maximum number of generations will be created
	double probability_;					//the mutation probability
	bool solutionFound;					//check whether the correct solution is found
};

