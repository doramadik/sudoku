#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

class SudokuSolver
{
public:
	struct Sudoku
	{
		int grid[9][9];

		Sudoku() = default;

		Sudoku(const int grid[9][9]);

		void print();

		int countSolvedCells();
	};

	struct Options
	{
		bool blocks = true;
		bool rows = true;
		bool sweep = true;
		bool pairing = true;
		bool recursive = true;
	};

	static Sudoku solve(const Sudoku& sudoku, const Options& options = Options());
private:
	struct FlipGrid
	{
		int grid[9][9]{};

		FlipGrid() = default;

		FlipGrid(const int grid[9][9]);

		int operator()(int row, int col, bool flip = false) const;

		int& operator()(int row, int col, bool flip = false);
	};

	// generates map of valid moves
	static FlipGrid generateValidMoves(const FlipGrid& solution);

	// checks if value can be placed on grid
	static bool isValidMove(const FlipGrid& solution, int row, int col, int value);

	// checks if row is occupied by value
	static bool checkRow(const FlipGrid& solution, int row, int value, bool flip = false);

	// checks if block is occupied by value
	static bool checkBlock(const FlipGrid& solution, int row, int col, int value);


	static bool blockSolver(FlipGrid& solution, FlipGrid& validMoves);

	static bool rowSolver(FlipGrid& solution, FlipGrid& validMoves, bool flip = false);

	static void setValue(FlipGrid& solution, FlipGrid& validMoves, int row, int col, int value, bool flip = false);

	struct Pair
	{
		int value;
		int row1, col1;
		int row2, col2;

		bool equalPositions(const Pair& p) const;
	};

	static bool pairSolver(FlipGrid& validMoves);

	static bool sweepSolver(FlipGrid& validMoves, bool flip = false);

	static void stableSolver(FlipGrid& solution, FlipGrid& validMoves, const Options& options);

	static bool recursiveSolver(FlipGrid& solution, FlipGrid& validMoves, const Options& options);

	static bool isSolved(const FlipGrid& solution);

	static bool isUnstable(const FlipGrid& solution, const FlipGrid& validMoves);
};

#endif // SUDOKU_SOLVER_HPP