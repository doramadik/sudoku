

/*
* This class is the concrete implementation of the Reproduction interface
* This class represents a SudokuOffSpring that will be used to represent a 
* SudokuOffSpring object that is created from a Sudoku parent. Each SudokuOffSpring
* object is then mutated and returned as new Sudoku puzzles in the new generations.
*/

#include <random>
#include "SudokuOffSpring.h"
#include "Sudoku.h"

//default constructor
SudokuOffSpring::SudokuOffSpring()
{}


//destructor
SudokuOffSpring::~SudokuOffSpring()
{}


/*
* function to make an offspring of a Sudoku puzzle parent
* parameters:
*	+ Puzzle: the parent Sudoku puzzle that needs to be used to to make an off spring off of
* pre-condition: Sudoku puzzle must exist
* post-condition: SudokuOffSpring will be created and mutated 
* return: a SudokuOffSpring object
*/
Reproduction& SudokuOffSpring::makeOffSpring(Puzzle& parent, double probability) 
{
   //cast to Sudoku object
   Sudoku sudokuParent = dynamic_cast<Sudoku&>(parent);

   //copy parent's original and grid value to the child SudokuOffSpring
   original_ = sudokuParent.getOriginal();
   grid_ = sudokuParent.getGrid();

   //mutate each grind's elements of the child
   mutate(probability);

   return *this;
}


/*
* function to mutate an offspring of a Sudoku puzzle parent
* parameters:
*	+ double: mutation rate for the off spring Sudoku puzzle
* pre-condition: makeOffSpring has produced a valid off spring that is mutable
* post-condition: an off spring will be mutated
* return: true if the operation was successful, false otherwise
*/
bool SudokuOffSpring::mutate(double probability)
{
   //run through the offspring 9x9 grid
   for(int x = 0; x < 9; x++) {
      for(int y = 0; y < 9; y++) {

         //run through original 2d vector to compare
         //set random value for elemet only if the element is not fixed
         if(original_[x][y] == 0) {   

            double randomP = (rand() % 101) / 100.0;  //random probability

            //set value at grid_[x][y] with a random number if random probability < probability
            if (randomP < probability) {
               int num = (rand() % 9) + 1;
               grid_[x][y] = num;
            }
         }
      }
   }
	return true;
}


/*
* function to get the 9x9 grid_ of a Sudoku puzzle
* pre-condition: a Sudoku puzzle is declared and initialized
* post-condition: none
* return: the 9x9 grid_ of a Sudoku puzzle
*/
vector< vector<int> >& SudokuOffSpring::getGrid()
{
	return grid_;
}


/*
* function to get the 9x9 original_ ancestral grid of a Sudoku puzzle
* pre-condition: a Sudoku puzzle is declared and initialized
* post-condition: none
* return: the 9x9 original_ ancestral grid of a Sudoku puzzle
*/
vector< vector<int> >& SudokuOffSpring::getOriginal()
{
	return original_;
}


/*
* function to print the 9x9 grid of a SudokuOffSpring puzzle
* pre-condition: a SudokuOffSpring puzzle is declared and initialized
* post-condition: none
* return: none
*/
void SudokuOffSpring::printOffSpring()
{
	cout << "+-------+-------+-------+" << endl;
	for(int x = 0; x <=8; x++ ){
		cout << "| ";

		for(int y = 0; y <= 8; y++) {
			cout << grid_[x][y] << " ";

			if(y % 3 == 2) {
				cout << "| ";
			}
		}
		
		cout << endl;
		if(x % 3 == 2) {
			cout << "+-------+-------+-------+" << endl;
		}
	}
}
