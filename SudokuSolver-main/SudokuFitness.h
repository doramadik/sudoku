
/*
* This class is the concrete implementation of the Fitness interface
* This class represents a SudokuFitess that will be used calculate and contain
* the fitness value of a Sudoku puzzle
*/

#pragma once
#include "Fitness.h"
#include <vector>

using namespace std;

class Sudoku;

class SudokuFitness : public Fitness
{
public:
//--------------------------------------------------------------
//                  CONSTRUCTORS & DESTRUCTOR
//--------------------------------------------------------------
   //default constructor
   SudokuFitness();
   
   //destructor
   ~SudokuFitness();

//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
	/*
	* function to calculate the fitness of a Sudoku puzzle
	* parameters:
	*	+ Puzzle: a Sudoku puzzle to calculate it's fitness 
	* return: an integer value as a fitness value of a Sudoku puzzle (0 being the best fit fitness score)
	*/
   int howFit(Puzzle&) override;

private:
   /*
	* function to scan all the rows in the row major order of the Sudoku grid to find duplicates
	* once there is a duplicate, the fitness score will increase by one and so on
	* parameters:
	* return: an integer value as a fitness value of the rows 
	*/
   int scanRow(Sudoku&);

   /*
	* function to scan all the columns in the column major order of the Sudoku grid to find duplicates
	* once there is a duplicate, the fitness score will increase by one and so on
	* parameters:
	* return: an integer value as a fitness value of the columns
	*/
   int scanColumn(Sudoku&);

   /*
	* function to scan all the 3x3 subblocks(9 in total) of the Sudoku grid to find duplicates
	* once there is a duplicate, the fitness score will increase by one and so on
	* parameters:
	* return: an integer value as a fitness value of the sub blocks
	*/
   int scanBlock(Sudoku&);


//--------------------------------------------------------------
//                        VARIABLES
//--------------------------------------------------------------
   vector< vector<int> > grid;      //the 9x9 grid representation of a Sudoku puzzle

};

