

/*
* This Fitness interface represents a fitness of a puzzle. This interface is 
* to be implemented by a valid concrete puzzle fitness class (e.g. SudokuFitness) 
* The method(s) below are to be implemented by concrete classes.
*/

#pragma once
#include "Puzzle.h"

using namespace std;

class Fitness
{
public:
//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
	/*
	* function to calculate the fitness of a puzzle 
	* parameters:
	*	+ Puzzle: a puzzle to calculate it's fitness (the puzzle must be a concrete implementation of a puzzle (e.g. Sudoku puzzle)
	* return: an integer value as a fitness value of a puzzle (0 being the best fit fitness score)
	*/
	virtual int howFit(Puzzle&) = 0;
};