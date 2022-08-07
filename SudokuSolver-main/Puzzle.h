

/*
* The Puzzle interface represents a puzzle abstract that can be implemented by any
* concrete puzzle classes. If a concrete class like Sudoku implements this interface, 
* it will have it's version of a Sudoku puzzle. The methods below are to be implemented by 
* the concrete classes.
*/

#pragma once
#include <iostream>

using namespace std;

class Puzzle
{
public:
//--------------------------------------------------------------
//                       OPERATORS OVERLOAD
//--------------------------------------------------------------
	/*
	* this operator is the abstract standardised way of printing out a puzzle, concrete way of printing out a puzzle
	* will be implemented by concrete puzzle classes (e.g. Sudoku puzzle)
	* parameter:
	*  + ostream&: the output stream object
	*  + Puzzle: the puzzle to be printed out
	*/
   friend ostream& operator<<(ostream& out, const Puzzle& p);

   /*
	* this operator is the abstract standardised way of taking in a puzzle as input from the console, concrete ways of
	* taking in the input and constructing a puzzle will be implemented by concrete classes
	* parameter:
	*  + istream&: the input stream object
	*  + Puzzle: the puzzle to be taken in and constructed to the appropriate puzzle object
	*/
   friend istream& operator>>(istream& in, Puzzle& p);

   /*
	* this operator compares two puzzles by their fitness scores
	* parameter:
	*  + Puzzle&: the puzzle to be compared with
	* pre-condition: other is not empty
	* post-condition: none
	* return: true if the left hand side puzzle is smaller than the right hand side puzzle in 
	* terms of their fitness scores
	*/
   bool operator<(const Puzzle& other) const;

   /*
	* this operator compares two puzzles by their fitness scores
	* parameter:
	*  + Puzzle&: the puzzle to be compared with
	* pre-condition: other is not empty
	* post-condition: none
	* return: true if the left hand side puzzle is greater than the right hand side puzzle in
	* terms of their fitness scores
	*/
   bool operator>(const Puzzle& other) const;


//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
	/*
	* function to set the fitness score of a puzzle
	* parameter:
	* pre-condition: a puzzle is not empty
	* post-condition: fit_score_ is set to a value other than the defaulted value
	* return: true if the operation was successful, false otherwise
	*/
   virtual bool setFit() = 0;

   /*
	* function to return the fitness score of a puzzle
	* pre-condition: a puzzle is not empty
	* post-condition: none
	* return: an integer value of a puzzle fitness score
	*/
   virtual int getFit() const = 0;
	

protected:

   /*
	* function to help the output stream to print out the puzzle
	* pre-condition: the puzzle must exist
	* post-condition: none
	* return: true if the operation was successful, false otherwise
	*/
   virtual bool outputHelper() const = 0;

   /*
	* function to help the input stream to take in the puzzle via the console and
	* construct the puzzle accordingly 
	* pre-condition: none
	* post-condition: a puzzle is constructed accordingly
	* return: true if the operation was successful, false otherwise
	*/
   virtual bool inputHelper(istream& in) = 0;
      
//--------------------------------------------------------------
//                        VARIABLES
//--------------------------------------------------------------

   //fitness score of a puzzle, this will be changed later by concrete classes
   int fit_score_ = 0;
};