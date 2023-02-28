// CS 3270 - Vanderbilt University

#include "Sudoku.h"
#include <gtest/gtest.h>
#include <string>

int main()
{
    std::string ans, filename;
    Sudoku puzzle;

    // Ask user for text file name.
    std::cout << std::endl
              << "Enter puzzle text file (assumes file is in \"txt\" folder).";
    std::cout << std::endl
              << "Pressing <Enter> will run the file \"sudoku-test1.txt\".";
    std::cout << std::endl;
    std::getline(std::cin, filename);

    // Default to sudoku-test1.txt.
    if (filename.empty()) {
        filename = "sudoku-test1.txt";
    }

    // Load puzzle from text file.
    puzzle.loadFromFile("../txt/" + filename);

    // Display unsolved puzzle.
    std::cout << "\nPuzzle:\n\n";
    std::cout << puzzle;

    // Display solved puzzle.
    std::cout << std::endl;
    std::cout << "Solution:\n\n";

    clock_t startTime = clock();

    if (puzzle.solve()) {
        std::cout << puzzle << std::endl; // Print solved puzzle.
    } else {
        std::cout << "No Solution" << std::endl; // Indicate there is no solution.
    }

    clock_t endTime = clock();

    // Display time it took to solve puzzle.
    std::cout << "Time used: " << (endTime - startTime) / (double)CLOCKS_PER_SEC << " seconds."
              << std::endl;
}