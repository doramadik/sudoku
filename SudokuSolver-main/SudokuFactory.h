

/*
* This class is the concrete implementation of the PuzzleFactory interface
* This class represents a SudokuFactory that will be used to make Sudoku puzzles
*/

#pragma once
#include "PuzzleFactory.h"
#include "Sudoku.h"
#include "SudokuOffSpring.h"

using namespace std;

class SudokuFactory : PuzzleFactory
{
	public:
//--------------------------------------------------------------
//                  CONSTRUCTORS & DESTRUCTOR
//--------------------------------------------------------------
	//default constructor
	SudokuFactory();

	//destructor
	~SudokuFactory();	


//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
	/*
	* function to make a puzzle object (the actual type of the puzzle will be based on the implementing child classes)
	* in this case, the puzzle that will be made is a Sudoku puzzle
	* parameters:
	*	+ Reproduction: the offspring that needs to be used to to make a Sudoku puzzle
	* pre-condition: a offspring must be a valid concrete type and available to be turned into a Sudoku puzzle
	* post-condition: a Sudoku puzzle will be created 
	* return: a Sudoku puzzle 
	*/
	Puzzle& createPuzzle(Reproduction&) override;
};

