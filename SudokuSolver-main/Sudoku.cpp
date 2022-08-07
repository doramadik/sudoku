
/*
* This Sudoku class holds the representation of a Sudoku puzzle, which consists of
* a 2D vector of size 9x9, and the following instance methods and variables below.
* This class also implements the Puzzle interface
*/

#include "Sudoku.h"
#include <cctype>
#include <string>

using namespace std;


//default contructor
Sudoku::Sudoku(){
	//initialize all sudoku 2D vetors's elements by 0
	original_.resize(9, vector<int>(9, 0));
	grid_.resize(9, vector<int>(9, 0));
}


//destructor
Sudoku::~Sudoku()
{}


/*
* function to set the original_, which is the ancestral Sudoku puzzle grid
* parameters:
*	+ vector< vector<int> >: the 2D grid representation of a Sudoku puzzle
* pre-condition: a Sudoku puzzle is declared
* post-condition: original_ variable is set to the 2D vector passed in
* return: true if the operation was successful, false otherwise
*/
bool Sudoku::setOriginal(vector< vector<int> > otherOriginal)
{
	original_ = otherOriginal;
	return true;
}


/*
* function to set the 9x9 grid_ representation of a Sudoku puzzle
* parameters:
*	+ vector< vector<int> >: the 2D grid representation of a Sudoku puzzle
* pre-condition: a Sudoku puzzle is declared 
* post-condition: grid_ variable is set to the 2D vector passed in 
* return: true if the operation was successful, false otherwise
*/
bool Sudoku::setGrid(vector< vector<int> > otherGrid)
{
	grid_ = otherGrid;
	return true;
}


/*
* function to set the fitness of a Sudoku puzzle
* pre-condition: a Sudoku puzzle is declared and initialized
* post-condition: the calling Sudoku puzzle has an associated fitness score
* return: true if the operation was successful, false otherwise
*/
bool Sudoku::setFit()
{
	fit_score_ = fitness_.howFit(*this);
	return true;
}


/*
* function to get the fitness score of a Sudoku puzzle
* pre-condition: a Sudoku puzzle is declared and initialized
* return: an integer value representing the fitness score of a Sudoku puzzle
*/
int Sudoku::getFit() const
{
	return fit_score_;
}


/*
* function to get the 9x9 grid_ of a Sudoku puzzle
* pre-condition: a Sudoku puzzle is declared and initialized
* return: the 9x9 grid_ of a Sudoku puzzle
*/
vector< vector<int> >& Sudoku::getGrid()
{
	return grid_;
}


/*
* function to get the 9x9 original_ ancestral grid of a Sudoku puzzle
* pre-condition: a Sudoku puzzle is declared and initialized
* return: the 9x9 original_ ancestral grid of a Sudoku puzzle
*/
vector< vector<int> >& Sudoku::getOriginal()
{
	return original_;
}


/*
* function to create an off spring of a Sudoku puzzle for genetic evolution purposes
* parameters:
*	+ double: a double value representing the mutation rate in the off spring
* pre-condition: a Sudoku puzzle is declared and initialized
* return: an SudokuOffSpring object representing an off spring of a Sudoku parent object
*/
SudokuOffSpring Sudoku::createOffSpring(double probability)
{
	//method return Reproduction&, cast to SudokuOffSpring object
	offSpring = dynamic_cast<SudokuOffSpring&> (offSpring.makeOffSpring(*this, probability));
	return offSpring;
}


/*
* function to print the 9x9 grid of a Sudoku puzzle
* pre-condition: a Sudoku puzzle is declared and initialized
*/
void Sudoku::printGrid() const
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


/*
* pre-condition: Sudoku object valid
* post-condition: printout Sudoku 9x9 grind
* function called: Sudoku::outputHelper
* return: os
*/
ostream& operator<<(ostream& os, const Puzzle& p)
	{
		p.outputHelper();
		return os;
	}



/*
* pre-condition: Sudoku object valid
* post-condition: take input to create Sudoku 9x9 grind
* function called: Sudoku::inputHelper
* return: is
*/
istream& operator>>(istream& is, Puzzle& p)
	{
		p.inputHelper(is);
		return is;
	}


/*
* function help initialize a Sudoku puzzle object (concrete implementation of the interface Puzzle)
* parameter:
*  + istream&: the input stream object
* pre-condition: none
* post-condition: a Sudoku puzzle object is initialized
* method called: Sudoku::setFit()
* return: true if the operation was successful, false otherwise
*/
bool Sudoku::inputHelper(istream& in)
{
	string input = "\0";		//store sudoku string to create sudoku puzzle
	int x = 0,y = 0;	//x is row index, y is column index
	
	in >> input;		

	//add the values for original sudoku 2D vector from input string
	for (int i = 0; i < input.size(); i++) {

		if (isdigit(input[i])) {		//skip all the non-digit characters

			//run through each element in 2D vector to store values
			//continue at row x if y <= 8
			if(y<=8 && x <= 8) {
				original_[x][y] = (int)(input[i])-48;
				y++;

			} else if (y > 8 && x <= 8) {		//go to next row ++x if y > 8
				y = 0;
				original_[++x][y] = (int)(input[i]-48);
				y++;

			} else {
				break;	//break after taking 81 digit character from string
			}				//the rest of the string will be ignored
		}
	}

	grid_ = original_;	//copy value from original to grid to process later
	setFit();

	return true;
}


/*
* function help print out a Sudoku puzzle object (concrete implementation of the interface Puzzle)
* pre-condition: a Sudoku puzzle is declared and initialized
* post-condition: none
* return: true if the operation was successful, false otherwise
*/
bool Sudoku::outputHelper() const
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
	return true;
}


/*
* operator that takes other Sudoku object to compare
* pre-condition: sudoku puzzle and the comparison sudoku puzzle objects valid
* post-condition: compare if this sudoku fitness < other sudoku fitness
* return: true if comparison process finish
*/
bool Sudoku::operator<(const Sudoku& other) const
{
	return fit_score_ < other.fit_score_;
}


/*
* operator that takes other Sudoku object to compare
* pre-condition: sudoku puzzle and the comparison sudoku puzzle objects valid
* post-condition: compare if this sudoku fitness > other sudoku fitness
* return: true if comparison process finish
*/
bool Sudoku::operator>(const Sudoku& other) const
{
	return fit_score_ > other.fit_score_;
}

