
/*
* The Reproduction interface is a template for any puzzle that will implement
* the makeOffSpring function to create an off spring version based on the parent
* puzzle. The function mutate will also be implemented by concrete classes to mutate
* the off spring of a puzzle (in order to use Genetic Programming method to find a solution to
* a puzzle).
*/

#pragma once
#include "Puzzle.h"

using namespace std;

class Reproduction
{
public:
//--------------------------------------------------------------
//                        FUNCTIONS
//--------------------------------------------------------------
	/*
	* the method create an offspring of a puzzle parent
	* parameters:
	*	+ Puzzle: the parent puzzle that needs to be used to to make an off spring off of
	* pre-condition: Puzzle must be a valid and non-abstract Puzzle type (e.g. Sudoku puzzle)
	* post-condition: an off spring will be created based on the parent puzzle
	* return: an off spring created from the parent puzzle
	*/
	virtual Reproduction& makeOffSpring(Puzzle&, double) = 0;
	
protected:

	/*
	* function to mutate an offspring of a puzzle parent by changing each element of parent with a random value
	* using probability passed in parameter
	* pre-condition: makeOffSpring has produced a valid offspring that is mutable (have grind with unfixed value)
	* post-condition: an off spring will be mutated
	* return: true if the operation was successful, false otherwise
	*/
	virtual bool mutate(double) = 0;
};