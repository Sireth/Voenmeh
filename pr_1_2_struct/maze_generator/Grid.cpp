#include <thread>
#include <random>
#include "Grid.h"


Grid::Grid(int width, int height): m_width(width), m_height(height), m_backtrace(width*height) {
    createCells();
    m_current = &m_cells[0];
}

void Grid::createCells() {
    for (int row = 0; row < m_height; row++) {
        for (int column = 0; column < m_width; column++) {
            m_cells.push_back(Cell(column, row));
        }
    }
}

Vector<Cell> Grid::generateMaze() {
    while (true) {
        m_current->setVisited(true);
        Cell *next = findNextCell();

        if (next != nullptr) {
            next->setVisited(true);
            m_backtrace.push(m_current);
            m_current->removeWalls(*next);
            m_current = next;
        } else if (m_backtrace.size() > 0) {
            m_current = m_backtrace.peek();
            m_backtrace.pop();
        } else if (m_backtrace.size() == 0) {
            break;
        }
    }
    return m_cells;
}



Cell *Grid::findNextCell() {
    Vector<Cell *> availableNeighbors = getAvailableNeighbors();
    if (!availableNeighbors.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned long> index(0, availableNeighbors.size() - 1);
        return availableNeighbors.at(index(gen));
    }

    return nullptr;
}

Vector<Cell *> Grid::getAvailableNeighbors() {
    Vector<Cell *> neighbors;

    int currentX = m_current->getX();
    int currentY = m_current->getY();

    int neighborIndexes[4] = {
            calculateIndex(currentX - 1, currentY),
            calculateIndex(currentX, currentY - 1),
            calculateIndex(currentX + 1, currentY),
            calculateIndex(currentX, currentY + 1),
    };

    for (int i : neighborIndexes) {
        if (i != -1 && !m_cells[i].isVisited()) {
            neighbors.push_back(&m_cells[i]);
        }
    }

    return neighbors;
}

int Grid::calculateIndex(int row, int column) const {
    if (row < 0 || column < 0 || column > m_width - 1 || row > m_height - 1)
        return -1;
    else
        return row + column * m_width;
}