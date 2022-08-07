

/*
* This Sudoku class holds the representation of a Sudoku puzzle, which consists of
* a 2D vector of size 9x9, and the following instance methods and variables below.
* This class also implements the Puzzle interface
*/

#pragma once
#include <vector>
#include "Puzzle.h"
#include "SudokuFitness.h"
#include "SudokuOffSpring.h"

using namespace std;

class Sudoku : public Puzzle
{
   public:
//--------------------------------------------------------------
//                  CONSTRUCTORS & DESTRUCTOR
//--------------------------------------------------------------
   //default contructor
   Sudoku();
   //destructor
   ~Sudoku();

//--------------------------------------------------------------
//                       OPERATORS OVERLOAD
//--------------------------------------------------------------
   /*
   * operator that takes other Sudoku object to compare
   * pre-condition: sudoku puzzle and the comparison sudoku puzzle objects valid
   * post-condition: compare if this sudoku fitness < other sudoku fitness
   * return: true if comparison process finish
   */
   bool operator<(const Sudoku& other) const;

   /*
   * operator that takes other Sudoku object to compare
   * pre-condition: sudoku puzzle and the comparison sudoku puzzle objects valid
   * post-condition: compare if this sudoku fitness > other sudoku fitness
   * return: true if comparison process finish
   */
   bool operator>(const Sudoku& other) const;

//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------

   /*
	* function to set the fitness of a Sudoku puzzle
	* pre-condition: a Sudoku puzzle is declared and initialized
	* post-condition: the calling Sudoku puzzle has an associated fitness score
	* return: true if the operation was successful, false otherwise
	*/
   bool setFit() override;

   /*
	* function to set the 9x9 grid_ representation of a Sudoku puzzle
	* parameters:
	*	+ vector< vector<int> >: the 2D grid representation of a Sudoku puzzle
	* pre-condition: a Sudoku puzzle is declared 
	* post-condition: grid_ variable is set to the 2D vector passed in 
	* return: true if the operation was successful, false otherwise
	*/
   bool setGrid(vector< vector<int> >);

   /*
	* function to set the original_, which is the ancestral Sudoku puzzle grid
	* parameters:
	*	+ vector< vector<int> >: the 2D grid representation of a Sudoku puzzle
	* pre-condition: a Sudoku puzzle is declared
	* post-condition: original_ variable is set to the 2D vector passed in
	* return: true if the operation was successful, false otherwise
	*/
   bool setOriginal(vector< vector<int> >);

   /*
   * function to get the fitness score of a Sudoku puzzle
   * pre-condition: a Sudoku puzzle is declared and initialized
   * return: an integer value representing the fitness score of a Sudoku puzzle
   */
   int getFit() const override;

   /*
	* function to get the 9x9 grid_ of a Sudoku puzzle
	* pre-condition: a Sudoku puzzle is declared and initialized
	* return: the 9x9 grid_ of a Sudoku puzzle
	*/
   vector< vector<int> >& getGrid();

   /*
	* function to get the 9x9 original_ ancestral grid of a Sudoku puzzle
	* pre-condition: a Sudoku puzzle is declared and initialized
	* return: the 9x9 original_ ancestral grid of a Sudoku puzzle
	*/
   vector< vector<int> >& getOriginal();

   /*
   * function to create an off spring of a Sudoku puzzle for genetic evolution purposes
   * parameters:
   *	+ double: a double value representing the mutation rate in the off spring
   * pre-condition: a Sudoku puzzle is declared and initialized
   * return: an SudokuOffSpring object representing an off spring of a Sudoku parent object
   */
   SudokuOffSpring createOffSpring(double);

   /*
   * function to print the 9x9 grid of a Sudoku puzzle
   * pre-condition: a Sudoku puzzle is declared and initialized
   */
   void printGrid() const;


   private:
   /*
	* function help print out a Sudoku puzzle object (concrete implementation of the interface Puzzle)
	* pre-condition: a Sudoku puzzle is declared and initialized
	* post-condition: none
	* return: true if the operation was successful, false otherwise
	*/
   bool outputHelper() const override;

   /*
	* function help initialize a Sudoku puzzle object (concrete implementation of the interface Puzzle)
	* parameter:
	*  + istream&: the input stream object
	* pre-condition: none
	* post-condition: a Sudoku puzzle object is initialized
   * method called: Sudoku::setFit()
	* return: true if the operation was successful, false otherwise
	*/
   bool inputHelper(istream& in) override;

//--------------------------------------------------------------
//                        VARIABLES
//--------------------------------------------------------------
   SudokuFitness fitness_;     //SudokuFitness object that determine the Sudoku fitness score
   SudokuOffSpring offSpring;    //SudokuOffSpring object creates an offspring for a Sudoku object
   vector< vector<int> > grid_;     //2D vector representing a 9x9 Sudoku grid 
   vector< vector<int> > original_;    //the ancestral Sudoku puzzle grid

};