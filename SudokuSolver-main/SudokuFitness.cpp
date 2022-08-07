
/*
* This class is the concrete implementation of the Fitness interface
* This class represents a SudokuFitess that will be used calculate and contain
* the fitness value of a Sudoku puzzle
*/

#include "SudokuFitness.h"
#include "Sudoku.h"


//default constructor
SudokuFitness::SudokuFitness()
{}


//destructor
SudokuFitness::~SudokuFitness()
{}


/*
* function to scan all the rows in the row major order of the Sudoku grid to find duplicates
* once there is a duplicate, the fitness score will increase by one and so on
* parameters:
*	+ Sudoku: a Sudoku puzzle to calculate it's fitness
* return: an integer value as a fitness value of the rows 
*/
int SudokuFitness::scanRow(Sudoku& s)
{
    int duplicate = 0;      //count duplicate in all rows
    
    //x is row index
    for(int x = 0; x <= 8; x++) {

        vector<bool> exist(10, false);  //check if values exist in each row

        //y is column index
        for(int y = 0; y <= 8; y++) {  
            int num = grid[x][y];
            
            //increase duplicate number if value already exist
            if(exist[num]) {
              duplicate++;
            } else { 
                exist[num] = true;      //else set value exists and continue
            }
        }
    }
    return duplicate;
}


/*
* function to scan all the columns in the column major order of the Sudoku grid to find duplicates
* once there is a duplicate, the fitness score will increase by one and so on
* parameters:
*	+ Sudoku: a Sudoku puzzle to calculate it's fitness
* return: an integer value as a fitness value of the columns
*/
int SudokuFitness::scanColumn(Sudoku&s)
{
    int duplicate = 0;      //count duplicate in all column

    //y is column index
    for(int y = 0; y <= 8; y++) {

        vector<bool> exist(10, false);      //check if values exist in each column

        //x is row index
        for(int x = 0; x <= 8; x++) {
            int num = grid[x][y];

            //increase duplicate number if value already exist
            if(exist[num]) {
                duplicate++;
            } else { 
                exist[num] = true;      //else set value exists and continue
            }
        }
    }
    return duplicate;
}



/*
* function to scan all the 3x3 subblocks(9 in total) of the Sudoku grid to find duplicates
* once there is a duplicate, the fitness score will increase by one and so on
* parameters:
*	+ Sudoku: a Sudoku puzzle to calculate it's fitness
* return: an integer value as a fitness value of the sub blocks
*/
int SudokuFitness::scanBlock(Sudoku& s)
{
    int duplicate = 0;      //count duplicate in all block

    //x is row index, y is column index
    for(int x = 0; x <= 6; x+=3) {
        for(int y = 0; y <= 6; y+=3) {

            vector<bool> exist(10, false);  //check if values exist in each block

            //z is row index, w is column index
            //row index run from x to x+z
            //column index run from y to y+w
            for(int z = 0; z < 3; z++) {
                for (int w = 0; w < 3; w++) {

                    int row = x+z;      //row index
                    int column = y + w;     //column index 
                    int num = grid[row][column];

                    //increase duplicate number if value already exist
                    if(exist[num]){
                        duplicate++;
                    } else { 
                        exist[num] = true;      //else set value exists and continue
                    }
                }
            }
        }
    }
    return duplicate;
}


/*
* function to calculate the fitness of a Sudoku puzzle
* parameters:
*	+ Puzzle: a Sudoku puzzle to calculate it's fitness 
* return: an integer value as a fitness value of a Sudoku puzzle (0 being the best fit fitness score)
*/
int SudokuFitness::howFit(Puzzle& puzzle)
{
    //cast to Sudoku object
    Sudoku sudoku = dynamic_cast<Sudoku&>(puzzle);
    grid = sudoku.getGrid();    //copy sudoku grid to process
    return scanRow(sudoku) + scanColumn(sudoku) + scanBlock(sudoku);    //total number of duplication 
                                                                        //in Sudoku 2D vector
}
