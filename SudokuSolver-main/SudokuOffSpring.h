
/*
* This class is the concrete implementation of the Reproduction interface
* This class represents a SudokuOffSpring that will be used to represent a 
* SudokuOffSpring object that is created from a Sudoku parent. Each SudokuOffSpring
* object is then mutated and returned as new Sudoku puzzles in the new generations.
*/

#pragma once
#include "Reproduction.h"
#include <vector>

using namespace std;

class SudokuOffSpring : public Reproduction
{
public:
//--------------------------------------------------------------
//                  CONSTRUCTORS & DESTRUCTOR
//--------------------------------------------------------------
   //default constructor
   SudokuOffSpring();

   //destructor
   ~SudokuOffSpring();

//--------------------------------------------------------------
//                        FUNCTIONS
//--------------------------------------------------------------
	/*
	* function to make an offspring of a Sudoku puzzle parent
	* parameters:
	*	+ Puzzle: the parent Sudoku puzzle that needs to be used to to make an off spring off of
	* pre-condition: Sudoku puzzle must exist
	* post-condition: SudokuOffSpring will be created and mutated 
	* return: a SudokuOffSpring object
	*/
   Reproduction& makeOffSpring(Puzzle&, double) override;

   /*
	* function to mutate an offspring of a Sudoku puzzle parent
	* parameters:
	*	+ double: mutation rate for the off spring Sudoku puzzle
	* pre-condition: makeOffSpring has produced a valid off spring that is mutable
	* post-condition: an off spring will be mutated
	* return: true if the operation was successful, false otherwise
	*/
   bool mutate(double) override;

   /*
	* function to get the 9x9 grid_ of a Sudoku puzzle
	* pre-condition: a Sudoku puzzle is declared and initialized
	* post-condition: none
	* return: the 9x9 grid_ of a Sudoku puzzle
	*/
   vector< vector<int> >& getGrid();

   /*
	* function to get the 9x9 original_ ancestral grid of a Sudoku puzzle
	* pre-condition: a Sudoku puzzle is declared and initialized
	* post-condition: none
	* return: the 9x9 original_ ancestral grid of a Sudoku puzzle
	*/
   vector< vector<int> >& getOriginal();

   /*
	* function to print the 9x9 grid of a SudokuOffSpring puzzle
	* pre-condition: a SudokuOffSpring puzzle is declared and initialized
	* post-condition: none
	* return: none
	*/
   void printOffSpring();

private:
   vector< vector<int> > grid_;        //2D vector representing a 9x9 Sudoku grid 
   vector< vector<int> > original_;    //the ancestral Sudoku puzzle grid


};

