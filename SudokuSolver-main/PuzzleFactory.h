

/*
* The PuzzleFactory interface is a template that is used to create a puzzle from a puzzle offspring
* The concrete classes are required to implement the createPuzzle(Reproduction&) method.
*/

#pragma once
#include "SudokuOffSpring.h"

class PuzzleFactory
{
	public:
//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
	/*
	* function to make a puzzle object (the actual type of the puzzle will be based on the implementing child classes)
	* parameters:
	*	+ Reproduction: the offspring that needs to be used to to make a puzzle
	* pre-condition: a offspring must be a valid concrete type and available to be turned into a puzzle
	* post-condition: a puzzle will be created (e.g. Sudoku puzzle)
	* return: a puzzle of type of a concrete class (e.g. Sudoku puzzle)
	*/
	virtual Puzzle& createPuzzle(Reproduction&) = 0;
};