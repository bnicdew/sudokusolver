// Name:Bryan Nicholson-Dews
// Date:9/19/2021

#include "vector"
#include <fstream>
#include <iostream>

#ifndef SUDOKU_H
#define SUDOKU_H

class Sudoku {
public:
    Sudoku();

    void loadFromFile(std::string);

    bool solve();

    void printSudoku(std::pair<uint32_t, uint32_t>);

    void printSudoku();

    void printSudoku(std::ostream&);

    bool checkVal(uint32_t, uint32_t, uint32_t);

    bool findVal(uint32_t, uint32_t, uint32_t);

    bool equals(const Sudoku& other) const;

    void findEmpty();

    bool isEmptyLoc(uint32_t, uint32_t);

    bool checkEmpty();

    friend std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku);

private:
    uint32_t sudNum[9][9];
    std::vector<uint32_t> rowLoc;
    std::vector<uint32_t> colLoc;
};

#endif