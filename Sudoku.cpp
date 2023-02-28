// Name:Bryan Nicholson-Dews
// Date:9/19/2021
#include "Sudoku.h"

#ifndef SUDOKU_CPP
#define SUDOKU_CPP

const int LIMIT = 9;
const uint32_t BASE = 0;

/**
 * Default Constructor -
 */
Sudoku::Sudoku()
{
    for (uint32_t i = 0; i < LIMIT; ++i) {
        for (uint32_t j = 0; j < LIMIT; ++j) {
            sudNum[i][j] = 0;
        }
    }
}
/**
 * loadFromFile -
 * @param filename - loads in each number from the sudoku puzzle
 */
void Sudoku::loadFromFile(std::string filename)
{
    std::ifstream infile;
    infile.open(filename);
    uint32_t num;
    uint32_t row = BASE;
    uint32_t col = BASE;

    while (infile >> num) {
        sudNum[row][col] = num;
        col++;
        if (col == LIMIT) {
            col = BASE;
            row++;
        }
    }
}

/**
 * solve -
 * @return - true if the sudoku is filled out completely, false otherwise
 */
bool Sudoku::solve()
{
    findEmpty();
    bool answer = findVal(BASE, BASE, BASE);
    if (answer) {
        for (uint32_t i = BASE; i < LIMIT; ++i) {
            for (uint32_t j = BASE; j < LIMIT; ++j) {
                if (sudNum[i][j] == BASE) {
                    for (uint32_t k = BASE; k <= LIMIT; ++k) {
                        if (checkVal(i, j, k)) {
                            sudNum[i][j] = k;
                        }
                    }
                }
            }
        }
    }
    rowLoc.clear();
    colLoc.clear();
    return checkEmpty();
}

/**
 * checkEmpty -
 * @details - checks if there are any unfilled locations
 * @return - true if there are any empty spots, false otherwise
 */
bool Sudoku::checkEmpty()
{
    for (uint32_t i = 0; i < LIMIT; ++i) {
        for (uint32_t j = 0; j < LIMIT; ++j) {
            if (sudNum[i][j] == 0)
                return false;
        }
    }
    return true;
}

/**
 * findEmpty -
 * @details - finds all empty spots in the sudoku array and adds to a row vector and column vector
 */
void Sudoku::findEmpty()
{
    for (uint32_t i = 0; i < LIMIT; ++i) {
        for (uint32_t j = 0; j < LIMIT; ++j) {
            if (sudNum[i][j] == 0) {
                rowLoc.push_back(i);
                colLoc.push_back(j);
            }
        }
    }
}

/**
 * isEmptyLoc -
 * @param row - current row in the sudoku grid
 * @param col - current column in the sudoku grid
 * @return - true if the location was ever empty, false otherwise
 */
bool Sudoku::isEmptyLoc(uint32_t row, uint32_t col)
{
    for (uint32_t i = 0; i < rowLoc.size(); ++i) {
        if (row == rowLoc[i] && col == colLoc[i]) {
            return true;
        }
    }
    return false;
}

/**
 * findVal -
 * @param row - current row in the sudoku grid
 * @param col - current column in the sudoku grid
 * @param num - number stored in the current grid location
 * @return - true if the sudoku is completed, false otherwise
 */
bool Sudoku::findVal(uint32_t row, uint32_t col, uint32_t num)
{
    if (col == LIMIT) {
        col = BASE;
        row++;
    }
    if (row < LIMIT && col < LIMIT) {
        if (sudNum[row][col] == 0 || isEmptyLoc(row, col)) {
            for (uint32_t i = num; i <= LIMIT; ++i) {
                if (checkVal(row, col, i)) {
                    sudNum[row][col] = i;
                    col++;
                    return findVal(row, col, BASE);
                }
            }
            sudNum[row][col] = 0;
            uint32_t pass;
            for (uint32_t i = 0; i < rowLoc.size(); ++i) {
                if (row == rowLoc[i] && col == colLoc[i]) {
                    if (i == 0)
                        return false;
                    row = rowLoc[i - 1];
                    col = colLoc[i - 1];
                    pass = sudNum[row][col];
                }
            }
        
            return findVal(row, col, pass);
        }
        col++;
        return findVal(row, col, BASE);
    }
    return true;
}

/**
 * checkVal -
 * @param row - current row in the sudoku grid
 * @param col - current column in the sudoku grid
 * @param num - tests number 1 - 9 if it works in the sudoku grid
 * @return - true if thenumber works in the sudoku location, false if it doesn't
 */
bool Sudoku::checkVal(uint32_t row, uint32_t col, uint32_t num)
{
    for (uint32_t i = 0; i < LIMIT; ++i) {
        if (sudNum[i][col] == num)
            return false;
    }
    for (uint32_t i = 0; i < LIMIT; ++i) {
        if (sudNum[row][i] == num)
            return false;
    }
    for (uint32_t i = row - row % 3; i < (row - row % 3) + 3; ++i) {
        for (uint32_t j = col - col % 3; j < (col - col % 3) + 3; ++j) {
            if (sudNum[i][j] == num)
                return false;
        }
    }
    return true;
}

/**
 * equals -
 * @param other - puzzle to be compared against
 * @return - true if every value matches in both sudoku puzzles, false otherwise
 */
bool Sudoku::equals(const Sudoku& other) const
{
    for (uint32_t i = 0; i < LIMIT; ++i) {
        for (uint32_t j = 0; j < LIMIT; ++j) {
            if (sudNum[i][j] != other.sudNum[i][j])
                return false;
        }
    }
    return true;
}

/**
 * operator<<
 * @param out - ostream that holds the entire puzzle to be printed
 * @param sudoku - the sudoku puzzle that will be printed
 * @return - ostream containing the entire sudoku puzzle, formatted and ready to be printed
 */
std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku)
{
    for (uint32_t i = 0; i < LIMIT; ++i) {
        if (i % 3 == 0 && i != 0)
            out << "------+-------+------" << std::endl;
        for (uint32_t j = 0; j < LIMIT; ++j) {
            if (j % 3 == 0 && j != 0)
                out << "| ";
            if (sudoku.sudNum[i][j] == 0)
                out << "  ";
            else
                out << sudoku.sudNum[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}

#endif
