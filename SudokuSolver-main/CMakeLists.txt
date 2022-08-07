cmake_minimum_required(VERSION 3.22)
project(SudokuSolver_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SudokuSolver_main
        Driver.cpp
        Fitness.h
        GeneticAlgorithm.cpp
        GeneticAlgorithm.h
        Population.h
        Puzzle.h
        PuzzleFactory.h
        Reproduction.h
        Sudoku.cpp
        Sudoku.h
        SudokuFactory.cpp
        SudokuFactory.h
        SudokuFitness.cpp
        SudokuFitness.h
        SudokuOffSpring.cpp
        SudokuOffSpring.h
        SudokuPopulation.cpp
        SudokuPopulation.h)
