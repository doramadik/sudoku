#include "sudokuSolver.hpp"

#include <iostream>
#include <vector>

// public
SudokuSolver::Sudoku::Sudoku(const int grid[9][9])
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			this->grid[row][col] = grid[row][col];
}

void SudokuSolver::Sudoku::print()
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			std::cout << grid[row][col] << (col == 8 ? "\n" : " ");
}

int SudokuSolver::Sudoku::countSolvedCells()
{
	int solvedCellsCount = 0;
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (grid[row][col] != 0) solvedCellsCount++;

	return solvedCellsCount;
}


SudokuSolver::Sudoku SudokuSolver::solve(const Sudoku& sudoku, const Options& options)
{
	// initialize solution grid with given values
	FlipGrid solution(sudoku.grid);

	// generate grid with all valid moves
	FlipGrid validMoves = generateValidMoves(solution);

	if (options.recursive)
		recursiveSolver(solution, validMoves, options);
	else
		stableSolver(solution, validMoves, options);
	
	return solution.grid;
}


// private
SudokuSolver::FlipGrid::FlipGrid(const int grid[9][9])
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			this->grid[row][col] = grid[row][col];
}

int SudokuSolver::FlipGrid::operator()(int row, int col, bool flip) const
{
	if (!flip)
		return grid[row][col];
	else
		return grid[col][row];
}

int& SudokuSolver::FlipGrid::operator()(int row, int col, bool flip)
{
	if (!flip)
		return grid[row][col];
	else
		return grid[col][row];
}


SudokuSolver::FlipGrid SudokuSolver::generateValidMoves(const FlipGrid& solution)
{
	FlipGrid validMoves;
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			for (int value = 0; value < 9; value++)
				if (isValidMove(solution, row, col, value + 1))
					// valid moves for different values are stored as bits
					validMoves(row, col) |= (1 << value);

	return validMoves;
}

bool SudokuSolver::isValidMove(const FlipGrid& solution, int row, int col, int value)
{
	// check if move is valid
	return solution(row, col) == 0                // cell empty
		&& checkRow(solution, col, value, true)   // along horizntal line
		&& checkRow(solution, row, value)         // along vertical line
		&& checkBlock(solution, row, col, value); // within block
}

bool SudokuSolver::checkRow(const FlipGrid& solution, int row, int value, bool flip)
{
	for (int col = 0; col < 9; col++)
		if (solution(row, col, flip) == value) return false;

	return true;
}

bool SudokuSolver::checkBlock(const FlipGrid& solution, int row, int col, int value)
{
	int blockRow = row / 3;
	int blockCol = col / 3;

	for (int iRow = blockRow * 3; iRow < (blockRow + 1) * 3; iRow++)
		for (int iCol = blockCol * 3; iCol < (blockCol + 1) * 3; iCol++)
			if (solution(iRow, iCol) == value) return false;

	return true;
}

bool SudokuSolver::blockSolver(FlipGrid& solution, FlipGrid& validMoves)
{
	bool advanced = false;
	for (int blockRow = 0; blockRow < 3; blockRow++)
		for (int blockCol = 0; blockCol < 3; blockCol++)
			for (int value = 0; value < 9; value++)
			{
				// TODO extract this to a function
				// count possible moves for value in current block
				int count = 0, row, col;
				for (int rowI = blockRow * 3; rowI < (blockRow + 1) * 3; rowI++)
				{
					for (int colI = blockCol * 3; colI < (blockCol + 1) * 3; colI++)
					{
						// check if there is only single valid move for this cell
						if ((validMoves(rowI, colI) == (1 << value)))
						{
							row = rowI;
							col = colI;
							count = -1;
							break;
						}
						else if ((validMoves(rowI, colI) & (1 << value)))
						{
							row = rowI;
							col = colI;
							count++;
						}
					}
					if (count == -1)
						break;
				}

				if (count == 1 || count == -1)
				{
					setValue(solution, validMoves, row, col, value);
					advanced = true;
				}
			}

	return advanced;
}

bool SudokuSolver::rowSolver(FlipGrid& solution, FlipGrid& validMoves, bool flip)
{
	bool advanced = false;
	for (int row = 0; row < 9; row++)
		for (int value = 0; value < 9; value++)
		{
			// check if row has only single valid move for value
			int index = -1;
			for (int col = 0; col < 9; col++)
				if (validMoves(row, col, flip) & (1 << value))
				{
					if (index != -1)
					{
						index = -1;
						break;
					}
					else
						index = col;
				}

			if (index != -1)
			{
				setValue(solution, validMoves, row, index, value, flip);
				advanced = true;
			}
		}

	return advanced;
}

void SudokuSolver::setValue(FlipGrid& solution, FlipGrid& validMoves, int row, int col, int value, bool flip)
{
	// set value to solution
	solution(row, col, flip) = value + 1;
	// remove position from valid moves
	validMoves(row, col, flip) = 0;

	// remove from possible moves horizonal and vertical
	for (int k = 0; k < 9; k++)
	{
		validMoves(row, k, flip) &= (~(1 << value));
		validMoves(k, col, flip) &= (~(1 << value));
	}

	// remove from possible moves within block
	int blockRow = row / 3;
	int blockCol = col / 3;
	for (int rowI = blockRow * 3; rowI < (blockRow + 1) * 3; rowI++)
		for (int colI = blockCol * 3; colI < (blockCol + 1) * 3; colI++)
			validMoves(rowI, colI, flip) &= (~(1 << value));
}

bool SudokuSolver::Pair::equalPositions(const Pair& p) const
{
	return (row1 == p.row1 && col1 == p.col1 && row2 == p.row2 && col2 == p.col2)
		|| (row1 == p.row2 && col1 == p.col2 && row2 == p.row1 && col2 == p.col1);
}

bool SudokuSolver::pairSolver(FlipGrid& validMoves)
{
	bool advanced = false;
	for (int blockRow = 0; blockRow < 3; blockRow++)
		for (int blockCol = 0; blockCol < 3; blockCol++)
		{
			// find all pairs
			std::vector<Pair> pairs;
			for (int value = 0; value < 9; value++)
			{
				Pair p{ value, -1, -1, -1, -1 };
				for (int row = blockRow * 3; row < (blockRow + 1) * 3; row++)
				{
					for (int col = blockCol * 3; col < (blockCol + 1) * 3; col++)
						if (validMoves(row, col) & (1 << value))
						{
							if (p.row1 == -1)
							{
								p.row1 = row;
								p.col1 = col;
							}
							else if (p.row2 == -1)
							{
								p.row2 = row;
								p.col2 = col;
							}
							else
							{
								p.value = -1;
								break;
							}
						}

					if (p.value == -1)
						break;
				}

				if (p.value != -1 && p.row1 != -1 && p.row2 != -1)
					pairs.push_back(p);
			}
			
			if (pairs.size() < 2) continue;

			// check equivalent pairs
			for (int pair1i = 0; pair1i < pairs.size() - 1; pair1i++)
			{
				const Pair& pair1 = pairs[pair1i];
				for (int pair2i = pair1i + 1; pair2i < pairs.size(); pair2i++)
				{
					const Pair& pair2 = pairs[pair2i];
					if (pair1.equalPositions(pair2))
					{
						unsigned int bitValue = (1 << pair1.value) | (1 << pair2.value);
						// check if this has any change to current state of valid moves
						if (validMoves(pair1.row1, pair1.col1) != bitValue
							|| validMoves(pair1.row2, pair1.col2) != bitValue)
						{
							validMoves(pair1.row1, pair1.col1) = bitValue;
							validMoves(pair1.row2, pair1.col2) = bitValue;

							advanced = true;
						}
					}
				}
			}
		}

	return advanced;
}

bool SudokuSolver::sweepSolver(FlipGrid& validMoves, bool flip)
{
	bool advanced = false;
	for (int blockRow = 0; blockRow < 3; blockRow++)
		for (int blockCol = 0; blockCol < 3; blockCol++)
			for (int value = 0; value < 9; value++)
			{
				int index = -1;
				for (int row = blockRow * 3; row < (blockRow + 1) * 3; row++)
				{
					int count = 0;
					for (int col = blockCol * 3; col < (blockCol + 1) * 3; col++)
						if (validMoves(row, col, flip) & (1 << value)) count++;

					if (count == 1 || (count >= 2 && index != -1))
					{
						index = -1;
						break;
					}
					else if (count >= 2)
						index = row;
				}

				if (index != -1)
				{
					// remove sweeped from possible moves
					for (int col = 0; col < 9; col++)
					{
						if (blockCol * 3 <= col && col < blockCol * 3 + 3)
							continue;

						if (validMoves(index, col, flip) & (1 << value))
						{
							validMoves(index, col, flip) &= (~(1 << value));
							advanced = true;
						}
					}
				}
			}

	return advanced;
}

void SudokuSolver::stableSolver(FlipGrid& solution, FlipGrid& validMoves, const Options& options)
{
	bool advanced;
	do
	{
		advanced = false;

		if (options.blocks)
		{
			if (blockSolver(solution, validMoves))
				advanced = true;
		}
		if (options.rows)
		{
			if (rowSolver(solution, validMoves) ||
				rowSolver(solution, validMoves, true))
				advanced = true;
		}
		if (options.pairing)
		{
			if (pairSolver(validMoves))
				advanced = true;
		}
		if (options.sweep)
		{
			if (sweepSolver(validMoves) ||
				sweepSolver(validMoves, true))
				advanced = true;
		}

	} while (advanced);
}

bool SudokuSolver::recursiveSolver(FlipGrid& solution, FlipGrid& validMoves, const Options& options)
{
	stableSolver(solution, validMoves, options);

	if (isSolved(solution))
		return true;

	// check if solution is unstable
	if (isUnstable(solution, validMoves))
		return false;

	// find least possible moves for cell to maximize propability for valid move
	int least = 10, leastRow = 0, leastCol = 0;
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (validMoves(row, col) == 0)
				continue;

			int count = 0;
			for (int value = 0; value < 9; value++)
				count += (validMoves(row, col) >> value) & 1;

			if (count < least)
			{
				least = count;
				leastRow = row;
				leastCol = col;
			}

			if (least <= 2) break;
		}
		if (least <= 2) break;
	}

	for (int value = 0; value < 9; value++)
	{
		if (!(validMoves(leastRow, leastCol) & (1 << value))) continue;

		FlipGrid solutionCopy(solution.grid);
		FlipGrid validMovesCopy(validMoves.grid);

		setValue(solutionCopy, validMovesCopy, leastRow, leastCol, value);

		if (recursiveSolver(solutionCopy, validMovesCopy, options))
		{
			solution = FlipGrid(solutionCopy.grid);
			return true;
		}
	}

	return false;
}

bool SudokuSolver::isSolved(const FlipGrid& solution)
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (solution(row, col) == 0) return false;

	return true;
}

bool SudokuSolver::isUnstable(const FlipGrid& solution, const FlipGrid& validMoves)
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (validMoves(row, col) == 0 && solution(row, col) == 0) return true;

	return false;
}