#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "sudokuSolver.hpp"

int main(int argc, char** argv)
{
	std::string fileName = argc == 1 ? "sudoku.txt" : argv[1];
	SudokuSolver::Sudoku sudoku;

	std::ifstream stream(fileName);
	if (!stream.good())
		return EXIT_FAILURE;

	try
	{
		for (int row = 0; row < 9; row++)
			for (int col = 0; col < 9; col++)
				stream >> sudoku.grid[row][col];

		SudokuSolver::solve(sudoku).print();
	}
	catch (std::exception e)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}