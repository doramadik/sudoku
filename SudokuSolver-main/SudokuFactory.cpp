

/*
* This class is the concrete implementation of the PuzzleFactory interface
* This class represents a SudokuFactory that will be used to make Sudoku puzzles
*/

#include "SudokuFactory.h"

using namespace std;

//default constructor
SudokuFactory::SudokuFactory()
{}


//destructor
SudokuFactory::~SudokuFactory()
{}


/*
* function to make a puzzle object (the actual type of the puzzle will be based on the implementing child classes)
* in this case, the puzzle that will be made is a Sudoku puzzle
* parameters:
*	+ Reproduction: the offspring that needs to be used to to make a Sudoku puzzle
* pre-condition: a offspring must be a valid concrete type and available to be turned into a Sudoku puzzle
* post-condition: a Sudoku puzzle will be created 
* return: a Sudoku puzzle 
*/
Puzzle& SudokuFactory::createPuzzle(Reproduction& offSpring)
{
	//cast to SudokuOffSpring object
	SudokuOffSpring sOffSpring = dynamic_cast<SudokuOffSpring&>(offSpring);

	static Sudoku newSudoku;

	//copy SudokuOffSpring original and grid vector to new Sudoku object
	newSudoku.setGrid(sOffSpring.getGrid());
	newSudoku.setOriginal(sOffSpring.getOriginal());
	newSudoku.setFit();

	return newSudoku;		//return the new Sudoku object
}
