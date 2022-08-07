

/*
* This class is the concrete implementation of the Population interface
* This class represents a SudokuPopulation that will be used to represent a
* population of Sudoku puzzles. A population of Sudoku will consist of the current
* population and the new population. Each new population will override the old population
* to represent the best generation/population after each iteration of evolution.
*/

#include "SudokuPopulation.h"
#include <algorithm>

using namespace std;

//default contructor
SudokuPopulation::SudokuPopulation()
{}


//destructor 
SudokuPopulation::~SudokuPopulation()
{}


/*
* function create a population of Sudoku puzzles 
* parameters:
*	+ Puzzle&: the ancestral Sudoku puzzle to start the population with
*	+ int: the maximum amount of Sudoku puzzles in the population
*	+ double: the mutation rate (used for genetic evolution)
* pre-condition: a Sudoku puzzle is declared and initialized
* post-condition: size_ of the population = int, a population of Sudoku puzzles is created
* return: true if the operation was sucessful, false otherwise
*/
bool SudokuPopulation::createPopulation(Puzzle& s, int populationSize, double prob)
{
	//set population size, probability and save original sudoku pro comparision
   total_population_ = populationSize;
	orginal_ = dynamic_cast<Sudoku&>(s).getGrid();
   probability = prob;

	//create sudoku population with random solutions
	for (int i = 0; i < total_population_; i++) {

		Sudoku newSudoku = dynamic_cast<Sudoku&>(s);

		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {

				//set random value for new sudoku's element at grind[x][y]
				//if it's not at fixed position (element = 0 at original sudoku grind)
				if (orginal_[x][y] == 0) {

					newSudoku.getGrid()[x][y] = (rand() % 9) + 1;
				}
			}
		}

		newSudoku.setFit();		//set fitness for new sudoku
		new_population_.push_back(newSudoku);
	}

   return true;
}


/*
* function create a new generation of Sudoku puzzles
* parameters:
*	+ bool&: used to check if a solution is found (stop genetic evolution process if found)
* pre-condition: a Sudoku population has been created
* post-condition: current Sudoku population of Sudoku puzzles will now be the new generation that has just been created 
* return: true if the operation was sucessful, false otherwise
*/
bool SudokuPopulation::createNewGen(bool& solutionFound)
{

	//stop creating generation when solution with fitness = 0 is found
	if (new_population_[0].getFit() == 0) {

		solutionFound = true;
		return true;
	}

	//number of children will be produced from all parents sudoku to remain population size
	int children = total_population_ - ten_percent_.size();
	int parentIndex = 0;		//paretn sudoku's index
	int maxOffSpring = children/ten_percent_.size();		//max offspring of 1 parent

	//create children for new generation for each sudoku parent in ten_percent_ vector
	for (int i = 0; i < children; i++) {

		//increase parent's index if the parent create max offspring
		if (i != 0 && i % (maxOffSpring) == 0) {

			if(parentIndex < ten_percent_.size()) {  
				parentIndex++;
			}
		}
     
	  //create parent sudoku's offspring
		SudokuOffSpring sos = ten_percent_[parentIndex].createOffSpring(probability);

		//create children sudoku from the sudoku offspring
      Sudoku temp = dynamic_cast<Sudoku&>(factory.createPuzzle(sos));
		new_population_.push_back(temp);		//add children sudoku to new generation
	}

	//sort the population by fitness score
	sort(new_population_.begin(), new_population_.end());

   return true;
}


/*
* function to eliminate the bad Sudoku puzzles (higher fitness score) and only keeping 10% of the best fit Sudoku puzzles (lower fitness score)
* pre-condition: population size_ not 0
* post-condition: population is now reduced to only 10% of only the best fit Sudoku puzzles
* return: true if the operation was sucessful, false otherwise
*/
bool SudokuPopulation::cull()
{
	//sort the population by fitness score
	sort(new_population_.begin(), new_population_.end());

	//stop culling the generation when solution with fitness = 0 is found
	if (new_population_[0].getFit() == 0) {
		return false;
	}

	//number of sudoku will be kept in population
	int culledSize = new_population_.size() * 10 / 100;

	new_population_.resize(culledSize);		//cull population, discard worst 90%
	ten_percent_ = new_population_;			//copy the remaining 

   return true;
}


/*
* function to find the best fit Sudoku puzzle
* pre-condition: population size_ not 0
* post-condition: none
* return: an integer value representing the fitness score of the best fit Sudoku puzzle
*/
int SudokuPopulation::bestFit()
{
	//sort the population by fitness score
	sort(new_population_.begin(), new_population_.end());

   return new_population_[0].getFit();		//return the fitness of the 1st one in population
}


/*
* function to find the best individual Sudoku puzzle
* pre-condition: population size_ not 0
* post-condition: none
* return: the best fit Sudoku puzzle
*/
Sudoku& SudokuPopulation::bestIndividual()
{
	//sort the population by fitness score
	sort(new_population_.begin(), new_population_.end());

	return new_population_[0];		//return the 1st sudoku with smallest fitness in population
}


/*
* function print out all the Sudoku puzzles in the current population
* pre-condition: population size_ not 0
*/
void SudokuPopulation::printPopulation()
{
	for(int i = 0; i < total_population_; i++) {

		new_population_[i].printGrid();
		cout << endl;
	}
}


/*
* function to print the size of the current Sudoku population
* pre-condition: population valid
* post-condition: none
* return: none
*/
void SudokuPopulation::getSize() const
{
   cout << new_population_.size() << endl;
}