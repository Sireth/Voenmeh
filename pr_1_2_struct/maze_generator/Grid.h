#ifndef TERM_2_GRID_H
#define TERM_2_GRID_H


#include "Cell.h"
#include "../stack/StackLinked.h"
#include "../vector/Vector.hpp"

class Grid {
private:
    int m_width;
    int m_height;

    Vector<Cell> m_cells;
    StackLinked<Cell *> m_backtrace;
    Cell *m_current;

    void createCells();

    [[nodiscard]] int calculateIndex(int i, int j) const;

    Vector<Cell *> getAvailableNeighbors();

    Cell *findNextCell();

public:
    Grid(int width, int height);

    Vector<Cell> generateMaze();
};


#endif //TERM_2_GRID_H
