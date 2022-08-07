

/*
* This class is the concrete implementation of the Population interface
* This class represents a SudokuPopulation that will be used to represent a
* population of Sudoku puzzles. A population of Sudoku will consist of the current
* population and the new population. Each new population will override the old population
* to represent the best generation/population after each iteration of evolution.
*/

#pragma once
#include "Population.h"
#include "Sudoku.h"
#include "SudokuFactory.h"

using namespace std;
class SudokuPopulation : public Population
{
public:
//--------------------------------------------------------------
//                  CONSTRUCTORS & DESTRUCTOR
//--------------------------------------------------------------
   //default contructor
	SudokuPopulation();

	//destructor 
	~SudokuPopulation();

//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
	/*
	* function create a population of Sudoku puzzles 
	* parameters:
	*	+ Puzzle&: the ancestral Sudoku puzzle to start the population with
	*	+ int: the maximum amount of Sudoku puzzles in the population
	*	+ double: the mutation rate (used for genetic evolution)
	* pre-condition: a Sudoku puzzle is declared and initialized
	* post-condition: size_ of the population = int, a population of Sudoku puzzles is created
	* return: true if the operation was sucessful, false otherwise
	*/
	bool createPopulation(Puzzle&, int, double) override;

	/*
	* function create a new generation of Sudoku puzzles
	* parameters:
	*	+ bool&: used to check if a solution is found (stop genetic evolution process if found)
	* pre-condition: a Sudoku population has been created
	* post-condition: current Sudoku population of Sudoku puzzles will now be the new generation that has just been created 
	* return: true if the operation was sucessful, false otherwise
	*/
	bool createNewGen(bool&) override;

	/*
	* function to find the best fit Sudoku puzzle
	* pre-condition: population size_ not 0
	* post-condition: none
	* return: an integer value representing the fitness score of the best fit Sudoku puzzle
	*/
	int bestFit() override;

	/*
	* function to find the best individual Sudoku puzzle
	* pre-condition: population size_ not 0
	* post-condition: none
	* return: the best fit Sudoku puzzle
	*/
	Sudoku& bestIndividual();

	/*
	* function to eliminate the bad Sudoku puzzles (higher fitness score) and only keeping 10% of the best fit Sudoku puzzles (lower fitness score)
	* pre-condition: population size_ not 0
	* post-condition: population is now reduced to only 10% of only the best fit Sudoku puzzles
	* return: true if the operation was sucessful, false otherwise
	*/
	bool cull() override;

	/*
	* function to print the size of the current Sudoku population
	* pre-condition: population valid
	* post-condition: none
	* return: none
	*/
	void getSize() const;

	/*
	* function print out all the Sudoku puzzles in the current population
	* pre-condition: population size_ not 0

	*/
	void printPopulation();
	
private:
	vector< vector<int> > orginal_;		//the ancestral Sudoku puzzle grid
	double probability;						//the mutation probability (used for genetic mutation)
	SudokuFactory factory;					//the factory for create new Sudoku puzzles
	vector<Sudoku> new_population_;		//the current Sudoku population
	vector<Sudoku> ten_percent_;			//the 10% of the best fit Sudoku puzzle in the current population
};

