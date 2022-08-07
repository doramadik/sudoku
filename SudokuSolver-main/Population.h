

/*
* This Population interface represents a population of puzzles. A population of puzzles consists of atleast one puzzle
* in which the process of evolution for Genetic Programming will take place. The best fit 10% puzzles in the population will 
* be chosen for continuing evolution through genetically mutating those best fit puzzles off spring to create a new population of new
* generation puzzles.
* This interface is to be implemented by a valid concrete population class (e.g. SudokuPopulation)
* The method(s) below are to be implemented by concrete classes.
*/

#pragma once
#include "Puzzle.h"

using namespace std;

class Population
{

public:
//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
	/*
	* function create a population of puzzles (to be implemted by concrete classes like SudokoPopulation and Sudoku)
	* parameters:
	*	+ Puzzle&: the ancestral puzzle to start the population with
	*	+ int: the maximum amount of puzzles in the population
	*	+ double: the mutation rate (used for genetic evolution)
	* pre-condition: a concrete puzzle (e.g. Sudoku) is declared and initialized
	* post-condition: size_ of the population = int, a population of puzzles is created 
	* return: true if the operation was sucessful, false otherwise
	*/
	virtual bool createPopulation(Puzzle&, int, double) = 0;

	/*
	* function create a new generation of puzzles 
	* parameters:
	*	+ bool&: used to check if a solution is found (stop genetic evolution process if found)
	* pre-condition: a population has been created
	* post-condition: current population of puzzles will now be the new generation that has just been created by this function
	* return: true if the operation was sucessful, false otherwise
	*/
	virtual bool createNewGen(bool&) = 0;

	/*
	* function to find the best fit puzzle 
	* pre-condition: population size_ not 0
	* post-condition: none
	* return: an integer value representing the fitness score of the best fit puzzle
	*/
	virtual int bestFit() = 0;

	/*
	* function to eliminate the bad puzzles (higher fitness score) and only keeping 10% of the best fit puzzles (lower fitness score)
	* pre-condition: population size_ not 0
	* post-condition: population is now reduced to only 10% of only the best fit puzzles
	* return: true if the operation was sucessful, false otherwise
	*/
	virtual bool cull() = 0;
	

	protected:
//--------------------------------------------------------------
//                        VARIABLES
//--------------------------------------------------------------
	int size_;			//the size_ of the current population
	int total_population_;		//the maximum capacity that a population can hold
};